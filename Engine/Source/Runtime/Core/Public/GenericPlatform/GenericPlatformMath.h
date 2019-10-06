#pragma once

#include <cmath>

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

		/** Returns higher value in a generic way. */
		template< class T >
		static constexpr FORCEINLINE T Max(const T A, const T B)
		{
			return (A >= B) ? A : B;
		}

		/** Returns lower value in a generic way. */
		template< class T >
		static constexpr FORCEINLINE T Min(const T A, const T B)
		{
			return (A <= B) ? A : B;
		}

		/** Computes the square root. */
		static FORCEINLINE float Sqrt(float Value) 
		{ 
			return sqrtf(Value); 
		}

		/** Computes a fully accurate inverse square root */
		static FORCEINLINE float InvSqrt(float F)
		{
			return 1.0f / sqrtf(F);
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