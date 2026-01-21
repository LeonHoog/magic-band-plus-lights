#include "ble_spam_attacks.h"
#include "protocols/magicband.h"

static Attack attacks[] = {
{
    .title="MagicBand+ Library",
    .text  = "Disney 0x0183 beacons",
    .protocol = &protocol_magicband,
    .payload = {
        .random_mac = true,
        .cfg.magicband = {
            .category = MB_Cat_E905_Single,
            .index = 0,
            .color5 = 0,
            .vibe_on = true,
        },
    },
},
{
        .title="CC Ping",
        .text  = "cc03000000",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_CC,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="CC 000100",
        .text  = "cc03000100",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_CC,
                .index = 1,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="CC 132000",
        .text  = "cc03132000",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_CC,
                .index = 2,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="00 cyan",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 0,
                .vibe_on = true,
            },
        },
    },
{
        .title="01 purple",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 1,
                .vibe_on = true,
            },
        },
    },
{
        .title="02 blue",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 2,
                .vibe_on = true,
            },
        },
    },
{
        .title="03 midnight blue",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 3,
                .vibe_on = true,
            },
        },
    },
{
        .title="04 blue",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 4,
                .vibe_on = true,
            },
        },
    },
{
        .title="05 bright purple",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 5,
                .vibe_on = true,
            },
        },
    },
{
        .title="06 lavender",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 6,
                .vibe_on = true,
            },
        },
    },
{
        .title="07 purple",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 7,
                .vibe_on = true,
            },
        },
    },
{
        .title="08 pink",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 8,
                .vibe_on = true,
            },
        },
    },
{
        .title="09 pink",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 9,
                .vibe_on = true,
            },
        },
    },
{
        .title="10 pink",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 10,
                .vibe_on = true,
            },
        },
    },
{
        .title="11 pink",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 11,
                .vibe_on = true,
            },
        },
    },
{
        .title="12 pink",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 12,
                .vibe_on = true,
            },
        },
    },
{
        .title="13 pink",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 13,
                .vibe_on = true,
            },
        },
    },
{
        .title="14 pink",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 14,
                .vibe_on = true,
            },
        },
    },
{
        .title="15 yellow orange",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 15,
                .vibe_on = true,
            },
        },
    },
{
        .title="16 off yellow",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 16,
                .vibe_on = true,
            },
        },
    },
{
        .title="17 yellow orange",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 17,
                .vibe_on = true,
            },
        },
    },
{
        .title="18 lime",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 18,
                .vibe_on = true,
            },
        },
    },
{
        .title="19 orange",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 19,
                .vibe_on = true,
            },
        },
    },
{
        .title="20 red orange",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 20,
                .vibe_on = true,
            },
        },
    },
{
        .title="21 red",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 21,
                .vibe_on = true,
            },
        },
    },
{
        .title="22 cyan",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 22,
                .vibe_on = true,
            },
        },
    },
{
        .title="23 cyan",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 23,
                .vibe_on = true,
            },
        },
    },
{
        .title="24 cyan",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 24,
                .vibe_on = true,
            },
        },
    },
{
        .title="25 green",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 25,
                .vibe_on = true,
            },
        },
    },
{
        .title="26 lime green",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 26,
                .vibe_on = true,
            },
        },
    },
{
        .title="27 white",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 27,
                .vibe_on = true,
            },
        },
    },
{
        .title="28 white",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 28,
                .vibe_on = true,
            },
        },
    },
{
        .title="29 off",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 29,
                .vibe_on = true,
            },
        },
    },
{
        .title="30 unique",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 30,
                .vibe_on = true,
            },
        },
    },
{
        .title="31 random",
        .text  = "single color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E905_Single,
                .index = 0,
                .color5 = 31,
                .vibe_on = true,
            },
        },
    },
{
        .title="E9-06 Dual (ex1)",
        .text  = "E9-06 dual palette",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E906_Dual,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-07 (ex1)",
        .text  = "unknown effect ex1",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E907_Unknown,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-07 (ex2)",
        .text  = "unknown effect ex2",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E907_Unknown,
                .index = 1,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-08 (ex1)",
        .text  = "6-bit color",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E908_6bit,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-09 5-Color (ex1)",
        .text  = "5-color palette",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E909_5Palette,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-0B Circle (ex1)",
        .text  = "circle animation",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E90B_Circle,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-0C Blink White",
        .text  = "blink white",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E90C_Animations,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-0C Orange Blink",
        .text  = "orange blink",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E90C_Animations,
                .index = 1,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-0C 5-Color Cycle",
        .text  = "palette cycle",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E90C_Animations,
                .index = 2,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-0C Taste the Rainbow",
        .text  = "rainbow cycle",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E90C_Animations,
                .index = 3,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-0E (ex1)",
        .text  = "example 1",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E90E_Examples,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-0E (ex2)",
        .text  = "example 2",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E90E_Examples,
                .index = 1,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-0E (ex3)",
        .text  = "example 3",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E90E_Examples,
                .index = 2,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-0E (ex4)",
        .text  = "example 4",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E90E_Examples,
                .index = 3,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-0E (ex5)",
        .text  = "example 5",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E90E_Examples,
                .index = 4,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-0F (ex1)",
        .text  = "example 1",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E90F_Examples,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-0F (ex2)",
        .text  = "example 2",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E90F_Examples,
                .index = 1,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-10 Alternating (ex1)",
        .text  = "alternating colors",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E910_Alternating,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-11 Cross Fade (ex1)",
        .text  = "cross fade",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E911_Crossfade,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-11 Cross Fade (ex2)",
        .text  = "cross fade",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E911_Crossfade,
                .index = 1,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-11 Cross Fade (ex3)",
        .text  = "cross fade",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E911_Crossfade,
                .index = 2,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-11 Cross Fade (ex4)",
        .text  = "cross fade",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E911_Crossfade,
                .index = 3,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-11 Cross Fade (ex5)",
        .text  = "cross fade",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E911_Crossfade,
                .index = 4,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-11 Cross Fade (ex6)",
        .text  = "cross fade",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E911_Crossfade,
                .index = 5,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-11 Cross Fade (ex7)",
        .text  = "cross fade",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E911_Crossfade,
                .index = 6,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-12 Circle+Vibe (ex1)",
        .text  = "circle + vibe",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E912_CircleVibe,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-12 Circle+Vibe (ex2)",
        .text  = "circle + vibe",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E912_CircleVibe,
                .index = 1,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-12 Circle+Vibe (ex3)",
        .text  = "circle + vibe",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E912_CircleVibe,
                .index = 2,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-13 (ex1)",
        .text  = "animation",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E913_Examples,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-13 (ex2)",
        .text  = "animation",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E913_Examples,
                .index = 1,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-14 (ex1)",
        .text  = "animation",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E914_Examples,
                .index = 0,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-14 (ex2)",
        .text  = "animation",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E914_Examples,
                .index = 1,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    },
{
        .title="E9-14 (ex3)",
        .text  = "animation",
        .protocol = &protocol_magicband,
        .payload = {
            .random_mac = true,
            .cfg.magicband = {
                .category = MB_Cat_E914_Examples,
                .index = 2,
                .color5 = 0,
                .vibe_on = false,
            },
        },
    }
};

Attack* get_attacks(void) {
    return attacks;
}

signed get_attacks_count(void) {
    return COUNT_OF(attacks);
}
