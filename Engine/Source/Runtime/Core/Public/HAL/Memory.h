#pragma once

#include "CoreTypes.h"
#include "MemoryBase.h"

namespace Nexus
{

	/**
	 *
	 */
	struct FMemory
	{

		/**
		 *
		 */
		static void* Malloc(PlatformSizeType Size, uint32 Alignment = DefaultAlignment);

		/**
		 *
		 */
		static void* Realloc(void* Original, PlatformSizeType Size, uint32 Alignment = DefaultAlignment);

		/**
		 *
		 */
		static void Free(void* Original);

		/**
		 *
		 */
		static FORCEINLINE void* Memcpy(void* Dest, const void* Src, PlatformSizeType Size);

	};

}

#include "Memory.inl"