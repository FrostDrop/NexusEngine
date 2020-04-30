#pragma once

#include "CoreTypes.h"

#include "HAL/Allocators/AnsiAllocator.h"

#include "Templates/IsBitwiseConstructible.h"
#include "Templates/IsTriviallyDestructable.h"
#include "Templates/Forward.h"

namespace Nexus
{

	template<typename FElementType, typename FAllocator = FAnsiAllocator>
	class TArray
	{

	private:

		template <typename FOtherElementType, typename FOtherAllocator>
		friend class TArray;

		using FSizeType = typename FAllocator::FSizeType;

	public:

		// Constructors.

		/**
		 * Constructor, initializes element number counters.
		 */
		FORCEINLINE TArray(void)
			: ArrayNum(0)
			, ArrayMax(0)
		{
		}

		/**
		 * Constructor from a raw array of elements.
		 *
		 * @param Ptr   A pointer to an array of elements to copy.
		 * @param Count The number of elements to copy from Ptr.
		 */
		FORCEINLINE TArray(const FElementType* Ptr, FSizeType Count)
		{
			CopyToEmpty(Ptr, Count, 0, 0);
		}

		/**
		 * Initializer list constructor.
		 */
		TArray(const std::initializer_list<FElementType>& InitList)
		{
			CopyToEmpty(InitList.begin(), static_cast<FSizeType>(InitList.size()), 0, 0);
		}

		/**
		 * Copy constructor. Use the common routine to perform the copy.
		 *
		 * @param Other The source array to copy.
		 */
		FORCEINLINE TArray(const TArray& Other)
		{
			CopyToEmpty(Other.GetData(), Other.Num(), 0, 0);
		}

		/**
		 * Copy constructor with changed allocator. Use the common routine to perform the copy.
		 *
		 * @param Other The source array to copy.
		 */
		template <typename FOtherElementType, typename FOtherAllocator>
		FORCEINLINE explicit TArray(const TArray<FOtherElementType, FOtherAllocator>& Other)
		{
			CopyToEmpty(Other.GetData(), Other.Num(), 0, 0);
		}

		/**
		 * Move constructor.
		 *
		 * @param Other Array to move from.
		 */
		FORCEINLINE TArray(TArray&& Other)
		{

		}

		/**
		 * Move constructor.
		 *
		 * @param Other Array to move from.
		 */
		template <typename OtherElementType, typename OtherAllocator>
		FORCEINLINE explicit TArray(TArray<OtherElementType, OtherAllocator>&& Other);

		/** 
		 * Destructor. 
		 */
		inline ~TArray()
		{
			DestructItems(GetData(), ArrayNum);
		}

	public:

		// Operators.

		/**
		 * Initializer list assignment operator. First deletes all currently contained elements
		 * and then copies from initializer list.
		 *
		 * @param InitList The initializer_list to copy from.
		 */
		TArray& operator=(const std::initializer_list<FElementType>& InitList);

		/**
		 * Assignment operator. First deletes all currently contained elements
		 * and then copies from other array.
		 *
		 * @param Other The source array to assign from.
		 */
		TArray& operator=(const TArray& Other);

		/**
		 * Assignment operator. First deletes all currently contained elements
		 * and then copies from other array.
		 *
		 * Allocator changing version.
		 *
		 * @param Other The source array to assign from.
		 */
		template<typename OtherAllocator>
		TArray& operator=(const TArray<FElementType, OtherAllocator>& Other);

		/**
		 * Move assignment operator.
		 *
		 * @param Other Array to assign and move from.
		 */
		TArray& operator=(TArray&& Other);

	public:

		// Index operators.

		/**
		 * Array bracket operator. Returns reference to element at give index.
		 *
		 * @returns Reference to indexed element.
		 */
		FORCEINLINE FElementType& operator[](FSizeType Index)
		{
			return GetData()[Index];
		}

		/**
		 * Array bracket operator. Returns reference to element at give index.
		 *
		 * Const version of the above.
		 *
		 * @returns Reference to indexed element.
		 */
		FORCEINLINE const FElementType& operator[](FSizeType Index) const
		{
			return GetData()[Index];
		}

	public:

		// Content modifier functions.

		/**
		 * Adds a new item to the end of the array, possibly reallocating the whole array to fit.
		 *
		 * @param Item The item to add
		 * @return Index to the new item
		 * @see AddDefaulted, AddUnique, AddZeroed, Append, Insert
		 */
		FORCEINLINE FSizeType Add(const FElementType& Item)
		{
			return Emplace(Item);
		}

		/**
		 * Constructs a new item at the end of the array, possibly reallocating the whole array to fit.
		 *
		 * @param Args	The arguments to forward to the constructor of the new item.
		 * @return		Index to the new item
		 */
		template <typename... FArgsType>
		FORCEINLINE FSizeType Emplace(FArgsType&&... Args)
		{
			const FSizeType Index = AddUninitialized(1);

			new(GetData() + Index) FElementType(TForward<FArgsType>(Args)...);
			return Index;
		}

		/**
		 * Adds a given number of uninitialized elements into the array.
		 *
		 * Caution, AddUninitialized() will create elements without calling
		 * the constructor and this is not appropriate for element types that
		 * require a constructor to function properly.
		 *
		 * @param Count Number of elements to add.
		 * @returns Number of elements in array before addition.
		 */
		FORCEINLINE FSizeType AddUninitialized(FSizeType Count = 1)
		{
			const FSizeType OldNum = ArrayNum;

			if ((ArrayNum += Count) > ArrayMax)
			{
				ResizeGrow(OldNum);
			}

			return OldNum;
		}

	public:

		// Simple functions.

		/**
		 * Helper function for returning a typed pointer to the first array entry.
		 *
		 * @returns Pointer to first array entry or nullptr if ArrayMax == 0.
		 */
		FORCEINLINE FElementType* GetData()
		{
			return static_cast<FElementType*>(AllocatorInstance.GetAllocation());
		}

		/**
		 * Returns number of elements in array.
		 *
		 * @returns Number of elements in array.
		 * @see GetSlack
		 */
		FORCEINLINE FSizeType Num() const
		{
			return ArrayNum;
		}

		/**
		 * Helper function returning the size of the inner type.
		 *
		 * @returns Size in bytes of array type.
		 */
		FORCEINLINE uint32 GetTypeSize() const
		{
			return sizeof(FElementType);
		}

		/**
		 * Helper function to return the amount of memory allocated by this container.
		 * Only returns the size of allocations made directly by the container, not the elements themselves.
		 *
		 * @returns Number of bytes allocated by this container.
		 */
		FORCEINLINE PlatformSizeType GetAllocatedSize(void) const
		{
			return AllocatorInstance.GetAllocatedSize(ArrayMax, sizeof(FElementType));
		}

		/**
		 * Returns the amount of slack in this array in elements.
		 */
		FORCEINLINE FSizeType GetSlack() const
		{
			return ArrayMax - ArrayNum;
		}

	private:

		// Memory functions.

		/**
		 *
		 */
		FORCENOINLINE void ResizeGrow(FSizeType OldNum)
		{
			ArrayMax = AllocatorInstance.CalculateSlackGrow(ArrayNum, ArrayMax, sizeof(FElementType));
			AllocatorInstance.ResizeAllocation(OldNum, ArrayMax, sizeof(FElementType));
		}

		/**
		 *
		 */
		FORCENOINLINE void ResizeForCopy(FSizeType NewMax, FSizeType PrevMax)
		{
			if (NewMax != PrevMax)
			{
				AllocatorInstance.ResizeAllocation(0, NewMax, sizeof(FElementType));
			}

			ArrayMax = NewMax;
		}

		/**
		 * Constructs a range of items into memory from a set of arguments.  The arguments come from an another array.
		 *
		 * @param	Dest		The memory location to start copying into.
		 * @param	Source		A pointer to the first argument to pass to the constructor.
		 * @param	Count		The number of elements to copy.
		 */
		template <typename FDestinationElementType, typename FSourceElementType>
		FORCEINLINE void ConstructItems(void* Dest, const FSourceElementType* Source, FSizeType Count)
		{
			if constexpr (TIsBitwiseConstructible<FDestinationElementType, FSourceElementType>::Value)
			{
				FMemory::Memcpy(Dest, Source, sizeof(FSourceElementType) * Count);
			}
			else
			{
				while (Count)
				{
					new (Dest) FDestinationElementType(*Source);
					++(FDestinationElementType*&)Dest;

					++Source;
					--Count;
				}
			}
		}

		/**
		 * Destructs a range of items in memory.
		 *
		 * @param	Elements	A pointer to the first item to destruct.
		 * @param	Count		The number of elements to destruct.
		 *
		 * @note: This function is optimized for values of T, and so will not dynamically dispatch destructor calls if T's destructor is virtual.
		 */
		FORCEINLINE void DestructItems(FElementType* Element, FSizeType Count)
		{
			if constexpr (!TIsTriviallyDestructible<FElementType>::Value)
			{
				while (Count)
				{
					using FDestructItemsElementType = FElementType;
					Element->FDestructItemsElementType::~FDestructItemsElementType();

					++Element;
					--Count;
				}
			}
		}

		/**
		 * Copies data from one array into this array. Uses the fast path if the
		 * data in question does not need a constructor.
		 *
		 * @param Source The source array to copy
		 * @param PrevMax The previous allocated size
		 * @param ExtraSlack Additional amount of memory to allocate at
		 *                   the end of the buffer. Counted in elements. Zero by
		 *                   default.
		 */
		template <typename FOtherElementType, typename FOtherSizeType>
		void CopyToEmpty(const FOtherElementType* OtherData, FOtherSizeType OtherNum, FSizeType PrevMax, FSizeType ExtraSlack)
		{
			FSizeType NewNum = OtherNum;
			ArrayNum = NewNum;

			if (OtherNum || ExtraSlack || PrevMax)
			{
				ResizeForCopy(NewNum + ExtraSlack, PrevMax);
				ConstructItems<FElementType, FOtherElementType>(GetData(), OtherData, OtherNum);
			}
			else
			{
				ArrayMax = 0;
			}
		}

	private:

		FAllocator AllocatorInstance;

		FSizeType ArrayNum;
		FSizeType ArrayMax;

	};

}