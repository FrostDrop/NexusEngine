#pragma once

#ifndef __GNUC__
#error This file should only be included on GCC compiler.
#endif


#define NEXUS_COMPILER_GCC
#define NEXUS_COMPILER_VERSION ((__GNUC__ * 100) + (__GNUC_MINOR__))


#define NEXUS_INLINE inline
#define NEXUS_FORCE_INLINE __attribute__((always_inline)) inline
#define NEXUS_NO_INLINE __attribute__ ((noinline))


#define NEXUS_SUPPRESS_WARNING(w)
#define NEXUS_DEPRECATED(function) __attribute((deprecated)) function
