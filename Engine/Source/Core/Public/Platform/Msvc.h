#pragma once

#ifndef _MSC_FULL_VER
#error This file should only be included on MSVC compiler.
#endif


#define NEXUS_COMPILER_MSVC
#define NEXUS_COMPILER_VERSION _MSC_FULL_VER


#define NEXUS_INLINE inline
#define NEXUS_FORCE_INLINE __forceinline
#define NEXUS_NO_INLINE __declspec(noinline)


#define NEXUS_SUPPRESS_WARNING(w) __pragma(warning(suppress: w))
#define NEXUS_DEPRECATED(function) __declspec(deprecated) function