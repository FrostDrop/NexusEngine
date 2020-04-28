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

/** DLL definitions. */
#define DLLIMPORT __declspec(dllimport)
#define DLLEXPORT __declspec(dllexport)

/** Bas defines. */
#define PLATFORM_LITTLE_ENDIAN 1