#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	template<bool bPredicate, typename FTrueType, typename FFalseType>
	struct TSelectType;

	template<typename FTrueType, typename FFalseType>
	struct TSelectType<true, FTrueType, FFalseType>
	{
		using Type = FTrueType;
	};

	template<typename FTrueType, typename FFalseType>
	struct TSelectType<false, FTrueType, FFalseType>
	{
		using Type = FFalseType;
	};

}