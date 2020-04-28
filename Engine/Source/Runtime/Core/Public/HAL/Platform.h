#pragma once

/** Define all other platforms to be zero. */
#if !defined(NEXUS_PLATFORM_WINDOWS)
	#define NEXUS_PLATFORM_WINDOWS 0
#endif
#if !defined(NEXUS_PLATFORM_LINUX)
	#define NEXUS_PLATFORM_LINUX 0
#endif
#if !defined(NEXUS_PLATFORM_MAC)
	#define NEXUS_PLATFORM_MAC 0
#endif

/** Include generic platform header. */
#include "GenericPlatform/GenericPlatform.h"

/** Include platform headers. */
#if NEXUS_PLATFORM_WINDOWS
	#include "Windows/WindowsPlatform.h"
#elif NEXUS_PLATFORM_LINUX
	#include "Linux/LinuxPlatform.h"
#elif NEXUS_PLATFORM_MAC
	#include "Mac/MacPlatform.h"
#else
	#error Unknown platform
#endif


namespace Nexus
{

	using uint8 = FPlatformTypes::uint8;
	using uint16 = FPlatformTypes::uint16;
	using uint32 = FPlatformTypes::uint32;
	using uint64 = FPlatformTypes::uint64;

	using int8 = FPlatformTypes::int8;
	using int16 = FPlatformTypes::int16;
	using int32 = FPlatformTypes::int32;
	using int64 = FPlatformTypes::int64;

	using PlatformSizeType = FPlatformTypes::PlatformSizeType;

}

/** API definition. */
#if NEXUS_BUILD_DLL
	#define CORE_API DLLEXPORT
#else
	#define CORE_API DLLIMPORT
#endif

/** Inlining. */
#ifndef FORCEINLINE
	#define FORCEINLINE
#endif
#ifndef FORCENOINLINE
	#define FORCENOINLINE
#endif

/** Base defines. */
#ifndef PLATFORM_LITTLE_ENDIAN
	#define PLATFORM_LITTLE_ENDIAN 0
#endif


