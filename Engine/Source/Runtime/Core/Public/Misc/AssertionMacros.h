#pragma once

#include <cassert>

#if NEXUS_DEBUG
	#define Check(Expression) assert(Expression)
#elif NEXUS_RELEASE
	#define Check(Expression)
#elif NEXUS_DISTRIBUTION
	#define Check(Expression)
#endif