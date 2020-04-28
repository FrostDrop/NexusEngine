#pragma once

#include <memory>

#include "CoreTypes.h"


namespace Nexus
{

	/**
	 *
	 */
	struct CORE_API FGenericPlatformMemory
	{

		/**
		 *
		 */
		static FORCEINLINE void* Memcpy(void* Dest, const void* Src, PlatformSizeType Count)
		{
			return memcpy(Dest, Src, Count);
		}

	};

}