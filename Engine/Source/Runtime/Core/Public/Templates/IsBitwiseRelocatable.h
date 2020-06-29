#pragma once

#include "CoreTypes.h"

#include "AndOrNot.h"
#include "AreTypesEqual.h"
#include "IsBitwiseConstructible.h"
#include "IsTriviallyDestructable.h"

namespace Nexus
{

	template <typename DestinationElementType, typename SourceElementType>
	struct TIsBitwiseRelocatable
	{
		enum
		{
			Value =
			TOr<
				TAreTypesEqual<DestinationElementType, SourceElementType>,
				TAnd<
					TIsBitwiseConstructible<DestinationElementType, SourceElementType>,
					TIsTriviallyDestructible<SourceElementType>
				>
			>::Value
		};
	};

}