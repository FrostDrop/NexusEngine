#pragma once

#include "CoreTypes.h"

#include "RemoveReference.h"
#include "IsLValueReference.h"

namespace Nexus
{

	/**
	 * Forward will cast a reference to an rvalue reference.
	 * This is Nexus' equivalent of std::forward.
	 */
	template <typename T>
	FORCEINLINE T&& TForward(typename TRemoveReference<T>::Type& Obj)
	{
		static_assert(!TIsLValueReferenceType<T>::Value, "Cannot forward lvalue reference.");
		return static_cast<T&&>(Obj);
	}

	template <typename T>
	FORCEINLINE T&& TForward(typename TRemoveReference<T>::Type&& Obj)
	{
		static_assert(!TIsLValueReferenceType<T>::Value, "Cannot forward lvalue reference.");
		return static_cast<T&&>(Obj);
	}

}