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