#pragma once

#include "HAL/PlatformMath.h"


/** Common defines. */
#undef  PI
#define PI 					(3.1415926535897932f)	/* Extra digits if needed: 3.1415926535897932384626433832795f */
#define SMALL_NUMBER		(1.e-8f)
#define KINDA_SMALL_NUMBER	(1.e-4f)

/** Common thresholds. */
#define THRESHOLD_VECTOR_NORMALIZED		(0.01f)		/** Allowed error for a normalized vector (against squared magnitude) */

/** Enable NaN diagnostics. */
#ifndef ENABLE_NAN_DIAGNOSTIC
	#if NEXUS_DEBUG
		#define ENABLE_NAN_DIAGNOSTIC 1
	#else
		#define ENABLE_NAN_DIAGNOSTIC 0
	#endif
#endif


namespace Nexus
{

	struct FMath : public FPlatformMath
	{

		/** Multiplies value by itself. */
		template< class T >
		static FORCEINLINE T Square(const T A)
		{
			return A * A;
		}

		/** Clamps X to be between Min and Max, inclusive */
		template< class T >
		static FORCEINLINE T Clamp(const T X, const T Min, const T Max)
		{
			return X < Min ? Min : X < Max ? X : Max;
		}

	};

}