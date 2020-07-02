#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	/**
	 * Type trait which yields a signed integer type of a given number of bytes.
	 * If there is no such type, the Type member type will be absent, allowing it to be used in SFINAE contexts.
	 */
	template <PlatformSizeType NumBytes>
	struct TSignedIntType
	{

	};

	template <> struct TSignedIntType<1> { using Type = int8; };
	template <> struct TSignedIntType<2> { using Type = int16; };
	template <> struct TSignedIntType<4> { using Type = int32; };
	template <> struct TSignedIntType<8> { using Type = int64; };


	/**
	 * Type trait which yields an unsigned integer type of a given number of bytes.
	 * If there is no such type, the Type member type will be absent, allowing it to be used in SFINAE contexts.
	 */
	template <PlatformSizeType NumBytes>
	struct TUnsignedIntType
	{

	};

	template <> struct TUnsignedIntType<1> { using Type = uint8; };
	template <> struct TUnsignedIntType<2> { using Type = uint16; };
	template <> struct TUnsignedIntType<4> { using Type = uint32; };
	template <> struct TUnsignedIntType<8> { using Type = uint64; };

}