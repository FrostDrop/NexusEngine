#pragma once


namespace Nexus
{

	struct FWindowsPlatformTypes : public FGenericPlatformTypes
	{

	};

	using FPlatformTypes = FWindowsPlatformTypes;

}

/** Inline definitions. */
#define FORCEINLINE __forceinline
#define FORCENOINLINE __declspec(noinline)

/** DLL definitions. */
#define DLLIMPORT __declspec(dllimport)
#define DLLEXPORT __declspec(dllexport)

// Alignment.
#if defined(__clang__)
	#define GCC_PACK(n) __attribute__((packed,aligned(n)))
	#define GCC_ALIGN(n) __attribute__((aligned(n)))
	#if defined(_MSC_VER)
		#define MS_ALIGN(n) __declspec(align(n))
	#endif
#else
	#define MS_ALIGN(n) __declspec(align(n))
#endif