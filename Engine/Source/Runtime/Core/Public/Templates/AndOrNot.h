#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	template <typename... FTypes>
	struct TAnd;

	template <bool LHSValue, typename... FRHS>
	struct TAndValue
	{
		enum { Value = TAnd<FRHS...>::Value };
	};

	template <typename... FRHS>
	struct TAndValue<false, FRHS...>
	{
		enum { Value = false };
	};

	template <typename FLHS, typename... FRHS>
	struct TAnd<FLHS, FRHS...> : TAndValue<FLHS::Value, FRHS...>
	{
	};

	template <>
	struct TAnd<>
	{
		enum { Value = true };
	};


	template <typename... FTypes>
	struct TOr;

	template <bool LHSValue, typename... FRHS>
	struct TOrValue
	{
		enum { Value = TOr<FRHS...>::Value };
	};

	template <typename... FRHS>
	struct TOrValue<true, FRHS...>
	{
		enum { Value = true };
	};

	template <typename FLHS, typename... FRHS>
	struct TOr<FLHS, FRHS...> : TOrValue<FLHS::Value, FRHS...>
	{
	};

	template <>
	struct TOr<>
	{
		enum { Value = false };
	};


	template <typename FType>
	struct TNot
	{
		enum { Value = !FType::Value };
	};

}