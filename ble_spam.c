#include "ble_spam.h"
#include "ble_spam_attacks.h"
#include <gui/gui.h>
#include <furi_hal_bt.h>
#include <extra_beacon.h>
#include <gui/elements.h>

#include "protocols/_protocols.h"
#include "views/main_view.h"

uint16_t delays[DELAYS_COUNT] = {20, 50, 100, 200, 500};

const NotificationSequence solid_message = {
    &message_red_0,
    &message_green_255,
    &message_blue_255,
    &message_do_not_reset,
    &message_delay_10,
    NULL,
};
NotificationMessage blink_message = {
    .type = NotificationMessageTypeLedBlinkStart,
    .data.led_blink.color = LightBlue | LightGreen,
    .data.led_blink.on_time = 10,
    .data.led_blink.period = 100,
};
const NotificationSequence blink_sequence = {
    &blink_message,
    &message_do_not_reset,
    NULL,
};
void ble_spam_start_blink(BleSpamState* state) {
    if(!state->ctx.led_indicator) return;
    uint16_t period = delays[state->delay];
    if(period <= 100) period += 30;
    blink_message.data.led_blink.period = period;
    notification_message_block(state->ctx.notification, &blink_sequence);
}
void ble_spam_stop_blink(BleSpamState* state) {
    if(!state->ctx.led_indicator) return;
    notification_message_block(state->ctx.notification, &sequence_blink_stop);
}

void ble_spam_randomize_mac(BleSpamState* state) {
    furi_hal_random_fill_buf(state->config.address, sizeof(state->config.address));
}

void ble_spam_start_extra_beacon(BleSpamState* state) {
    uint8_t size = 0;
    uint8_t buffer[31] = {0};
    uint16_t delay = delays[state->delay];
    GapExtraBeaconConfig* config = &state->config;
    Attack* attacks = get_attacks();
    Payload* payload = &attacks[state->index].payload;
    const Protocol* protocol = attacks[state->index].protocol;

    config->min_adv_interval_ms = delay;
    config->max_adv_interval_ms = delay * 1.5;
    if(payload->random_mac) ble_spam_randomize_mac(state);
    furi_check(furi_hal_bt_extra_beacon_set_config(config));

    if(protocol) {
        protocol->make_packet(payload, buffer, &size);
    } else {
        protocols[furi_hal_random_get() % protocols_count]->make_packet(NULL, buffer, &size);
    }
    furi_check(furi_hal_bt_extra_beacon_set_data(buffer, size));

    furi_check(furi_hal_bt_extra_beacon_start());
}

static int32_t adv_thread(void* _ctx) {
    BleSpamState* state = _ctx;
    
    while(true) {
        uint32_t flags = furi_thread_flags_wait(1 | 2, FuriFlagWaitAny, FuriWaitForever);
        if(flags & 2 || !state->advertising) break; // Exit flag or stop

        Attack* attacks = get_attacks();
        Payload* payload = &attacks[state->index].payload;
        const Protocol* protocol = attacks[state->index].protocol;

        if(!payload->random_mac) ble_spam_randomize_mac(state);
        ble_spam_start_blink(state);
        if(furi_hal_bt_extra_beacon_is_active()) {
            furi_check(furi_hal_bt_extra_beacon_stop());
        }

        while(state->advertising) {
             if(protocol && payload->mode == PayloadModeBruteforce &&
               payload->bruteforce.counter++ >= 10) {
                payload->bruteforce.counter = 0;
                payload->bruteforce.value =
                    (payload->bruteforce.value + 1) % (1 << (payload->bruteforce.size * 8));
            }

            ble_spam_start_extra_beacon(state);
            furi_thread_flags_wait(2, FuriFlagWaitAny, delays[state->delay]);
            furi_check(furi_hal_bt_extra_beacon_stop());
        }
        ble_spam_stop_blink(state);
    }
    return 0;
}

void ble_spam_toggle_adv(BleSpamState* state) {
    state->advertising = !state->advertising;
    if(state->advertising) {
        furi_thread_flags_set(furi_thread_get_id(state->thread), 1);
    } 
}

void ble_spam_manual_attack(BleSpamState* state) {
    if(!state->advertising) {
        Attack* attacks = get_attacks();
        Payload* payload = &attacks[state->index].payload;
        if(!payload->random_mac) ble_spam_randomize_mac(state);
        if(furi_hal_bt_extra_beacon_is_active()) {
            furi_check(furi_hal_bt_extra_beacon_stop());
        }

        ble_spam_start_extra_beacon(state);

        if(state->ctx.led_indicator)
            notification_message(state->ctx.notification, &solid_message);
        furi_delay_ms(10);
        furi_check(furi_hal_bt_extra_beacon_stop());

        if(state->ctx.led_indicator)
            notification_message_block(state->ctx.notification, &sequence_reset_rgb);
    }
}

static void lock_timer_callback(void* _ctx) {
    BleSpamState* state = _ctx;
    if(state->lock_count < 3) {
        notification_message_block(state->ctx.notification, &sequence_display_backlight_off);
    } else {
        state->ctx.lock_keyboard = false;
    }
    with_view_model(state->main_view, BleSpamState * *model, { (*model)->lock_warning = false; }, true);
    state->lock_count = 0;
    furi_timer_set_thread_priority(FuriTimerThreadPriorityNormal);
}

static bool custom_event_callback(void* _ctx, uint32_t event) {
    BleSpamState* state = _ctx;
    return scene_manager_handle_custom_event(state->ctx.scene_manager, event);
}

static void tick_event_callback(void* _ctx) {
    BleSpamState* state = _ctx;
    bool advertising;
    with_view_model(
        state->main_view, BleSpamState * *model, { advertising = (*model)->advertising; }, advertising);
    scene_manager_handle_tick_event(state->ctx.scene_manager);
}

static bool back_event_callback(void* _ctx) {
    BleSpamState* state = _ctx;
    return scene_manager_handle_back_event(state->ctx.scene_manager);
}

int32_t ble_spam(void* p) {
    UNUSED(p);
    GapExtraBeaconConfig prev_cfg;
    const GapExtraBeaconConfig* prev_cfg_ptr = furi_hal_bt_extra_beacon_get_config();
    if(prev_cfg_ptr) {
        memcpy(&prev_cfg, prev_cfg_ptr, sizeof(prev_cfg));
    }
    uint8_t prev_data[EXTRA_BEACON_MAX_DATA_SIZE];
    uint8_t prev_data_len = furi_hal_bt_extra_beacon_get_data(prev_data);
    bool prev_active = furi_hal_bt_extra_beacon_is_active();

    BleSpamState* state = malloc(sizeof(BleSpamState));
    state->config.adv_channel_map = GapAdvChannelMapAll;
    state->config.adv_power_level = GapAdvPowerLevel_6dBm;
    state->config.address_type = GapAddressTypePublic;
    state->thread = furi_thread_alloc();
    furi_thread_set_callback(state->thread, adv_thread);
    furi_thread_set_context(state->thread, state);
    furi_thread_set_stack_size(state->thread, 2048);
    furi_thread_start(state->thread);
    state->ctx.led_indicator = true;
    state->lock_timer = furi_timer_alloc(lock_timer_callback, FuriTimerTypeOnce, state);

    state->ctx.notification = furi_record_open(RECORD_NOTIFICATION);
    Gui* gui = furi_record_open(RECORD_GUI);
    state->ctx.view_dispatcher = view_dispatcher_alloc();

    view_dispatcher_set_event_callback_context(state->ctx.view_dispatcher, state);
    view_dispatcher_set_custom_event_callback(state->ctx.view_dispatcher, custom_event_callback);
    view_dispatcher_set_tick_event_callback(state->ctx.view_dispatcher, tick_event_callback, 100);
    view_dispatcher_set_navigation_event_callback(state->ctx.view_dispatcher, back_event_callback);
    state->ctx.scene_manager = scene_manager_alloc(&scene_handlers, &state->ctx);

    state->main_view = view_alloc();
    view_allocate_model(state->main_view, ViewModelTypeLocking, sizeof(BleSpamState*));
    with_view_model(state->main_view, BleSpamState * *model, { *model = state; }, false);
    view_set_context(state->main_view, state->main_view);
    view_set_draw_callback(state->main_view, ble_spam_main_view_draw);
    view_set_input_callback(state->main_view, ble_spam_main_view_input);
    view_dispatcher_add_view(state->ctx.view_dispatcher, ViewMain, state->main_view);

    state->ctx.byte_input = byte_input_alloc();
    view_dispatcher_add_view(
        state->ctx.view_dispatcher, ViewByteInput, byte_input_get_view(state->ctx.byte_input));

    state->ctx.submenu = submenu_alloc();
    view_dispatcher_add_view(
        state->ctx.view_dispatcher, ViewSubmenu, submenu_get_view(state->ctx.submenu));

    state->ctx.text_input = text_input_alloc();
    view_dispatcher_add_view(
        state->ctx.view_dispatcher, ViewTextInput, text_input_get_view(state->ctx.text_input));

    state->ctx.variable_item_list = variable_item_list_alloc();
    view_dispatcher_add_view(
        state->ctx.view_dispatcher,
        ViewVariableItemList,
        variable_item_list_get_view(state->ctx.variable_item_list));

    view_dispatcher_attach_to_gui(state->ctx.view_dispatcher, gui, ViewDispatcherTypeFullscreen);
    scene_manager_next_scene(state->ctx.scene_manager, SceneMain);
    view_dispatcher_run(state->ctx.view_dispatcher);

    view_dispatcher_remove_view(state->ctx.view_dispatcher, ViewByteInput);
    byte_input_free(state->ctx.byte_input);

    view_dispatcher_remove_view(state->ctx.view_dispatcher, ViewSubmenu);
    submenu_free(state->ctx.submenu);

    view_dispatcher_remove_view(state->ctx.view_dispatcher, ViewTextInput);
    text_input_free(state->ctx.text_input);

    view_dispatcher_remove_view(state->ctx.view_dispatcher, ViewVariableItemList);
    variable_item_list_free(state->ctx.variable_item_list);

    view_dispatcher_remove_view(state->ctx.view_dispatcher, ViewMain);
    view_free(state->main_view);

    scene_manager_free(state->ctx.scene_manager);
    view_dispatcher_free(state->ctx.view_dispatcher);
    furi_record_close(RECORD_GUI);
    furi_record_close(RECORD_NOTIFICATION);

    furi_timer_free(state->lock_timer);
    
    // Stop worker thread
    state->advertising = false;
    furi_thread_flags_set(furi_thread_get_id(state->thread), 2); // Set exit flag
    furi_thread_join(state->thread);
    furi_thread_free(state->thread);

    free(state);

    if(furi_hal_bt_extra_beacon_is_active()) {
        furi_check(furi_hal_bt_extra_beacon_stop());
    }
    if(prev_cfg_ptr) {
        furi_check(furi_hal_bt_extra_beacon_set_config(&prev_cfg));
    }
    furi_check(furi_hal_bt_extra_beacon_set_data(prev_data, prev_data_len));
    if(prev_active) {
        furi_check(furi_hal_bt_extra_beacon_start());
    }
    return 0;
}
