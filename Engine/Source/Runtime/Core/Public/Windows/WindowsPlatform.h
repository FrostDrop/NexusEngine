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
#define FORCEINLINE __forceinline
#define FORCENOINLINE __declspec(noinline)

/** Function type macros. */
#define VARARGS __cdecl

/** DLL definitions. */
#define DLLIMPORT __declspec(dllimport)
#define DLLEXPORT __declspec(dllexport)

/** Base defines. */
#define PLATFORM_LITTLE_ENDIAN 1

/** Assume. */
#if !defined(__clang__) || defined(_MSC_VER)
	#define Assume(expr) __assume(expr)
#endif