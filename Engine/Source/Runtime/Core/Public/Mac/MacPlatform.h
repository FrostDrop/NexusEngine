#pragma once


namespace Nexus
{

	struct FMacPlatformTypes : public FGenericPlatformTypes
	{

		using PlatformSizeType = size_t;

	};

	using FPlatformTypes = FMacPlatformTypes;

}

/** Inline definitions. */
#if NEXUS_DEBUG
	#define FORCEINLINE inline
#else
	#define FORCEINLINE inline __attribute__ ((always_inline))
#endif

#define FORCENOINLINE __attribute__ ((noinline))

/** Function type macros. */
#define VARARGS

/** DLL definitions. */
#define DLLIMPORT
#define DLLEXPORT

/** Base defines. */
#define PLATFORM_LITTLE_ENDIAN 1