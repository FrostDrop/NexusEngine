#pragma once


namespace Nexus
{

	/**
	 *
	 */
	enum EMemoryAlignment
	{

		/**
		 *
		 */
		DefaultAlignment = 0

	};

	/** Global memory allocator. */
	CORE_API extern class FMalloc* GMalloc;

	/**
	 *
	 */
	class CORE_API FMalloc
	{

	public:

		/**
		 * Malloc.
		 */
		virtual void* Malloc(PlatformSizeType Size, uint32 Alignment = DefaultAlignment) = 0;

		/**
		 * Realloc.
		 */
		virtual void* Realloc(void* Original, PlatformSizeType NewSize, uint32 Alignment = DefaultAlignment) = 0;

		/**
		 * Free.
		 */
		virtual void Free(void* Original) = 0;

		/**
		 *
		 */
		virtual PlatformSizeType QuantizeSize(PlatformSizeType Size, uint32 Alignment = DefaultAlignment)
		{
			return Size;
		}

	};


}