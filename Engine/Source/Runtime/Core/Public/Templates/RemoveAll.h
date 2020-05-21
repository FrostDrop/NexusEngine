#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	template<typename T> struct TRemoveAll				{ using Type = T; };
	template<typename T> struct TRemoveAll<const T>		{ using Type = typename TRemoveAll<T>::Type; };
	template<typename T> struct TRemoveAll<T const&>	{ using Type = typename TRemoveAll<T>::Type; };
	template<typename T> struct TRemoveAll<T&>			{ using Type = typename TRemoveAll<T>::Type; };
	template<typename T> struct TRemoveAll<T const*>	{ using Type = typename TRemoveAll<T>::Type; };
	template<typename T> struct TRemoveAll<T*>			{ using Type = typename TRemoveAll<T>::Type; };

}