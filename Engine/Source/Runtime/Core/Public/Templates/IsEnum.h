#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	/**
	 *
	 */
	template <typename T>
	struct TIsEnum
	{
		enum { Value = __is_enum(T) };
	};

}