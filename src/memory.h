#pragma once

#include <stdlib.h> /* malloc, free, ... */
#include <string.h> /* memcpy, memmove, ... */

#include "detection.h"
#include "intrinsics.h"
#include "aliases.h"

u32_t u32_lowest_bit(u32_t inValue);
u32_t u32_highest_bit(u32_t inValue);