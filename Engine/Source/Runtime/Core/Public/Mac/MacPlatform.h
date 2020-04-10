#pragma once


namespace Nexus
{

	struct FMacPlatformTypes : public FGenericPlatformTypes
	{

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

/** DLL definitions. */
#define DLLIMPORT
#define DLLEXPORT

/** Alignment. */
#define GCC_ALIGN(n) __attribute__((aligned(n)))