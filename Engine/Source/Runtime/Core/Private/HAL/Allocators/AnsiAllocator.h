#pragma once

#include "CoreTypes.h"
#include "HAL/Memory.h"


namespace Nexus
{

	/**
	 *
	 */
	class CORE_API FAnsiAllocator
	{

	private:

		using FSizeType = PlatformSizeType;

	public:

		/** 
		 * Default constructor. 
		 */
		FAnsiAllocator()
			: Data(nullptr)
		{

		}

		/** 
		 * Destructor. 
		 */
		FORCEINLINE ~FAnsiAllocator()
		{
			if (Data)
			{
				FMemory::Free(Data);
			}
		}

		/**
		 *
		 */
		void ResizeAllocation(FSizeType PreviousNumElements, FSizeType NumElements, FSizeType NumBytesPerElement)
		{
			if (NumElements)
			{
				void* NewAlloc = FMemory::Realloc(Data, NumElements * NumBytesPerElement);
				Data = NewAlloc;
			}
			else
			{
				FMemory::Free(Data);
				Data = nullptr;
			}
		}

		/**
		 * Gets the address of the allocated memory.
		 */
		FORCEINLINE void* GetAllocation() const
		{
			return Data;
		}

		/**
		 * Checks whether the allocator has allocated memory.
		 */
		FORCEINLINE bool HasAllocation() const
		{
			return !!Data;
		}

	private:

		FAnsiAllocator(const FAnsiAllocator&) = delete;
		FAnsiAllocator& operator=(const FAnsiAllocator&) = delete;

	private:

		void* Data;

	};


}