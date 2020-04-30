#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	/** Tests whether two typenames refer to the same type. */
	template<typename A, typename B>
	struct TAreTypesEqual;

	template<typename, typename>
	struct TAreTypesEqual
	{
		enum { Value = false };
	};

	template<typename A>
	struct TAreTypesEqual<A, A>
	{
		enum { Value = true };
	};

}