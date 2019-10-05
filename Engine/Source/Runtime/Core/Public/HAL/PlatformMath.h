#pragma once

#include "GenericPlatform/GenericPlatformMath.h"


#if NEXUS_PLATFORM_WINDOWS
	#include "Windows/WindowsPlatformMath.h"
#elif NEXUS_PLATFORM_LINUX
	#include "Linux/LinuxPlatformMath.h"
#elif NEXUS_PLATFORM_MAC
	#include "Mac/MacPlatformMath.h"
#else
	#error Unknown platform
#endif