#pragma once

#include <notification/notification_messages.h>
#include <gui/view_dispatcher.h>
#include <gui/modules/byte_input.h>
#include <gui/modules/submenu.h>
#include <gui/modules/text_input.h>
#include <gui/modules/variable_item_list.h>

#include "extra_beacon.h"
#include "furi_hal_bt.h"
#include "scenes/_setup.h"

enum {
    ViewMain,
    ViewByteInput,
    ViewSubmenu,
    ViewTextInput,
    ViewVariableItemList,
};

enum {
    ConfigRandomMac,
    ConfigExtraStart = ConfigRandomMac,
    ConfigLedIndicator,
    ConfigLockKeyboard,
};

typedef struct Attack Attack;
typedef struct BleSpamState BleSpamState;

typedef struct {
    Attack* attack;
    uint8_t byte_store[3];
    VariableItemListEnterCallback fallback_config_enter;
    bool led_indicator;
    bool lock_keyboard;

    NotificationApp* notification;
    ViewDispatcher* view_dispatcher;
    SceneManager* scene_manager;

    ByteInput* byte_input;
    Submenu* submenu;
    TextInput* text_input;
    VariableItemList* variable_item_list;
    //OFW PATCH
    VariableItem* item_pp_color;

} Ctx;

struct BleSpamState {
    Ctx ctx;
    View* main_view;
    bool lock_warning;
    uint8_t lock_count;
    FuriTimer* lock_timer;

    bool advertising;
    uint8_t delay;
    GapExtraBeaconConfig config;
    FuriThread* thread;
    int8_t index;
    bool ignore_bruteforce;
};

void ble_spam_toggle_adv(BleSpamState* state);
void ble_spam_start_blink(BleSpamState* state);
void ble_spam_stop_blink(BleSpamState* state);
void ble_spam_randomize_mac(BleSpamState* state);
void ble_spam_start_extra_beacon(BleSpamState* state);
void ble_spam_manual_attack(BleSpamState* state);

#define DELAYS_COUNT 5
extern uint16_t delays[DELAYS_COUNT];

