#pragma once

#include <cmath>

#include "HAL/Platform.h"


namespace Nexus
{

	struct FGenericPlatformMath
	{

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

		/** Computes absolute value in a generic way. */
		template< class T >
		static constexpr FORCEINLINE T Abs(const T A)
		{
			return (A >= static_cast<T>(0)) ? A : -A;
		}

		/** Returns lower value in a generic way. */
		template< class T >
		static constexpr FORCEINLINE T Min(const T A, const T B)
		{
			return (A <= B) ? A : B;
		}

		/** Returns higher value in a generic way. */
		template< class T >
		static constexpr FORCEINLINE T Max(const T A, const T B)
		{
			return (A >= B) ? A : B;
		}

		/** Computes the square root. */
		static FORCEINLINE float Sqrt(float Value) 
		{ 
			return sqrtf(Value); 
		}

		/** Computes a fully accurate inverse square root. */
		static FORCEINLINE float InvSqrt(float F)
		{
			return 1.0f / sqrtf(F);
		}

		/**
		 * Computes A^B.
		 */
		static FORCEINLINE float Pow(float A, float B) 
		{ 
			return powf(A, B); 
		}

		/**
		 * Returns value based on comparand. The main purpose of this function is to avoid
		 * branching based on floating point comparison which can be avoided via compiler
		 * intrinsics.
		 *
		 * Please note that we don't define what happens in the case of NaNs as there might
		 * be platform specific differences.
		 *
		 * @param	Comparand		Comparand the results are based on
		 * @param	ValueGEZero		Return value if Comparand >= 0
		 * @param	ValueLTZero		Return value if Comparand < 0
		 *
		 * @return	ValueGEZero if Comparand >= 0, ValueLTZero otherwise
		 */
		static constexpr FORCEINLINE float FloatSelect(float Comparand, float ValueGEZero, float ValueLTZero)
		{
			return Comparand >= 0.f ? ValueGEZero : ValueLTZero;
		}

	};

}