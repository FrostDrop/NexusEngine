#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	/**
	 * Includes a function in an overload set if the predicate is true.  It should be used similarly to this:
	 *
	 * // This function will only be instantiated if SomeTrait<T>::Value is true for a particular T
	 * template <typename T>
	 * typename TEnableIf<SomeTrait<T>::Value, ReturnType>::Type Function(const T& Obj)
	 * {
	 *     ...
	 * }
	 *
	 * ReturnType is the real return type of the function.
	 */
	template <bool Predicate, typename FResult = void>
	class TEnableIf;

	/**
	 *
	 */
	template <typename FResult>
	class TEnableIf<true, FResult>
	{

	public:
		typedef FResult Type;

	};

	/**
	 *
	 */
	template <typename FResult>
	class TEnableIf<false, FResult>
	{ };

}