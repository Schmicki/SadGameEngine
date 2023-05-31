#pragma once

#include "detection.h"
#include "intrinsics.h"
#include "aliases.h"

#if defined(COMPILER_MSVC)

#define WIN32_LEAN_AND_MEAN 1

#include <Windows.h>

#undef near
#undef far

static i32_t atomic_load(i32_t* in_atomic)
{
	MemoryBarrier();
	return *in_atomic;
}

static void_t atomic_store(i32_t* in_atomic, i32_t in_new)
{
	MemoryBarrier();
	*in_atomic = in_new;
}

static i32_t atomic_exchange(i32_t* in_atomic, i32_t in_new)
{
	return InterlockedExchange((u32_t*)in_atomic, in_new);
}

static i32_t atomic_compare_exchange(i32_t* in_atomic, i32_t in_expected, i32_t in_new)
{
	return InterlockedCompareExchange((u32_t*)in_atomic, in_new, in_expected);
}

#elif defined(COMPILER_GCC)



#elif defined(COMPILER_CLANG)



#endif