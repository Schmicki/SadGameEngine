#pragma once

#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h> /* printf, fopen, ... */
#include "platform.h"

u8_t* load_file(const char* file, u32_t oversize, u32_t* out_len);
u8_t* load_image_from_file(const char* file, u32_t* out_x, u32_t* out_y);