#pragma once

#include "CoreTypes.h"

#include "Templates/IsCharType.h"
#include "Templates/SelectType.h"
#include "Templates/IsTriviallyCopyAssignable.h"
#include "Templates/InstantiateEmptyString.h"
#include "Templates/InstantiateNullTerminator.h"

#include "Array.h"


namespace Nexus
{

	/**
	 *
	 */
	template<
		typename FCharType = TSelectType<
			PLATFORM_CHAR_IS_CHAR16,
			WideChar,
			AnsiChar
		>::Type
	>
	class FString
	{

	private:

		static_assert(TAreTypesEqual<FCharType, AnsiChar>::Value || TAreTypesEqual<FCharType, WideChar>::Value, "Cannot instantiate FString with types other than 'AnsiChar' or 'WideChar'.");

	public:

		//////////////////////////////////////////////////
		// Constructors. /////////////////////////////////
		//////////////////////////////////////////////////

		/**
		 *
		 */
		FString() = default;

		/**
		 * Constructor using an array of TCHAR
		 *
		 * @param In array of TCHAR
		 */
		template <
			typename FOtherCharType,
			typename = typename TEnableIf<TIsCharType<FOtherCharType>::Value>::Type
		>
		FORCEINLINE FString(const FOtherCharType* Source)
		{
			if (Source && *Source)
			{
				uint32 SourceLength = static_cast<uint32>(FPlatformString::Strlen(Source)) + 1;
				uint32 DestLength = FPlatformString::ConvertedLength<FCharType>(Source, SourceLength);
				Data.AddUninitialized(DestLength);

				FPlatformString::Convert(Data.GetData(), DestLength, Source, SourceLength);
			}
		}

		/**
		 * Constructor to create FString with specified number of characters from another string with additional character zero
		 *
		 * @param InCount how many characters to copy
		 * @param InSrc String to copy from
		 */
		template <
			typename FOtherCharType,
			typename = typename TEnableIf<TIsCharType<FOtherCharType>::Value>::Type // This TEnableIf is to ensure we don't instantiate this constructor for non-char types, like id* in Obj-C
		>
			FORCEINLINE explicit FString(uint32 InCount, const FOtherCharType* InSrc)
		{
			if (InSrc && *InSrc)
			{
				uint32 DestLen = FPlatformString::ConvertedLength<FCharType>(InSrc, InCount);
				if (DestLen > 0)
				{
					Data.AddUninitialized(DestLen + 1);

					FPlatformString::Convert(Data.GetData(), DestLen, InSrc, InCount);
					*(Data.GetData() + Data.Num() - 1) = TInstantiateNullTerminator<FCharType>::Value;
				}
			}
		}

		/**
		 *
		 */
		FString(const FString&) = default;

		/**
		 *
		 */
		FString(FString&&) = default;

	public:

		//////////////////////////////////////////////////
		// Assignment operators. /////////////////////////
		//////////////////////////////////////////////////

		/**
		 *
		 */
		FString& operator=(const FString&) = default;

		/**
		 * Copy Assignment from array of TCHAR
		 *
		 * @param Other array of TCHAR
		 */
		FORCEINLINE FString& operator=(const FCharType* Other)
		{
			if (Data.GetData() != Other)
			{
				uint32 Length = (Other && *Other) ? FPlatformString::Strlen(Other) + 1 : 0;

				Data.Empty(Length);
				Data.AddUninitialized(Length);

				if (Length)
				{
					FMemory::Memcpy(Data.GetData(), Other, Length * sizeof(FCharType));
				}
			}

			return *this;
		}

		/**
		 *
		 */
		FString& operator=(FString&&) = default;

	public:

		//////////////////////////////////////////////////
		// Index operators. //////////////////////////////
		//////////////////////////////////////////////////

		/**
		 * Return specific character from this string
		 *
		 * @param Index into string
		 * @return Character at Index
		 */
		FORCEINLINE FCharType& operator[](uint32 Index)
		{
			Check(Index != INVALID_INDEX && Index < Num());
			return Data.GetData()[Index];
		}

		/**
		 * Return specific const character from this string
		 *
		 * @param Index into string
		 * @return const Character at Index
		 */
		FORCEINLINE const FCharType& operator[](uint32 Index) const
		{
			Check(Index != INVALID_INDEX && Index < Num());
			return Data.GetData()[Index];
		}

	public:

		//////////////////////////////////////////////////
		// Other operators. //////////////////////////////
		//////////////////////////////////////////////////

		/**
		 * Concatenate this with given char
		 *
		 * @param inChar other Char to be concatenated onto the end of this string
		 * @return reference to this
		 */
		template <typename CharType>
		FORCEINLINE typename TEnableIf<TIsCharType<CharType>::Value, FString&>::Type operator+=(CharType InChar)
		{
			AppendChar(InChar);
			return *this;
		}

		/**
		 * Concatenate this with given string
		 *
		 * @param Str array of TCHAR to be concatenated onto the end of this
		 * @return reference to this
		 */
		FORCEINLINE FString& operator+=(const FCharType* CharArray)
		{
			PlatformSizeType Length = FPlatformString::Strlen(CharArray);
			AppendChars(CharArray, static_cast<uint32>(Length));

			return *this;
		}

		/**
		 * Concatenate this with given string
		 *
		 * @param Str other string to be concatenated onto the end of this
		 * @return reference to this
		 */
		FORCEINLINE FString& operator+=(const FString& String)
		{
			Append(String);
			return *this;
		}

		/**
		 * Get pointer to the string
		 *
		 * @Return Pointer to Array of FCharType if Num, otherwise the empty string
		 */
		FORCEINLINE const FCharType* operator*() const
		{
			return Data.Num() ? Data.GetData() : TInstantiateEmptyString<FCharType>::Value;
		}

	public:

		/**
		 * Concatenate this with given char
		 *
		 * @param InChar other Char to be concatenated onto the end of this string
		 * @return reference to this
		 */
		FORCEINLINE void AppendChar(const FCharType InChar)
		{
			CheckInvariants();

			if (InChar != 0)
			{
				uint32 InsertIndex = (Data.Num() > 0) ? Data.Num() - 1 : 0;
				uint32 InsertCount = (Data.Num() > 0) ? 1 : 2;

				Data.AddUninitialized(InsertCount);
				Data[InsertIndex] = InChar;
				Data[InsertIndex + 1] = 0;
			}
		}

		/**
		 * Appends an array of characters to the string.
		 *
		 * @param Array A pointer to the start of an array of characters to append.  This array need not be null-terminated, and null characters are not treated specially.
		 * @param Count The number of characters to copy from Array.
		 */
		FORCEINLINE void AppendChars(const FCharType* Array, uint32 Count)
		{
			if (!Count)
				return;

			Check(Array);
			CheckInvariants();

			uint32 Index = Data.Num();

			Data.AddUninitialized(Count + (Index ? 0 : 1));
			FCharType* EndPtr = Data.GetData() + Index - (Index ? 1 : 0);

			CopyAssignItems(EndPtr, Array, Count);
			*(EndPtr + Count) = 0;
		}

		/**
		 * Concatenate this with given string
		 *
		 * @param Str other string to be concatenated onto the end of this
		 * @return reference to this
		 */
		FORCEINLINE void Append(const FString& String)
		{
			CheckInvariants();
			String.CheckInvariants();

			AppendChars(String.Data.GetData(), String.Num());
		}

		/**
		 *
		 */
		FORCEINLINE void InsertAt(uint32 Index, FCharType Character)
		{
			if (Character != 0)
			{
				if (Data.Num() == 0)
				{
					AppendChar(Character);
				}
				else
				{
					Data.Insert(Character, Index);
				}
			}
		}

		/**
		 *
		 */
		FORCEINLINE void InsertAt(uint32 Index, const FString& Characters)
		{
			if (Characters.Num())
			{
				if (Data.Num() == 0)
				{
					Append(Characters);
				}
				else
				{
					Data.Insert(Characters.Data.GetData(), Characters.Num(), Index);
				}
			}
		}

	public:

		//////////////////////////////////////////////////
		// Memory operations. ////////////////////////////
		//////////////////////////////////////////////////

		/**
		 * Empties the string, but doesn't change memory allocation, unless the new size is larger than the current string.
		 *
		 * @param NewReservedSize The expected usage size (in characters, not including the terminator) after calling this function.
		 */
		FORCEINLINE void Reset(uint32 NewReservedSize = 0)
		{
			const uint32 NewSizeIncludingTerminator = (NewReservedSize > 0) ? (NewReservedSize + 1) : 0;
			Data.Reset(NewSizeIncludingTerminator);

			if (FCharType* DataPtr = Data.GetData())
			{
				*DataPtr = TInstantiateNullTerminator<FCharType>::Value;
			}
		}

		/**
		 * Create empty string of given size with zero terminating character
		 *
		 * @param Slack length of empty string to create
		 */
		FORCEINLINE void Empty(int32 Slack = 0)
		{
			Data.Empty(Slack);
		}

		/**
		 * Remove unallocated empty character space from the end of this string
		 */
		FORCEINLINE void Shrink()
		{
			Data.Shrink();
		}

	public:

		//////////////////////////////////////////////////
		// Simple functions. /////////////////////////////
		//////////////////////////////////////////////////

		/**
		 * Test whether this string is empty
		 *
		 * @return true if this string is empty, otherwise return false.
		 */
		FORCEINLINE bool IsEmpty() const
		{
			return Data.Num() <= 1;
		}

		/** 
		 * Get the length of the string, excluding terminating character.
		 */
		FORCEINLINE uint32 Num() const
		{
			return Data.Num() ? Data.Num() - 1 : 0;
		}

		/**
		 *
		 */
		FORCEINLINE const FCharType* GetData() const
		{
			return Data.Num() ? Data.GetData() : TInstantiateEmptyString<FCharType>::Value;
		}

		/**
		 * Get string as array of TCHARS
		 *
		 * @warning: Operations on the TArray<*CHAR> can be unsafe, such as adding
		 *		non-terminating 0's or removing the terminating zero.
		 */
		FORCEINLINE TArray<FCharType>& GetCharArray()
		{
			return Data;
		}

		/**
		 *
		 */
		FORCEINLINE PlatformSizeType GetAllocatedSize() const
		{
			return Data.GetAllocatedSize();
		}

	private:

		//////////////////////////////////////////////////
		// Raw memory functions. /////////////////////////
		//////////////////////////////////////////////////

		/**
		 * Copy assigns a range of items.
		 *
		 * @param	Dest		The memory location to start assigning to.
		 * @param	Source		A pointer to the first item to assign.
		 * @param	Count		The number of elements to assign.
		 */
		FORCEINLINE void CopyAssignItems(FCharType* Dest, const FCharType* Source, uint32 Count)
		{
			if constexpr (TIsTriviallyCopyAssignable<FCharType>::Value)
			{
				FMemory::Memcpy(Dest, Source, sizeof(FCharType) * Count);
			}
			else
			{
				while (Count)
				{
					*Dest = *Source;
					++Dest;
					++Source;
					--Count;
				}
			}
		}

	private:

		//////////////////////////////////////////////////
		// Utility functions. ////////////////////////////
		//////////////////////////////////////////////////

		/**
		 * Run slow checks on this string
		 */
		FORCEINLINE void CheckInvariants() const
		{
			uint32 Num = Data.Num();
			Check(!Num || !Data.GetData()[Num - 1]);
			Check(Data.GetSlack() >= 0);
		}

	private:

		/**
		 *
		 */
		TArray<FCharType> Data;

	};

}