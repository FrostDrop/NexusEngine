#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	/**
	 *
	 */
	template<typename FEncoding>
	struct TInstantiateNullTerminator { static_assert(sizeof(FEncoding) == 0, "Cannot instantiate null termination character of unknown char type."); };

	template<> struct TInstantiateNullTerminator<AnsiChar> { static constexpr const AnsiChar Value = '\0'; };
	template<> struct TInstantiateNullTerminator<WideChar> { static constexpr const WideChar Value = L'\0'; };
	template<> struct TInstantiateNullTerminator<Char16> { static constexpr const Char16 Value = u'\0'; };
	template<> struct TInstantiateNullTerminator<Char32> { static constexpr const Char32 Value = U'\0'; };

}