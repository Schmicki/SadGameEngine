#pragma once

/* detect compiler */
#if defined(_MSC_VER)

#define COMPILER_MSVC 1

#elif defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)

#define COMPILER_GCC 1

#elif defined(__clang__)

#define COMPILER_CLANG 1

#else

#error detection could not find compiler, please implement it

#endif

/* detect architecture */
#if defined(_M_AMD64) || defined(_M_X64) || defined(__x86_64__) || defined(__amd64__)

#define PLATFORM_X64 1

#elif defined(_M_IX86) || defined(__i386__)

#define PLATFORM_X86 1

#elif  defined(_M_ARM64) || defined(__aarch64__) || defined(_M_ARM64EC)

#define PLATFORM_ARM64 1

#elif defined(_M_ARM) || defined(__ar_)

#define PLATFORM_ARM32 1

#elif defined(__mips__)

#define PLATFORM_MIPS 1

#else

#error detection could not find architecture, please implement it

#endif

/* detect os */
#if defined(_WIN64) || defined(_WIN32) || defined(WIN32)

#define OS_WINDOWS 1

#elif defined(__ANDROID__) || defined(ANDROID)

#define OS_ANDROID 1

#elif defined(__linux__)

#define OS_LINUX 1

#elif defined(__APPLE__)

#define OS_MACOS 1

#elif defined(__PSP__)

#define OS_PSP 1

#else

#error detection could not find system, please implement it

#endif

/* detect build mode */
#if defined(DEBUG) || defined(_DEBUG) || !defined(NDEBUG) || BUILD_DEBUG

#ifndef BUILD_DEBUG
#define BUILD_DEBUG 1
#endif

#else

#ifndef BUILD_RELEASE
#define BUILD_RELEASE 1
#endif

#ifndef NDEBUG
#define NDEBUG 1
#endif

#endif

/* detect platform features */
#if defined(PLATFORM_X86) /* X86 */
#define PLATFORM_HAS_F64 1
#define CACHE_LINE 64
#endif /* X86 */

#if defined(PLATFORM_X64) /* X64 */
#define PLATFORM_HAS_I64 1
#define PLATFORM_HAS_F64 1
#define CACHE_LINE 64
#endif /* X64 */

#if defined(PLATFORM_ARM32) /* ARM32 */
#define CACHE_LINE 64
#endif /* ARM32 */

#if defined(PLATFORM_ARM64) /* ARM64 */
#define PLATFORM_HAS_I64 1
#define CACHE_LINE 64
#endif /* ARM64 */

#if defined(PLATFORM_MIPS) /* MIPS */
#define CACHE_LINE 64
#endif /* MIPS */