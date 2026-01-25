#include <gui/elements.h>

#include "main_view.h"
#include "../ble_spam_attacks.h"
#include "../protocols/_protocols.h"

#define PAGE_MIN (-5)
enum {
    PageHelpBruteforce = PAGE_MIN,
    PageHelpApps,
    PageHelpDelay,
    PageHelpDistance,
    PageHelpInfoConfig,
    PageStart = 0,
};
#define PageEnd (ATTACKS_COUNT - 1)
#define PAGE_MAX ATTACKS_COUNT
#define PageAboutCredits PAGE_MAX

#ifndef FAP_VERSION
#define FAP_VERSION "1.0.0"
#endif

void ble_spam_main_view_draw(Canvas* canvas, void* _model) {
    BleSpamState* state = *(BleSpamState**)_model;
    const char* back = "Back";
    const char* next = "Next";
    if(state->index < 0) {
        back = "Next";
        next = "Back";
    }
    if(state->index == PageStart - 1) {
        next = "Spam";
    } else if(state->index == PageStart) {
        back = "Help";
    } else if(state->index == PageEnd) {
        next = "About";
    } else if(state->index == PageEnd + 1) {
        back = "Spam";
    }

    Attack* attacks = get_attacks();
    const Attack* attack =
        (state->index >= 0 && state->index <= ATTACKS_COUNT - 1) ? &attacks[state->index] : NULL;
    const Payload* payload = attack ? &attack->payload : NULL;
    const Protocol* protocol = attack ? attack->protocol : NULL;

    canvas_set_font(canvas, FontSecondary);
    const Icon* icon = protocol ? protocol->icon : &I_ble_spam;
    canvas_draw_icon(canvas, 4 - (icon == &I_ble_spam), 3, icon);
    canvas_draw_str(canvas, 14, 12, "MagicBand+");

    if(state->index == PageHelpBruteforce) {
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str_aligned(canvas, 124, 12, AlignRight, AlignBottom, "Help");
        elements_text_box(
            canvas,
            4,
            16,
            120,
            48,
            AlignLeft,
            AlignTop,
            "\e#Bruteforce\e# cycles codes\n"
            "to find popups, hold left and\n"
            "right to send manually and\n"
            "change delay",
            false);
    } else if(state->index == PageHelpApps) {
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str_aligned(canvas, 124, 12, AlignRight, AlignBottom, "Help");
        elements_text_box(
            canvas,
            4,
            16,
            120,
            48,
            AlignLeft,
            AlignTop,
            "\e#Some Apps\e# interfere\n"
            "with the attacks, stay on\n"
            "homescreen for best results",
            false);
    } else if(state->index == PageHelpDelay) {
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str_aligned(canvas, 124, 12, AlignRight, AlignBottom, "Help");
        elements_text_box(
            canvas,
            4,
            16,
            120,
            48,
            AlignLeft,
            AlignTop,
            "\e#Delay\e# is time between\n"
            "attack attempts (top right),\n"
            "keep 20ms for best results",
            false);
    } else if(state->index == PageHelpDistance) {
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str_aligned(canvas, 124, 12, AlignRight, AlignBottom, "Help");
        elements_text_box(
            canvas,
            4,
            16,
            120,
            48,
            AlignLeft,
            AlignTop,
            "\e#Distance\e# varies greatly:\n"
            "some are long range (>30 m)\n"
            "others are close range (<1 m)",
            false);
    } else if(state->index == PageHelpInfoConfig) {
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str_aligned(canvas, 124, 12, AlignRight, AlignBottom, "Help");
        elements_text_box(
            canvas,
            4,
            16,
            120,
            48,
            AlignLeft,
            AlignTop,
            "See \e#more info\e# and change\n"
            "attack \e#options\e# by holding\n"
            "Ok on each attack page",
            false);
    } else if(state->index == PageAboutCredits) {
        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str_aligned(canvas, 124, 12, AlignRight, AlignBottom, "Credits");
        elements_text_box(
            canvas,
            4,
            16,
            122,
            48,
            AlignLeft,
            AlignTop,
            "Original App/Code: \e#WillyJL\e#\n"
            "Modified By: \e#haw8411\e#\n"
            "                                   Version \e#" FAP_VERSION "\e#",
            false);
    } else if(attack) {
        if(state->ctx.lock_keyboard && !state->advertising) {
            ble_spam_toggle_adv(state);
        }
        char str[32];

        canvas_set_font(canvas, FontPrimary);
        if(payload->mode == PayloadModeBruteforce) {
            snprintf(
                str,
                sizeof(str),
                "0x%0*lX",
                payload->bruteforce.size * 2,
                payload->bruteforce.value);
        } else {
            snprintf(str, sizeof(str), "%ims", delays[state->delay]);
        }
        canvas_draw_str_aligned(canvas, 116, 12, AlignRight, AlignBottom, str);
        canvas_draw_icon(canvas, 119, 6, &I_SmallArrowUp_3x5);
        canvas_draw_icon(canvas, 119, 10, &I_SmallArrowDown_3x5);

        canvas_set_font(canvas, FontPrimary);
        if(payload->mode == PayloadModeBruteforce) {
            canvas_draw_str_aligned(canvas, 64, 22, AlignCenter, AlignBottom, "Bruteforce");
            if(delays[state->delay] < 100) {
                snprintf(str, sizeof(str), "%ims>", delays[state->delay]);
            } else {
                snprintf(str, sizeof(str), "%.1fs>", (double)delays[state->delay] / 1000);
            }
            uint16_t w = canvas_string_width(canvas, str);
            elements_slightly_rounded_box(canvas, 3, 14, 30, 10);
            elements_slightly_rounded_box(canvas, 119 - w, 14, 6 + w, 10);
            canvas_invert_color(canvas);
            canvas_draw_str_aligned(canvas, 5, 22, AlignLeft, AlignBottom, "<Send");
            canvas_draw_str_aligned(canvas, 122, 22, AlignRight, AlignBottom, str);
            canvas_invert_color(canvas);
        } else {
            snprintf(
                str,
                sizeof(str),
                "%02i/%02i: %s",
                state->index + 1,
                ATTACKS_COUNT,
                protocol ? protocol->get_name(payload) : "Everything AND");
            canvas_draw_str(canvas, 4 - (state->index < 19 ? 1 : 0), 22, str);
        }

        canvas_set_font(canvas, FontPrimary);
        canvas_draw_str(canvas, 4, 33, attack->title);

        canvas_set_font(canvas, FontSecondary);
        canvas_draw_str(canvas, 4, 46, attack->text);

        elements_button_center(canvas, state->advertising ? "Stop" : "Start");
    }

    if(state->index > PAGE_MIN) {
        elements_button_left(canvas, back);
    }
    if(state->index < PAGE_MAX) {
        elements_button_right(canvas, next);
    }

    if(state->lock_warning) {
        canvas_set_font(canvas, FontSecondary);
        elements_bold_rounded_frame(canvas, 14, 8, 99, 48);
        elements_multiline_text(canvas, 65, 26, "To unlock\npress:");
        canvas_draw_icon(canvas, 65, 42, &I_Pin_back_arrow_10x8);
        canvas_draw_icon(canvas, 80, 42, &I_Pin_back_arrow_10x8);
        canvas_draw_icon(canvas, 95, 42, &I_Pin_back_arrow_10x8);
        canvas_draw_icon(canvas, 16, 13, &I_WarningDolphin_45x42);
        canvas_draw_dot(canvas, 17, 61);
    }
}

bool ble_spam_main_view_input(InputEvent* input, void* _context) {
    View* view = _context;
    BleSpamState* state = *(BleSpamState**)view_get_model(view);
    bool consumed = false;

    if(state->ctx.lock_keyboard) {
        consumed = true;
        state->lock_warning = true;
        if(state->lock_count == 0) {
            furi_timer_set_thread_priority(FuriTimerThreadPriorityElevated);
            furi_timer_start(state->lock_timer, 1000);
        }
        if(input->type == InputTypeShort && input->key == InputKeyBack) {
            state->lock_count++;
        }
        if(state->lock_count >= 3) {
            furi_timer_set_thread_priority(FuriTimerThreadPriorityElevated);
            furi_timer_start(state->lock_timer, 1);
        }
    } else if(
        input->type == InputTypeShort || input->type == InputTypeLong ||
        input->type == InputTypeRepeat) {
        consumed = true;

        Attack* attacks = get_attacks();
        bool is_attack = state->index >= 0 && state->index <= ATTACKS_COUNT - 1;
        Payload* payload = is_attack ? &attacks[state->index].payload : NULL;
        bool advertising = state->advertising;

        switch(input->key) {
        case InputKeyOk:
            if(is_attack) {
                if(input->type == InputTypeLong) {
                    if(advertising) ble_spam_toggle_adv(state);
                    state->ctx.attack = &attacks[state->index];
                    scene_manager_set_scene_state(state->ctx.scene_manager, SceneConfig, 0);
                    view_commit_model(view, consumed);
                    scene_manager_next_scene(state->ctx.scene_manager, SceneConfig);
                    return consumed;
                } else if(input->type == InputTypeShort) {
                    ble_spam_toggle_adv(state);
                }
            }
            break;
        case InputKeyUp:
            if(is_attack) {
                if(payload->mode == PayloadModeBruteforce) {
                    payload->bruteforce.counter = 0;
                    payload->bruteforce.value =
                        (payload->bruteforce.value + 1) % (1 << (payload->bruteforce.size * 8));
                } else if(state->delay < DELAYS_COUNT - 1) {
                    state->delay++;
                    if(advertising) ble_spam_start_blink(state);
                }
            }
            break;
        case InputKeyDown:
            if(is_attack) {
                if(payload->mode == PayloadModeBruteforce) {
                    payload->bruteforce.counter = 0;
                    payload->bruteforce.value =
                        (payload->bruteforce.value - 1) % (1 << (payload->bruteforce.size * 8));
                } else if(state->delay > 0) {
                    state->delay--;
                    if(advertising) ble_spam_start_blink(state);
                }
            }
            break;
        case InputKeyLeft:
            if(input->type == InputTypeLong) {
                state->ignore_bruteforce = payload ? (payload->mode != PayloadModeBruteforce) :
                                                     true;
            }
            if(input->type == InputTypeShort || !is_attack || state->ignore_bruteforce ||
               payload->mode != PayloadModeBruteforce) {
                if(state->index > PAGE_MIN) {
                    if(advertising) ble_spam_toggle_adv(state);
                    state->index--;
                }
            } else {
               ble_spam_manual_attack(state);
            }
            break;
        case InputKeyRight:
            if(input->type == InputTypeLong) {
                state->ignore_bruteforce = payload ? (payload->mode != PayloadModeBruteforce) :
                                                     true;
            }
            if(input->type == InputTypeShort || !is_attack || state->ignore_bruteforce ||
               payload->mode != PayloadModeBruteforce) {
                if(state->index < PAGE_MAX) {
                    if(advertising) ble_spam_toggle_adv(state);
                    state->index++;
                }
            } else if(input->type == InputTypeLong) {
                state->delay = (state->delay + 1) % DELAYS_COUNT;
                if(advertising) ble_spam_start_blink(state);
            }
            break;
        case InputKeyBack:
             if(advertising) ble_spam_toggle_adv(state);
             consumed = false;
             break;
        default:
            break;
        }
    }

    view_commit_model(view, consumed);
    return consumed;
}
