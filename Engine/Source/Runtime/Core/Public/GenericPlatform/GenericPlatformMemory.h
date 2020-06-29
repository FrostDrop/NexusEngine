#pragma once

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

		/**
		 *
		 */
		static FORCEINLINE void* Memmove(void* Dest, const void* Src, PlatformSizeType Count)
		{
			return memmove(Dest, Src, Count);
		}

		/**
		 *
		 */
		static FORCEINLINE void* Memset(void* Dest, uint8 Char, PlatformSizeType Size)
		{
			return memset(Dest, Char, Size);
		}

		/**
		 *
		 */
		static FORCEINLINE void* Memzero(void* Dest, PlatformSizeType Size)
		{
			return memset(Dest, 0, Size);
		}

		/**
		 *
		 */
		static FORCEINLINE int32 Memcmp(const void* Buffer1, const void* Buffer2, PlatformSizeType Count)
		{
			return memcmp(Buffer1, Buffer2, Count);
		}

	};

}