#pragma once

#include "protocols/_protocols.h"

Attack* get_attacks(void);
signed get_attacks_count(void);
#define ATTACKS_COUNT get_attacks_count()
