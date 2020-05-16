#pragma once


#include "CoreTypes.h"


namespace Nexus
{

	template<typename T>
	struct TIsTriviallyCopyConstructible
	{

		enum { Value = __has_trivial_copy(T) };

	};

}