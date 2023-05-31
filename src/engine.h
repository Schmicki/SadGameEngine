#pragma once

#include "platform.h"
#include "containers.h"
#include "math.h"
#include "renderer.h"

/*************************************************************************************************/

#define MAX_PLAYERS 8

typedef struct player_t
{
	u32_t input_device;
} player_t;

/*************************************************************************************************/

extern player_t players[MAX_PLAYERS + 1];

#if defined(OS_HAS_WINDOW) /* OS_HAS_WINDOW */

extern window_t main_window;

#endif /* OS_HAS_WINDOW */

extern render_interface_t render_interface;

/*************************************************************************************************/

u8_t engine_initialize();

u8_t engine_update();

u8_t engine_destroy();