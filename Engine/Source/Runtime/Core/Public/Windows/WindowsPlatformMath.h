#pragma once

#include <intrin.h>
#include "GenericPlatform/GenericPlatformMath.h"



namespace Nexus
{

	/**
	 *
	 */
	struct FWindowsPlatformMath : public FGenericPlatformMath
	{

		/**
		 *
		 */
		static FORCEINLINE uint32 CountLeadingZeros(uint32 Value)
		{
			unsigned long Log2;
			if (_BitScanReverse(&Log2, Value) != 0)
			{
				return 31 - Log2;
			}

			return 32;
		}

		/**
		 *
		 */
		static FORCEINLINE uint32 CountTrailingZeros(uint32 Value)
		{
			if (Value == 0)
			{
				return 32;
			}

			unsigned long BitIndex;
			_BitScanForward(&BitIndex, Value);

			return BitIndex;
		}

	};

	using FPlatformMath = FWindowsPlatformMath;

}