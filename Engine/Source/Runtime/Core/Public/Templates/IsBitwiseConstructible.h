#pragma once

#include "CoreTypes.h"

#include "IsReferenceType.h"
#include "AreTypesEqual.h"
#include "RemoveConstVolatile.h"
#include "IsTriviallyCopyConstructible.h"

namespace Nexus
{

	template <typename T, typename Arg>
	struct TIsBitwiseConstructible
	{
		static_assert(
			!TIsReferenceType<T>::Value &&
			!TIsReferenceType<Arg>::Value,
			"TIsBitwiseConstructible is not designed to accept reference types.");

		static_assert(
			TAreTypesEqual<T, typename TRemoveConstVolatile<T>::Type>::Value &&
			TAreTypesEqual<Arg, typename TRemoveConstVolatile<Arg>::Type>::Value,
			"TIsBitwiseConstructible is not designed to accept qualified types.");

		enum { Value = false };

	};

	template <typename T>
	struct TIsBitwiseConstructible<T, T>
	{
		// Ts can always be bitwise constructed from itself if it is trivially copyable.
		enum { Value = TIsTriviallyCopyConstructible<T>::Value };
	};

	template <typename T, typename U>
	struct TIsBitwiseConstructible<const T, U> : TIsBitwiseConstructible<T, U>
	{
		// Constructing a const T is the same as constructing a T
	};

	// Const pointers can be bitwise constructed from non-const pointers.
	// This is not true for pointer conversions in general, e.g. where an offset may need to be applied in the case
	// of multiple inheritance, but there is no way of detecting that at compile-time.
	template <typename T>
	struct TIsBitwiseConstructible<const T*, T*>
	{
		// Constructing a const T is the same as constructing a T
		enum { Value = true };
	};

	// Unsigned types can be bitwise converted to their signed equivalents, and vice versa.
	// (assuming two's-complement, which we are)
	template <> struct TIsBitwiseConstructible<uint8, int8>		{ enum { Value = true }; };
	template <> struct TIsBitwiseConstructible< int8, uint8>	{ enum { Value = true }; };
	template <> struct TIsBitwiseConstructible<uint16, int16>	{ enum { Value = true }; };
	template <> struct TIsBitwiseConstructible< int16, uint16>	{ enum { Value = true }; };
	template <> struct TIsBitwiseConstructible<uint32, int32>	{ enum { Value = true }; };
	template <> struct TIsBitwiseConstructible< int32, uint32>	{ enum { Value = true }; };
	template <> struct TIsBitwiseConstructible<uint64, int64>	{ enum { Value = true }; };
	template <> struct TIsBitwiseConstructible< int64, uint64>	{ enum { Value = true }; };

}