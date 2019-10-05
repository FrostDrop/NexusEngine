#pragma once

#include "GenericPlatform/GenericPlatformMath.h"


namespace Nexus
{

	struct FLinuxPlatformMath : public FGenericPlatformMath
	{

	};

	using FPlatformMath = FLinuxPlatformMath;

}