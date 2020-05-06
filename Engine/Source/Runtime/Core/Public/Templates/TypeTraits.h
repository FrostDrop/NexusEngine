#pragma once

#include "CoreTypes.h"

#include "IsEnum.h"
#include "IsPointer.h"
#include "IsArithmetic.h"
#include "AndOrNot.h"

namespace Nexus
{

	/**
	 * Helper for array traits. Provides a common base to more easily refine a portion of the traits
	 * when specializing. Mainly used by MemoryOps.h which is used by the contiguous storage containers like TArray.
	 */
	template<typename T>
	struct TTypeTraits
	{

		// There's no good way of detecting this so we'll just assume it to be true for certain known types and expect
		// users to customize it for their custom types.
		enum { IsBytewiseComparable = TOr<TIsEnum<T>, TIsArithmetic<T>, TIsPointer<T>>::Value };

	};

}