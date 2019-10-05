#pragma once

#include "HAL/Platform.h"

namespace Nexus
{

	struct FGenericPlatformMath
	{

		/** Computes absolute value in a generic way */
		template< class T >
		static constexpr FORCEINLINE T Abs(const T A)
		{
			return (A >= static_cast<T>(0)) ? A : -A;
		}

		/** Return true if value is NaN (not a number). */
		static FORCEINLINE bool IsNaN(float A)
		{
			return ((*(uint32*)& A) & 0x7FFFFFFF) > 0x7F800000;
		}

		/** Return true if value is finite (not NaN and not Infinity). */
		static FORCEINLINE bool IsFinite(float A)
		{
			return ((*(uint32*)& A) & 0x7F800000) != 0x7F800000;
		}

	};

}