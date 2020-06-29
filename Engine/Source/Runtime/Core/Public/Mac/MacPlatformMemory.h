#pragma once


#include "GenericPlatform/GenericPlatformMemory.h"

namespace Nexus
{

	CORE_API struct FMacPlatformMemory
		: public FGenericPlatformMemory
	{



	};

	using FPlatformMemory = FMacPlatformMemory;

}