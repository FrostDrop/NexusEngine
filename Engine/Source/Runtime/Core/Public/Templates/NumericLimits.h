#pragma once

#include "CoreTypes.h"


/* Numeric constants
*****************************************************************************/

#define MIN_uint8		((uint8)	0x00)
#define	MIN_uint16		((uint16)	0x0000)
#define	MIN_uint32		((uint32)	0x00000000)
#define MIN_uint64		((uint64)	0x0000000000000000)
#define MIN_int8		((int8)		-128)
#define MIN_int16		((int16)	-32768)
#define MIN_int32		((int32)	0x80000000)
#define MIN_int64		((int64)	0x8000000000000000)

#define MAX_uint8		((uint8)	0xff)
#define MAX_uint16		((uint16)	0xffff)
#define MAX_uint32		((uint32)	0xffffffff)
#define MAX_uint64		((uint64)	0xffffffffffffffff)
#define MAX_int8		((int8)		0x7f)
#define MAX_int16		((int16)	0x7fff)
#define MAX_int32		((int32)	0x7fffffff)
#define MAX_int64		((int64)	0x7fffffffffffffff)

#define MIN_float		(1.175494351e-38F)
#define MAX_float		(3.402823466e+38F)
#define MIN_double		(2.2250738585072014e-308)
#define MAX_double		(1.7976931348623158e+308)	

namespace Nexus
{

	/**
	 * Helper class to map a numeric type to its limits.
	 */
	template <typename FNumericType>
	struct TNumericLimits;


	/**
	 * Numeric limits for const types.
	 */
	template <typename FNumericType>
	struct TNumericLimits<const FNumericType>
		: public TNumericLimits<FNumericType>
	{ };


	/**
	 * Numeric limits for volatile types.
	 */
	template <typename FNumericType>
	struct TNumericLimits<volatile FNumericType>
		: public TNumericLimits<FNumericType>
	{ };


	/**
	 * Numeric limits for const volatile types.
	 */
	template <typename FNumericType>
	struct TNumericLimits<const volatile FNumericType>
		: public TNumericLimits<FNumericType>
	{ };


	template<>
	struct TNumericLimits<uint8>
	{

		using FNumericType = uint8;

		static constexpr FNumericType Min()
		{
			return MIN_uint8;
		}

		static constexpr FNumericType Max()
		{
			return MAX_uint8;
		}

		static constexpr FNumericType Lowest()
		{
			return Min();
		}

	};


	template<>
	struct TNumericLimits<uint16>
	{

		using FNumericType = uint16;

		static constexpr FNumericType Min()
		{
			return MIN_uint16;
		}

		static constexpr FNumericType Max()
		{
			return MAX_uint16;
		}

		static constexpr FNumericType Lowest()
		{
			return Min();
		}

	};


	template<>
	struct TNumericLimits<uint32>
	{

		using FNumericType = uint32;

		static constexpr FNumericType Min()
		{
			return MIN_uint32;
		}

		static constexpr FNumericType Max()
		{
			return MAX_uint32;
		}

		static constexpr FNumericType Lowest()
		{
			return Min();
		}

	};


	template<>
	struct TNumericLimits<uint64>
	{

		using FNumericType = uint64;

		static constexpr FNumericType Min()
		{
			return MIN_uint64;
		}

		static constexpr FNumericType Max()
		{
			return MAX_uint64;
		}

		static constexpr FNumericType Lowest()
		{
			return Min();
		}

	};


	template<>
	struct TNumericLimits<int8>
	{

		using FNumericType = int8;

		static constexpr FNumericType Min()
		{
			return MIN_int8;
		}

		static constexpr FNumericType Max()
		{
			return MAX_int8;
		}

		static constexpr FNumericType Lowest()
		{
			return Min();
		}

	};


	template<>
	struct TNumericLimits<int16>
	{

		using FNumericType = int16;

		static constexpr FNumericType Min()
		{
			return MIN_int16;
		}

		static constexpr FNumericType Max()
		{
			return MAX_int16;
		}

		static constexpr FNumericType Lowest()
		{
			return Min();
		}

	};


	template<>
	struct TNumericLimits<int32>
	{

		using FNumericType = int32;

		static constexpr FNumericType Min()
		{
			return MIN_int32;
		}

		static constexpr FNumericType Max()
		{
			return MAX_int32;
		}

		static constexpr FNumericType Lowest()
		{
			return Min();
		}

	};


	template<>
	struct TNumericLimits<int64>
	{

		using FNumericType = int64;

		static constexpr FNumericType Min()
		{
			return MIN_int64;
		}

		static constexpr FNumericType Max()
		{
			return MAX_int64;
		}

		static constexpr FNumericType Lowest()
		{
			return Min();
		}

	};


	template<>
	struct TNumericLimits<float>
	{

		using FNumericType = float;

		static constexpr FNumericType Min()
		{
			return MIN_float;
		}

		static constexpr FNumericType Max()
		{
			return MAX_float;
		}

		static constexpr FNumericType Lowest()
		{
			return -Max();
		}

	};


	template<>
	struct TNumericLimits<double>
	{

		using FNumericType = double;

		static constexpr FNumericType Min()
		{
			return MIN_double;
		}

		static constexpr FNumericType Max()
		{
			return MAX_double;
		}

		static constexpr FNumericType Lowest()
		{
			return -Max();
		}

	};


}