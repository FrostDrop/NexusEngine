#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	/**
	 *
	 */
	template<typename T>
	struct TIsFixedWidthEncoding { enum { Value = false }; };

	template<> struct TIsFixedWidthEncoding<AnsiChar> { enum { Value = true }; };
	template<> struct TIsFixedWidthEncoding<WideChar> { enum { Value = true }; };
	template<> struct TIsFixedWidthEncoding<Char16> { enum { Value = true }; };
	template<> struct TIsFixedWidthEncoding<Char32> { enum { Value = true }; };

}