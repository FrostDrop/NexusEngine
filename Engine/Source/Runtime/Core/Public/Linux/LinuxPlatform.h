#pragma once


namespace Nexus
{

	struct FLinuxPlatformTypes : public FGenericPlatformTypes
	{

		using PlatformSizeType = __SIZE_TYPE__;

	};

	using FPlatformTypes = FLinuxPlatformTypes;

}

/** Inline definitions. */
#if NEXUS_DEBUG
	#define FORCEINLINE inline
#else
	#define FORCEINLINE inline __attribute__ ((always_inline))
#endif

#define FORCENOINLINE __attribute__ ((noinline))

/** DLL definitions. */
#define DLLIMPORT __attribute__((visibility("default")))
#define DLLEXPORT __attribute__((visibility("default")))

/** Base defines. */
#define PLATFORM_LITTLE_ENDIAN 1

/** Only enable vectorintrinsics on x86(-64). */
#if defined(_M_IX86) || defined(__i386__) || defined(_M_X64) || defined(__x86_64__) || defined (__amd64__) 
	#define PLATFORM_ENABLE_VECTORINTRINSICS 1
#else
	#define PLATFORM_ENABLE_VECTORINTRINSICS 0
#endif