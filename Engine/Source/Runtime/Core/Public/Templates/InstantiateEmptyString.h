#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	/**
	 *
	 */
	template<typename FEncoding>
	struct TInstantiateEmptyString { static_assert(sizeof(FEncoding) == 0, "Cannot instantiate empty string of unknown char type."); };

	template<> struct TInstantiateEmptyString<AnsiChar> { static constexpr const AnsiChar* Value = ""; };
	template<> struct TInstantiateEmptyString<WideChar> { static constexpr const WideChar* Value = L""; };
	template<> struct TInstantiateEmptyString<Char16>	{ static constexpr const Char16* Value = u""; };
	template<> struct TInstantiateEmptyString<Char32>	{ static constexpr const Char32* Value = U""; };

}