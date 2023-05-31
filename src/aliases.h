#pragma once

#include <stddef.h> /* ptrdiff_t, size_t, ... */
#include <stdint.h> /* int8_t, int16_t, ... */

#include "detection.h"
#include "intrinsics.h"

/* Special type aliases. */

typedef void void_t;
typedef char char_t;

/* Integer aliases. */

typedef int8_t i8_t;
typedef int16_t i16_t;
typedef int32_t i32_t;

typedef uint8_t u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;

typedef ptrdiff_t iptr_t;
typedef size_t uptr_t;

#if defined(PLATFORM_HAS_I64)

typedef int64_t i64_t;
typedef uint64_t u64_t;

#endif

/* Float alias. */

#if !defined(PLATFORM_HAS_F64) && defined(FLT_F64) /* !F64 && FLT_64 */

#undef FLT_F64

#endif /* NO F64 */

#if defined FLT_F64 /* FLT_F64 */

typedef double flt_t;

#else /* FLT_F32 */

typedef float flt_t;

#endif /* FLT_F32 */

/* Common function types. */

typedef u32_t(*hashfunc_t)(void_t*);
typedef i32_t(*cmpfunc_t)(void_t*, void_t*);

/*************************************************************************************************/

#ifdef NULL
#undef NULL
#endif

#ifdef FALSE
#undef FALSE
#endif

#ifdef TRUE
#undef TRUE
#endif

#define FALSE 0
#define TRUE 1
#define NULL 0

#define I8_MIN INT8_MIN
#define I16_MIN INT16_MIN
#define I32_MIN INT32_MIN
#define I64_MIN INT64_MIN
#define IPTR_MIN PTRDIFF_MIN

#define I8_MAX INT8_MAX
#define I16_MAX INT16_MAX
#define I32_MAX INT32_MAX
#define I64_MAX INT64_MAX
#define IPTR_MAX PTRDIFF_MAX

#define U8_MAX UINT8_MAX
#define U16_MAX UINT16_MAX
#define U32_MAX UINT32_MAX
#define U64_MAX UINT64_MAX
#define UPTR_MAX SIZE_MAX
