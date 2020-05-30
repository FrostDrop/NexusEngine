#pragma once

#include "CoreTypes.h"

#include "Templates/EnableIf.h"
#include "Templates/IsFixedWidthEncoding.h"

namespace Nexus
{

	/**
	 * Metafunction which tests whether two encodings are compatible.
	 *
	 * We'll say the encodings are compatible if they're both fixed-width and have the same size.  This
	 * should be good enough and catches things like UCS2CHAR and WIDECHAR being equivalent.
	 * Specializations of this template can be provided for any other special cases.
	 * Same size is a minimum requirement.
	 */
	template <typename FEncodingA, typename FEncodingB>
	struct TAreEncodingsCompatible
	{
		enum { Value = TIsFixedWidthEncoding<FEncodingA>::Value && TIsFixedWidthEncoding<FEncodingB>::Value && sizeof(FEncodingA) == sizeof(FEncodingB) };
	};

	struct FGenericPlatformString
	{

		/**
		 *
		 */
		static FORCEINLINE PlatformSizeType Strlen(const AnsiChar* String)
		{
			return strlen(String);
		}

		/**
		 *
		 */
		static FORCEINLINE PlatformSizeType Strlen(const WideChar* String)
		{
			return wcslen(String);
		}

		/**
		 * Tests whether a particular character is a valid member of its encoding.
		 *
		 * @param Ch The character to test.
		 * @return True if the character is a valid member of Encoding.
		 */
		template <typename FEncoding>
		static bool IsValidChar(FEncoding Ch)
		{
			return true;
		}


		/**
		 * Tests whether a particular character can be converted to the destination encoding.
		 *
		 * @param Ch The character to test.
		 * @return True if Ch can be encoded as a DestEncoding.
		 */
		template <typename FDestEncoding, typename FSourceEncoding>
		static bool CanConvertChar(FSourceEncoding Char)
		{
			return IsValidChar(Char) && (FSourceEncoding)(FDestEncoding)Char == Char && IsValidChar((FDestEncoding)Char);
		}

		/**
		 * Returns the required buffer length for the [Src, Src+SrcSize) string when converted to the DestChar encoding.
		 * The Src range should contain a null terminator if a null terminator is required in the output.
		 *
		 * @param  Cource     The start of the string to convert.
		 * @param  SourceCount The number of Src elements to convert.
		 * @return				The number of DestChar elements that Src will be converted into.
		 */
		template <typename FDestEncoding, typename FSourceEncoding>
		static typename TEnableIf<TIsFixedWidthEncoding<FSourceEncoding>::Value && TIsFixedWidthEncoding<FDestEncoding>::Value, uint32>::Type ConvertedLength(const FSourceEncoding* Source, uint32 SourceCount)
		{
			return SourceCount;
		}

		/**
		 * Converts the [Src, Src+SrcSize) string range from SourceChar to DestChar and writes it to the [Dest, Dest+DestSize) range.
		 * The Src range should contain a null terminator if a null terminator is required in the output.
		 * If the Dest range is not big enough to hold the converted output, NULL is returned.  In this case, nothing should be assumed about the contents of Dest.
		 *
		 * @param Dest      The start of the destination buffer.
		 * @param DestSize  The size of the destination buffer.
		 * @param Src       The start of the string to convert.
		 * @param SrcSize   The number of Src elements to convert.
		 * @param BogusChar The char to use when the conversion process encounters a character it cannot convert.
		 * @return          A pointer to one past the last-written element.
		 */
		template <typename FSourceEncoding, typename FDestEncoding>
		static FORCEINLINE typename TEnableIf<
			TAreEncodingsCompatible<FSourceEncoding, FDestEncoding>::Value,
			FDestEncoding*
		>::Type Convert(FDestEncoding* Dest, uint32 DestSize, const FSourceEncoding* Src, uint32 SrcSize, FDestEncoding BogusChar = static_cast<FDestEncoding>('?'))
		{
			if (DestSize < SrcSize)
				return nullptr;

			return static_cast<FDestEncoding*>(FPlatformMemory::Memcpy(Dest, Src, SrcSize * sizeof(FSourceEncoding))) + SrcSize;
		}

		/**
		 * Converts the [Src, Src+SrcSize) string range from SourceEncoding to DestEncoding and writes it to the [Dest, Dest+DestSize) range.
		 * The Src range should contain a null terminator if a null terminator is required in the output.
		 * If the Dest range is not big enough to hold the converted output, NULL is returned.  In this case, nothing should be assumed about the contents of Dest.
		 *
		 * @param Dest      The start of the destination buffer.
		 * @param DestSize  The size of the destination buffer.
		 * @param Src       The start of the string to convert.
		 * @param SrcSize   The number of Src elements to convert.
		 * @param BogusChar The char to use when the conversion process encounters a character it cannot convert.
		 * @return          A pointer to one past the last-written element.
		 */
		template <typename FSourceEncoding, typename FDestEncoding>
		static typename TEnableIf<
			// This overload should be called when the types are not compatible but the source is fixed-width, e.g. ANSICHAR->WIDECHAR.
			!TAreEncodingsCompatible<FSourceEncoding, FDestEncoding>::Value && TIsFixedWidthEncoding<FSourceEncoding>::Value,
			FDestEncoding*
		>::Type Convert(FDestEncoding* Dest, uint32 DestSize, const FSourceEncoding* Source, uint32 SourceSize, FDestEncoding BogusChar = static_cast<FDestEncoding>('?'))
		{
			const uint32 Size = DestSize <= SourceSize ? DestSize : SourceSize;
			bool bInvalidChars = false;

			for (uint32 I = 0; I < Size; ++I)
			{
				FSourceEncoding SourceChar = Source[I];
				Dest[I] = static_cast<FDestEncoding>(SourceChar);

				bInvalidChars |= !CanConvertChar<FDestEncoding>(SourceChar);
			}

			if (bInvalidChars)
			{
				for (uint32 I = 0; I < Size; ++I)
				{
					if (!CanConvertChar<FDestEncoding>(Source[I]))
					{
						Dest[I] = BogusChar;
					}
				}
			}

			return DestSize < SourceSize ? nullptr : Dest + Size;
		}

	};

}