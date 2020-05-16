#pragma once

#include "CoreTypes.h"
#include "Math/MathUtility.h"

#include "HAL/Allocators/AnsiAllocator.h"


#define NUM_BITS_PER_DWORD static_cast<uint32>(32)
#define NUM_BITS_PER_DWORD_LOG_TWO static_cast<uint32>(5)


namespace Nexus
{

	/** 
	 * Used to read/write a bit in the array as a bool. 
	 */
	class FBitReference
	{

	public:

		/**
		 *
		 */
		FORCEINLINE FBitReference(uint32& InData, uint32 InMask)
			: Data(InData)
			, Mask(InMask)
		{
		}

		/**
		 *
		 */
		FORCEINLINE operator bool() const
		{
			return (Data & Mask) != 0;
		}

		/**
		 *
		 */
		FORCEINLINE void operator=(const bool bNewValue)
		{
			if (bNewValue)
			{
				Data |= Mask;
			}
			else
			{
				Data &= ~Mask;
			}
		}

		/**
		 *
		 */
		FORCEINLINE void operator|=(const bool bNewValue)
		{
			if (bNewValue)
			{
				Data |= Mask;
			}
		}

		/**
		 *
		 */
		FORCEINLINE void operator&=(const bool bNewValue)
		{
			if (!bNewValue)
			{
				Data &= ~Mask;
			}
		}
		
		/**
		 *
		 */
		FORCEINLINE FBitReference& operator=(const FBitReference& Copy)
		{
			*this = static_cast<bool>(Copy);
			return *this;
		}

	private:

		/**
		 *
		 */
		uint32& Data;

		/**
		 *
		 */
		uint32 Mask;

	};

	/**
	 *
	 */
	class FConstBitReference
	{

	public:

		/**
		 *
		 */
		FORCEINLINE FConstBitReference(const uint32& InData, uint32 InMask)
			: Data(InData)
			, Mask(InMask)
		{

		}

		/**
		 *
		 */
		FORCEINLINE operator bool() const
		{
			return (Data & Mask) != 0;
		}

	private:

		/**
		 *
		 */
		const uint32& Data;

		/**
		 *
		 */
		uint32 Mask;

	};

	/**
	 *
	 */
	class FRelativeBitReference
	{

	public:

		/**
		 *
		 */
		FORCEINLINE explicit FRelativeBitReference(uint32 BitIndex)
			: DwordIndex(BitIndex >> NUM_BITS_PER_DWORD_LOG_TWO)
			, Mask(1 << (BitIndex & (NUM_BITS_PER_DWORD - 1)))
		{
		}

		uint32  DwordIndex;
		uint32 Mask;
	};

	template<typename FAllocator = FAnsiAllocator>
	class TBitArray
	{

	public:

		//////////////////////////////////////////////////
		// Iterators. ////////////////////////////////////
		//////////////////////////////////////////////////

		/** 
		 * BitArray iterator. 
		 */
		class FIterator : public FRelativeBitReference
		{

		public:

			/**
			 *
			 */
			FORCEINLINE FIterator(TBitArray<FAllocator>& InArray, uint32 StartIndex = 0)
				: FRelativeBitReference(StartIndex)
				, Array(InArray)
				, Index(StartIndex)
			{
			}

			/**
			 *
			 */
			FORCEINLINE FIterator& operator++()
			{
				++Index;
				this->Mask <<= 1;

				if (!this->Mask)
				{
					this->Mask = 1;
					++this->DwordIndex;
				}

				return *this;
			}
			
			/**
			 *
			 */
			FORCEINLINE explicit operator bool() const
			{
				return Index < Array.Num();
			}
			
			/**
			 *
			 */
			FORCEINLINE bool operator !() const
			{
				return !(bool)*this;
			}

			/**
			 *
			 */
			FORCEINLINE FBitReference GetValue() const 
			{ 
				return FBitReference(Array.GetData()[this->DwordIndex], this->Mask); 
			}

			/**
			 *
			 */
			FORCEINLINE uint32 GetIndex() const 
			{ 
				return Index; 
			}

		private:

			TBitArray<FAllocator>& Array;
			uint32 Index;
		};

		/** 
		 * Const BitArray iterator. 
		 */
		class FConstIterator : public FRelativeBitReference
		{

		public:

			/**
			 *
			 */
			FORCEINLINE FConstIterator(const TBitArray<FAllocator>& InArray, uint32 StartIndex = 0)
				: FRelativeBitReference(StartIndex)
				, Array(InArray)
				, Index(StartIndex)
			{
			}

			/**
			 *
			 */
			FORCEINLINE FConstIterator& operator++()
			{
				++Index;
				this->Mask <<= 1;

				if (!this->Mask)
				{
					this->Mask = 1;
					++this->DwordIndex;
				}

				return *this;
			}

			/**
			 *
			 */
			FORCEINLINE explicit operator bool() const
			{
				return Index < Array.Num();
			}
			
			/**
			 *
			 */
			FORCEINLINE bool operator !() const
			{
				return !(bool)*this;
			}

			/**
			 *
			 */
			FORCEINLINE FConstBitReference GetValue() const 
			{ 
				return FConstBitReference(Array.GetData()[this->DwordIndex], this->Mask); 
			}

			/**
			 *
			 */
			FORCEINLINE uint32 GetIndex() const 
			{ 
				return Index; 
			}

		private:

			const TBitArray<FAllocator>& Array;
			uint32 Index;

		};

		/** 
		 * Const reverse iterator. 
		 */
		class FConstReverseIterator : public FRelativeBitReference
		{

		public:

			/**
			 *
			 */
			FORCEINLINE FConstReverseIterator(const TBitArray<FAllocator>& InArray)
				: FRelativeBitReference(InArray.Num() - 1)
				, Array(InArray)
				, Index(InArray.Num() - 1)
			{
			}

			/**
			 *
			 */
			FORCEINLINE FConstReverseIterator& operator++()
			{
				--Index;
				this->Mask >>= 1;

				if (!this->Mask)
				{
					this->Mask = (1 << (NUM_BITS_PER_DWORD - 1));
					--this->DwordIndex;
				}

				return *this;
			}

			/**
			 *
			 */
			FORCEINLINE explicit operator bool() const
			{
				return Index >= 0;
			}
			
			/**
			 *
			 */
			FORCEINLINE bool operator !() const
			{
				return !(bool)*this;
			}

			/**
			 *
			 */
			FORCEINLINE FConstBitReference GetValue() const 
			{ 
				return FConstBitReference(Array.GetData()[this->DwordIndex], this->Mask); 
			}

			/**
			 *
			 */
			FORCEINLINE int32 GetIndex() const 
			{ 
				return Index; 
			}

		private:

			const TBitArray<FAllocator>& Array;
			int32 Index;

		};

	public:

		//////////////////////////////////////////////////
		// Constructors. /////////////////////////////////
		//////////////////////////////////////////////////

		/**
		 * Minimal initialization constructor.
		 * @param Value - The value to initial the bits to.
		 * @param InNumBits - The initial number of bits in the array.
		 */
		explicit TBitArray(const bool Value = false, const uint32 InNumBits = 0)
			: NumBits(0)
			, MaxBits(0)
		{
			Init(Value, InNumBits);
		}


	public:

		/**
		 *
		 */
		FORCEINLINE FBitReference operator[](uint32 Index)
		{
			Check(Index < NumBits);

			return FBitReference(
				GetData()[Index / NUM_BITS_PER_DWORD],
				1 << (Index & (NUM_BITS_PER_DWORD - 1))
			);
		}

		/**
		 *
		 */
		FORCEINLINE const FConstBitReference operator[](uint32 Index) const
		{
			Check(Index < NumBits);

			return FConstBitReference(
				GetData()[Index / NUM_BITS_PER_DWORD],
				1 << (Index & (NUM_BITS_PER_DWORD - 1))
			);
		}

	public:

		//////////////////////////////////////////////////
		// Basic memory operations. //////////////////////
		//////////////////////////////////////////////////

		/**
		 * Resets the array's contents.
		 * @param Value - The value to initial the bits to.
		 * @param NumBits - The number of bits in the array.
		 */
		void Init(bool bValue, uint32 InNumBits)
		{
			Empty(InNumBits);
			if (InNumBits)
			{
				NumBits = InNumBits;
				FMemory::Memset(GetData(), bValue ? 0xff : 0, FMath::DivideAndRoundUp(NumBits, NUM_BITS_PER_DWORD) * sizeof(uint32));
			}
		}

		/**
		 * Reserves memory such that the array can contain at least Number bits.
		 *
		 * @Number  The number of bits to reserve space for.
		 */
		void Reserve(uint32 Number)
		{
			if (Number > MaxBits)
			{
				const uint32 MaxDwords = AllocatorInstance.CalculateSlackGrow(
					FMath::DivideAndRoundUp(Number, NUM_BITS_PER_DWORD),
					FMath::DivideAndRoundUp(MaxBits, NUM_BITS_PER_DWORD),
					sizeof(uint32)
				);

				MaxBits = MaxDwords * NUM_BITS_PER_DWORD;
				Realloc(NumBits);
			}
		}

		/**
		 * Removes all bits from the array, potentially leaving space allocated for an expected number of bits about to be added.
		 * @param ExpectedNumBits - The expected number of bits about to be added.
		 */
		void Empty(uint32 ExpectedNumBits = 0)
		{
			NumBits = 0;

			ExpectedNumBits = FMath::DivideAndRoundUp(ExpectedNumBits, NUM_BITS_PER_DWORD) * NUM_BITS_PER_DWORD;
			if (MaxBits != ExpectedNumBits)
			{
				MaxBits = ExpectedNumBits;
				Realloc(0);
			}
		}

		/**
		 * Removes all bits from the array retaining any space already allocated.
		 */
		void Reset()
		{
			FMemory::Memset(GetData(), 0, FMath::DivideAndRoundUp(NumBits, NUM_BITS_PER_DWORD) * sizeof(uint32));
			NumBits = 0;
		}

		/**
		 * Adds a bit to the array with the given value.
		 * @return The index of the added bit.
		 */
		uint32 Add(const bool bValue)
		{
			const uint32 Index = NumBits;
			Reserve(Index + 1);

			++NumBits;
			(*this)[Index] = bValue;

			return Index;
		}

		/**
		 * Adds multiple bits to the array with the given value.
		 * @return The index of the first added bit.
		 */
		int32 Add(const bool Value, uint32 NumToAdd)
		{
			const uint32 Index = NumBits;

			Reserve(Index + NumToAdd);
			NumBits += NumToAdd;

			for (uint32 It = Index, End = It + NumToAdd; It != End; ++It)
			{
				(*this)[It] = Value;
			}

			return Index;
		}

		/**
		 * Sets or unsets a range of bits within the array.
		 * @param  Index  The index of the first bit to set.
		 * @param  Num    The number of bits to set.
		 * @param  Value  The value to set the bits to.
		 */
		FORCENOINLINE void SetRange(uint32 Index, uint32 Num, bool bValue)
		{
			Check(Index + Num <= NumBits);

			if (Num == 0)
			{
				return;
			}

			// Work out which uint32 index to set from, and how many
			uint32 StartIndex = Index / NUM_BITS_PER_DWORD;
			uint32 Count = (Index + Num + (NUM_BITS_PER_DWORD - 1)) / NUM_BITS_PER_DWORD - StartIndex;

			// Work out masks for the start/end of the sequence
			uint32 StartMask = 0xFFFFFFFFu << (Index % NUM_BITS_PER_DWORD);
			uint32 EndMask = 0xFFFFFFFFu >> (NUM_BITS_PER_DWORD - (Index + Num) % NUM_BITS_PER_DWORD) % NUM_BITS_PER_DWORD;

			uint32* Data = GetData() + StartIndex;
			if (bValue)
			{
				if (Count == 1)
				{
					*Data |= StartMask & EndMask;
				}
				else
				{
					*Data++ |= StartMask;
					Count -= 2;

					while (Count != 0)
					{
						*Data++ = ~0;
						--Count;
					}

					*Data |= EndMask;
				}
			}
			else
			{
				if (Count == 1)
				{
					*Data &= ~(StartMask & EndMask);
				}
				else
				{
					*Data++ &= ~StartMask;
					Count -= 2;

					while (Count != 0)
					{
						*Data++ = 0;
						--Count;
					}

					*Data &= ~EndMask;
				}
			}
		}

		/**
		 * Removes bits from the array.
		 * @param BaseIndex - The index of the first bit to remove.
		 * @param NumBitsToRemove - The number of consecutive bits to remove.
		 */
		void RemoveAt(uint32 BaseIndex, uint32 NumBitsToRemove = 1)
		{
			Check(BaseIndex + NumBitsToRemove <= NumBits);

			if (BaseIndex + NumBitsToRemove != NumBits)
			{
				FIterator WriteIt(*this);

				for (FConstIterator ReadIt(*this); ReadIt; ++ReadIt)
				{
					if (ReadIt.GetIndex() < BaseIndex || ReadIt.GetIndex() >= BaseIndex + NumBitsToRemove)
					{
						if (WriteIt.GetIndex() != ReadIt.GetIndex())
						{
							WriteIt.GetValue() = (bool)ReadIt.GetValue();
						}
						++WriteIt;
					}
				}
			}

			NumBits -= NumBitsToRemove;
		}

	private:

		/**
		 *
		 */
		FORCENOINLINE void Realloc(uint32 PreviousNumBits)
		{
			const uint32 PreviousNumDwords = FMath::DivideAndRoundUp(PreviousNumBits, NUM_BITS_PER_DWORD);
			const uint32 MaxDwords = FMath::DivideAndRoundUp(MaxBits, NUM_BITS_PER_DWORD);

			AllocatorInstance.ResizeAllocation(PreviousNumDwords, MaxDwords, sizeof(uint32));

			if (MaxDwords)
			{
				FMemory::Memzero(GetData() + PreviousNumDwords, (MaxDwords - PreviousNumDwords) * sizeof(uint32));
			}
		}

	public:

		/**
		 *
		 */
		FORCEINLINE const uint32* GetData() const
		{
			return static_cast<uint32*>(AllocatorInstance.GetAllocation());
		}

		/**
		 *
		 */
		FORCEINLINE uint32* GetData()
		{
			return static_cast<uint32*>(AllocatorInstance.GetAllocation());
		}

		/**
		 *
		 */
		FORCEINLINE uint32 Num() const 
		{ 
			return NumBits; 
		}

	private:

		FAllocator AllocatorInstance;

		uint32 NumBits;
		uint32 MaxBits;

	};

}