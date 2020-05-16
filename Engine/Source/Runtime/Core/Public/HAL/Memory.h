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
		static PlatformSizeType QuantizeSize(PlatformSizeType Size, uint32 Alignment = DefaultAlignment);

		/**
		 *
		 */
		static FORCEINLINE void* Memcpy(void* Dest, const void* Src, PlatformSizeType Size);

		/**
		 *
		 */
		static FORCEINLINE void* Memmove(void* Dest, const void* Src, PlatformSizeType Size);

		/**
		 *
		 */
		static FORCEINLINE int32 Memcmp(const void* Buffer1, const void* Buffer2, PlatformSizeType Size);


	};

}

#include "Memory.inl"