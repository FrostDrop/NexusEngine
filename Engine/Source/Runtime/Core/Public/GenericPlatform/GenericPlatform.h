#pragma once


namespace Nexus
{

	struct FGenericPlatformTypes
	{

		/** Unsigned base types. */
		using uint8 = unsigned char;
		using uint16 = unsigned short;
		using uint32 = unsigned int;
		using uint64 = unsigned long long;

		/** Signed base types. */
		using int8 = signed char;
		using int16 = signed short;
		using int32 = signed int;
		using int64 = signed long long;

		/** Character types. */
		using AnsiChar = char;
		using WideChar = wchar_t;
		using Char8 = char;
		using Char16 = char16_t;
		using Char32 = char32_t;

	};

}