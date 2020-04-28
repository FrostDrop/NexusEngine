#pragma once

#include "CoreTypes.h"
#include "MemoryBase.h"


namespace Nexus
{

	/**
	 * Default Ansi malloc.
	 */
	class CORE_API FMallocAnsi : public FMalloc
	{

	public:

		/**
		 * Malloc.
		 */
		virtual void* Malloc(PlatformSizeType Size, uint32 Alignment = DefaultAlignment) override;

		/**
		 * Realloc.
		 */
		virtual void* Realloc(void* Original, PlatformSizeType NewSize, uint32 Alignment = DefaultAlignment) override;

		/**
		 * Free.
		 */
		virtual void Free(void* Original) override;

	private:

		inline PlatformSizeType GetAnsiAllocationSize(void* Original) const;

	};

}