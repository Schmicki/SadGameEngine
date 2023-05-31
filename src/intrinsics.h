#pragma once

#include "detection.h"

#if defined(COMPILER_MSVC) /* MSVC */

#define libexport __declspec(dllexport)
#define libimport __declspec(dllimport)
#define libhide
#define forceinline __forceinline

#define alignas(alignment) __declspec(align(alignment))
#define alignof(T) __alignof(T)

#endif /* MSVC */

#if defined(COMPILER_GCC) /* GCC */

#define libexport __attribute__((visibility("default")))
#define libimport
#define libhide __attribute__((visibility("hidden")))
#define forceinline __attribute__((always_inline))

#define alignas(alignment) __attribute__ ((aligned (alignment)))
#define alignof(T) __alignof__(T)

#endif /* GCC */

#if defined(COMPILER_CLANG) /* CLANG */

#define libexport __attribute__((visibility("default")))
#define libimport
#define libhide __attribute__((visibility("hidden")))
#define forceinline __attribute__((always_inline))

#define alignas(alignment) __attribute__ ((aligned (alignment)))
#define alignof(T) __alignof__(T)

#endif /* CLANG */

#define cachealign alignas(CACHE_LINE)