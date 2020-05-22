#pragma once

#include "GenericPlatform/GenericPlatformMemory.h"


namespace Nexus
{

	struct CORE_API FLinuxPlatformMemory
		: public FGenericPlatformMemory
	{



	};

	using FPlatformMemory = FLinuxPlatformMemory;

}