#pragma once

#include "CoreTypes.h"
#include "HAL/Memory.h"

#include "Templates/NumericLimits.h"

namespace Nexus
{

	/**
	 *
	 */
	class FAnsiAllocator
	{

	public:

		using FSizeType = uint32;

	public:

		/** 
		 * Default constructor. 
		 */
		FORCEINLINE FAnsiAllocator(void)
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
		void ResizeAllocation(FSizeType PreviousNumElements, FSizeType NumElements, PlatformSizeType NumBytesPerElement)
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
		* Moves the state of another allocator into this one.
		* Assumes that the allocator is currently empty, i.e. memory may be allocated but any existing elements have already been destructed (if necessary).
		* @param Other - The allocator to move the state from.  This allocator should be left in a valid empty state.
		*/
		FORCEINLINE void MoveToEmpty(FAnsiAllocator& Other)
		{
			// Check(this != &Other);

			if (Data)
			{
				FMemory::Free(Data);
			}

			Data = Other.Data;
			Other.Data = nullptr;
		}

		FSizeType CalculateSlackGrow(FSizeType NumElements, FSizeType NumAllocatedElements, PlatformSizeType NumBytesPerElement) const
		{
#if AGGRESSIVE_MEMORY_SAVING
			const PlatformSizeType FirstGrow = 1;
			const PlatformSizeType ConstantGrow = 0;
#else
			const PlatformSizeType FirstGrow = 4;
			const PlatformSizeType ConstantGrow = 16;
#endif

			FSizeType Result;
			FSizeType Grow = FirstGrow;

			if (NumAllocatedElements || FSizeType(NumElements) > Grow)
			{
				Grow = FSizeType(NumElements) + 3 * FSizeType(NumElements) / 8 + ConstantGrow;
			}
			
			Result = Grow;
			if (NumElements > Result)
			{
				Result = TNumericLimits<FSizeType>::Max();
			}

			return Result;
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