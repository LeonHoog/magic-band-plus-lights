#pragma once

#include <gui/view.h>
#include "../ble_spam.h"

void ble_spam_main_view_draw(Canvas* canvas, void* _model);
bool ble_spam_main_view_input(InputEvent* event, void* _context);
