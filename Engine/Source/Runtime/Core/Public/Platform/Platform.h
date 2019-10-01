#pragma once


#if defined(__x86_64__) || defined(_M_X64)
	#define NEXUS_PLATFORM_CPU_X64
#elif defined(__i386) || defined(_M_IX86)
	#define NEXUS_PLATFORM_CPU_X86
#else
	#define NEXUS_PLATFORM_CPU_UNKNOWN
#endif


#if defined(_MSC_FULL_VER)
	#include "Msvc.h"
#elif defined(__GNUC__)
	#include "Gcc.h"
#else
	#error Unsupported compiler was used.
#endif


#ifdef NEXUS_COMPILER_MSVC
	#ifdef NEXUS_LIB_TYPE_DLL
		#define NEXUS_API __declspec(dllexport)
	#else
		#define NEXUS_API __declspec(dllimport)
	#endif
#elif defined NEXUS_COMPILER_GCC
	#ifdef NEXUS_LIB_TYPE_DLL
		#define NEXUS_API
	#else
		#define NEXUS_API
	#endif
#else
	#ifdef NEXUS_LIB_TYPE_DLL
		#define NEXUS_API
	#else
		#define NEXUS_API
	#endif
#endif