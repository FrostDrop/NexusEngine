#pragma once


namespace Nexus
{

	struct FWindowsPlatformTypes : public FGenericPlatformTypes
	{

	};

	using FPlatformTypes = FWindowsPlatformTypes;

}

/** Inline definitions. */
#if NEXUS_DEBUG
	#define FORCEINLINE inline
#else
	#define FORCEINLINE __forceinline
#endif

#define FORCENOINLINE __declspec(noinline)

/** DLL definitions. */
#define DLLIMPORT __declspec(dllimport)
#define DLLEXPORT __declspec(dllexport)

/** Bas defines. */
#define PLATFORM_LITTLE_ENDIAN 1