#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include <assets_icons.h>
#include "ble_spam_icons.h"
#include <furi_hal_random.h>
#include <core/core_defines.h>
#include "../ble_spam.h"

typedef struct Payload Payload;

typedef struct {
    const Icon* icon;
    const char* (*get_name)(const Payload* payload);
    void (*make_packet)(Payload* payload, uint8_t* buffer, uint8_t* size);
    void (*extra_config)(Ctx* ctx);
    uint8_t (*config_count)(const Payload* payload);
} Protocol;
