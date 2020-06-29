#pragma once


namespace Nexus
{

	struct FWindowsPlatformTypes : public FGenericPlatformTypes
	{
#ifdef _WIN64
		using PlatformSizeType = unsigned __int64;
#else
		using PlatformSizeType = unsigned long;
#endif
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


/** Base defines. */
#define PLATFORM_LITTLE_ENDIAN 1

/** Assume. */
#if !defined(__clang__) || defined(_MSC_VER)
	#define Assume(expr) __assume(expr)
#endif

/** Vector intrinsics. */
#define PLATFORM_ENABLE_VECTORINTRINSICS 1
