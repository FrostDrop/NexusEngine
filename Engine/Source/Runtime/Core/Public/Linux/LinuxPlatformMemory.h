#pragma once

#include "GenericPlatform/GenericPlatformMemory.h"


namespace Nexus
{

	CORE_API struct FLinuxPlatformMemory
		: public FGenericPlatformMemory
	{



	};

	using FPlatformMemory = FLinuxPlatformMemory;

}