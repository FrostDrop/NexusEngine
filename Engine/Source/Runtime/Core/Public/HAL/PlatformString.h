#pragma once

#include "GenericPlatform/GenericPlatformString.h"

#if NEXUS_PLATFORM_WINDOWS
	#include "Windows/WindowsPlatformString.h"
#elif NEXUS_PLATFORM_LINUX
	#include "Linux/LinuxPlatformString.h"
#elif NEXUS_PLATFORM_MAC
	#include "Mac/MacPlatformString.h"
#else
	#error Unknown platform
#endif