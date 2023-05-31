#pragma once

#include "detection.h"
#include "intrinsics.h"
#include "aliases.h"
#include "memory.h"
#include "iostream.h"

#if defined(OS_WINDOWS) || defined(OS_LINUX) /* OS_WINDOWS || OS_LINUX */

/*************************************************************************************************/

#define OS_HAS_WINDOW 1

#if defined(COMPILER_MSVC) /* MSVC */

typedef struct window_t
{
	void_t* handle;
} window_t;

#undef near
#undef far

#endif /* MSVC */

/*************************************************************************************************/

window_t window_new(const char_t* title);

void window_free(window_t* window);

void window_swap_buffers(window_t* window);

/* input */

u8_t window_process_messages();

void_t window_input_initialize();

#endif /* OS_WINDOWS || OS_LINUX */