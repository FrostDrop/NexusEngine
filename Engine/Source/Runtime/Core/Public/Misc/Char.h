#pragma once

#include "CoreTypes.h"

#include "Templates/IntType.h"


namespace Nexus
{

	/**
	 *
	 */
	template<typename T>
	struct TLiteral
	{

		static_assert(sizeof(T) == 0, "Cannot select literal of unknown type.");

	};

	/**
	 *
	 */
	template<>
	struct TLiteral<AnsiChar>
	{
		static constexpr const AnsiChar  Select(const AnsiChar  ansi, const WideChar wide) { return ansi; }
		static constexpr const AnsiChar* Select(const AnsiChar* ansi, const WideChar* wide) { return ansi; }
	};

	/**
	 *
	 */
	template<>
	struct TLiteral<WideChar>
	{
		static constexpr const WideChar  Select(const AnsiChar ansi, const WideChar  wide) { return wide; }
		static constexpr const WideChar* Select(const AnsiChar* ansi, const WideChar* wide) { return wide; }
	};

	/**
	 *
	 */
	template<typename FCharType>
	struct TChar
	{

		/**
		 * Only converts ASCII characters, same as CRT to[w]upper() with standard C locale
		 */
		static FORCEINLINE FCharType ToUpper(FCharType Char)
		{
			return static_cast<FCharType>(ToUnsigned(Char) - ((static_cast<uint32>(Char) - 'a' < 26u) << 5));
		}

		/**
		 * Only converts ASCII characters, same as CRT to[w]upper() with standard C locale
		 */
		static FORCEINLINE FCharType ToLower(FCharType Char)
		{
			return static_cast<FCharType>(ToUnsigned(Char) + ((static_cast<uint32>(Char) - 'A' < 26u) << 5));
		}

		/**
		 *
		 */
		static constexpr FORCEINLINE uint32 ToUnsigned(FCharType Char)
		{
			return static_cast<typename TUnsignedIntType<sizeof(FCharType)>::Type>(Char);
		}

	};

}