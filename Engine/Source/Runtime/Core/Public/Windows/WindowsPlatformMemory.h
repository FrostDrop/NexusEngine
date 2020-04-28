#pragma once

#include "GenericPlatform/GenericPlatformMemory.h"


namespace Nexus
{

	struct CORE_API FWindowsPlatformMemory
		: public FGenericPlatformMemory
	{



	};

	using FPlatformMemory = FWindowsPlatformMemory;

}