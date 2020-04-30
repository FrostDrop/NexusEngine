#pragma once

#include "CoreTypes.h"
#include "Templates/RemoveReference.h"

namespace Nexus
{

	/**
	 * Forward will cast a reference to an rvalue reference.
	 * This is Nexus' equivalent of std::forward.
	 */
	template <typename T>
	FORCEINLINE T&& TForward(typename TRemoveReference<T>::Type& Obj)
	{
		return (T&&)Obj;
	}

	template <typename T>
	FORCEINLINE T&& TForward(typename TRemoveReference<T>::Type&& Obj)
	{
		return (T&&)Obj;
	}

}