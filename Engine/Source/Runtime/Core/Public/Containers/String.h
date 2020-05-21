#pragma once

#include "CoreTypes.h"
#include "Templates/IsCharType.h"
#include "Templates/SelectType.h"

#include "Array.h"


namespace Nexus
{

	template<typename FEncoding>
	struct TInstantiateEmptyString { static_assert(sizeof(FEncoding) == 0, "Cannot instantiate empty string of unknown char type."); };

	template<>
	struct TInstantiateEmptyString<AnsiChar> { static constexpr AnsiChar* Value = ""; };

	template<>
	struct TInstantiateEmptyString<WideChar> { static constexpr WideChar* Value = L""; };

	template<typename FEncoding>
	struct TInstantiateNullTerminator { static_assert(sizeof(FEncoding) == 0, "Cannot instantiate null termination character of unknown char type."); };

	template<>
	struct TInstantiateNullTerminator<AnsiChar> { static constexpr AnsiChar Value = '\0'; };

	template<>
	struct TInstantiateNullTerminator<WideChar> { static constexpr WideChar Value = L'\0'; };

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
					FMemory::Memcpy(Data.GetData(), Other, Len * sizeof(FCharType));
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
			Check(Index < Num());
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
			Check(Index < Num());
			return Data.GetData()[Index];
		}

	public:

		//////////////////////////////////////////////////
		// Other operators. //////////////////////////////
		//////////////////////////////////////////////////

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
				*DataPtr = TInstantiateNullTerminator<FCharType>;
			}
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

		/**
		 *
		 */
		TArray<FCharType> Data;

	};

}