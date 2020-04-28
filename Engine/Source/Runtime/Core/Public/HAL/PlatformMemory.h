#pragma once


/** Include platform memory headers. */
#if NEXUS_PLATFORM_WINDOWS
	#include "Windows/WindowsPlatformMemory.h"
#elif NEXUS_PLATFORM_LINUX
	#include "Linux/LinuxPlatformMemory.h"
#elif NEXUS_PLATFORM_MAC
	#include "Mac/MacPlatformMemory.h"
#else
	#error Unknown platform
#endif