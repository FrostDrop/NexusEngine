#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	/**
	 * Type trait which returns true if the type T is an array or a reference to an array of ArrType.
	 */
	template <typename T, typename FArrayType>
	struct TIsArrayOrRefTypeOf
	{
		enum { Value = false };
	};

	template <typename ArrType> struct TIsArrayOrRefTypeOf<               ArrType[], ArrType> { enum { Value = true }; };
	template <typename ArrType> struct TIsArrayOrRefTypeOf<const          ArrType[], ArrType> { enum { Value = true }; };
	template <typename ArrType> struct TIsArrayOrRefTypeOf<      volatile ArrType[], ArrType> { enum { Value = true }; };
	template <typename ArrType> struct TIsArrayOrRefTypeOf<const volatile ArrType[], ArrType> { enum { Value = true }; };

	template <typename ArrType, unsigned int N> struct TIsArrayOrRefTypeOf<               ArrType[N], ArrType> { enum { Value = true }; };
	template <typename ArrType, unsigned int N> struct TIsArrayOrRefTypeOf<const          ArrType[N], ArrType> { enum { Value = true }; };
	template <typename ArrType, unsigned int N> struct TIsArrayOrRefTypeOf<      volatile ArrType[N], ArrType> { enum { Value = true }; };
	template <typename ArrType, unsigned int N> struct TIsArrayOrRefTypeOf<const volatile ArrType[N], ArrType> { enum { Value = true }; };

	template <typename ArrType, unsigned int N> struct TIsArrayOrRefTypeOf<               ArrType(&)[N], ArrType> { enum { Value = true }; };
	template <typename ArrType, unsigned int N> struct TIsArrayOrRefTypeOf<const          ArrType(&)[N], ArrType> { enum { Value = true }; };
	template <typename ArrType, unsigned int N> struct TIsArrayOrRefTypeOf<      volatile ArrType(&)[N], ArrType> { enum { Value = true }; };
	template <typename ArrType, unsigned int N> struct TIsArrayOrRefTypeOf<const volatile ArrType(&)[N], ArrType> { enum { Value = true }; };

}