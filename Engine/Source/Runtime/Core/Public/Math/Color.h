#pragma once

#include "CoreTypes.h"

#include "Math/Vector.h"
#include "Math/Vector4.h"

namespace Nexus
{

	/**
	 * Enum for the different kinds of gamma spaces we expect to need to convert from/to.
	 */
	enum class EGammaSpace : uint8
	{

		/** No gamma correction is applied to this space, the incoming colors are assumed to already be in linear space. */
		Linear,

		/** A simplified sRGB gamma correction is applied, pow(1/2.2). */
		Pow22,

		/** Use the standard sRGB conversion. */
		sRGB

	};

	/**
	 * A linear, 32-bit/component floating point RGBA color.
	 */
	struct alignas(16) FLinearColor
	{

	public:

		/** The color red component. */
		float R;

		/** The color green component. */
		float G;

		/** The color blue component. */
		float B;

		/** The color alpha component. */
		float A;

	public:

		// Lookup tables.

		/** Static lookup table used for FColor -> FLinearColor conversion (sRGB -> linear). */
		CORE_API static float sRGBToLinearTable[256];

		/** Static lookup table used for FColor -> FLinearColor conversion (Pow(2.2)). */
		CORE_API static float Pow22OneOver255Table[256];

		/** 1.0f / 255.0f. Used, because multiplication is faster than division. */
		static float OneOver255;

	public:

		// Common colors.

		static CORE_API const FLinearColor White;
		static CORE_API const FLinearColor Gray;
		static CORE_API const FLinearColor Black;
		static CORE_API const FLinearColor Transparent;
		static CORE_API const FLinearColor Red;
		static CORE_API const FLinearColor Green;
		static CORE_API const FLinearColor Blue;
		static CORE_API const FLinearColor Yellow;

	public:

		// Constructors.

		/**
		 * Default contructor (no initialization).
		 */
		FORCEINLINE FLinearColor();

		/**
		 * Default contructor (with initialization).
		 */
		FORCEINLINE explicit FLinearColor(EForceInit);

		/**
		 * Creates and initializes a new linear color from the specified components.
		 *
		 * @param InR Color red component.
		 * @param InG Color green component.
		 * @param InB Color blue component.
		 * @param InA Color alpha component.
		 */
		constexpr FORCEINLINE FLinearColor(float InR, float InG, float InB, float InA = 1.0f);

		/**
		 * Creates and initializes a new linear color from the specified vector.
		 *
		 * @param Vector The vector specifying the RGB components of the color.
		 */
		FLinearColor(const FVector& Vector);

		/**
		 * Creates and initializes a new linear color from the specified vector.
		 *
		 * @param Vector The vector specifying the RGBA components of the color.
		 */
		FLinearColor(const FVector4& Vector);

		/**
		 * Converts an FColor which is assumed to be in sRGB space, into linear color space.
		 *
		 * @param Color The sRGB color that needs to be converted into linear space.
		 */
		FLinearColor(const struct FColor& Color);

	public:

		// Index access.

		/**
		 *
		 */
		FORCEINLINE float& Component(uint32 Index);

		/**
		 *
		 */
		FORCEINLINE const float& Component(uint32 Index) const;

	public:

		// Binary Operators.

		/**
		 *
		 */
		FORCEINLINE FLinearColor operator+(const FLinearColor& ColorB) const;

		/**
		 *
		 */
		FORCEINLINE FLinearColor& operator+=(const FLinearColor& ColorB);

		/**
		 *
		 */
		FORCEINLINE FLinearColor operator-(const FLinearColor& ColorB) const;

		/**
		 *
		 */
		FORCEINLINE FLinearColor& operator-=(const FLinearColor& ColorB);

		/**
		 *
		 */
		FORCEINLINE FLinearColor operator*(float Scalar) const;

		/**
		 *
		 */
		FORCEINLINE FLinearColor operator*(const FLinearColor& ColorB) const;

		/**
		 *
		 */
		FORCEINLINE FLinearColor& operator*=(float Scalar);

		/**
		 *
		 */
		FORCEINLINE FLinearColor& operator*=(const FLinearColor& ColorB);

		/**
		 *
		 */
		FORCEINLINE FLinearColor operator/(float Scalar) const;

		/**
		 *
		 */
		FORCEINLINE FLinearColor operator/(const FLinearColor& ColorB) const;

		/**
		 *
		 */
		FORCEINLINE FLinearColor& operator/=(float Scalar);

		/**
		 *
		 */
		FORCEINLINE FLinearColor& operator/=(const FLinearColor& ColorB);

		// Equality operators.

		/**
		 *
		 */
		FORCEINLINE bool operator==(const FLinearColor& ColorB) const;

		/**
		 *
		 */
		FORCEINLINE bool operator!=(const FLinearColor& ColorB) const;

	public:

		// Error tolerant comparison.

		/**
		 *
		 */
		FORCEINLINE bool Equals(const FLinearColor& ColorB, float Tolerance = KINDA_SMALL_NUMBER) const;

	public:

		// Simple functions.

		/** 
		 * Computes the perceptually weighted luminance value of a color.
		 *
		 * @return The computed luminance.
		 */
		FORCEINLINE float ComputeLuminance() const;

		/**
		 * Clamps all components of the color between the two given values (default: 0.0 - 1.0).
		 *
		 * @return The clamped linear color.
		 */
		FORCEINLINE FLinearColor GetClamped(float InMin = 0.0f, float InMax = 1.0f) const;

	public:

		// Utility functions.

		/**
		 * Computes the linear color for a sRGB color component.
		 *
		 * @param Component The sRGB color component to transform into linear space.
		 * @return The color component in linear color space.
		 */
		FORCEINLINE float SRGBToLinearColor(uint8 Component) const;

		/**
		 * Computes the linear color for a Pow(2.2) color component.
		 *
		 * @param Component The Pow(2.2) color component to transform into linear space.
		 * @return The color component in linear color space.
		 */
		FORCEINLINE float Pow22ToLinearColor(float Component) const;

	public:

		// Conversion functions.

		/**
		 * Converts an FColor coming from an observed sRGB output, into a linear color.
		 * @param Color The sRGB color that needs to be converted into linear space.
		 */
		CORE_API static FLinearColor FromSRGBColor(const FColor& Color);

		/**
		 * Converts an FColor coming from an observed Pow(1/2.2) output, into a linear color.
		 * @param Color The Pow(1/2.2) color that needs to be converted into linear space.
		 */
		CORE_API static FLinearColor FromPow22Color(const FColor& Color);

	};

	struct alignas(16) FColor
	{

	public:

#if PLATFORM_LITTLE_ENDIAN
#ifdef _MSC_VER
		union
		{

			struct
			{
				uint8 B;
				uint8 G;
				uint8 R;
				uint8 A;
			};

			uint32 AlignmentDummy;
		};
#else
		uint8 alignas(4) B;
		uint8 alignas(4) G;
		uint8 alignas(4) R;
		uint8 alignas(4) A;
#endif
		union
		{
			struct
			{
				uint8 A;
				uint8 R;
				uint8 G;
				uint8 B;
			};

			uint32 AlignmentDummy;
		};
#endif

	public:

		// Pre-init colors.

		static CORE_API const FColor White;
		static CORE_API const FColor Black;
		static CORE_API const FColor Transparent;
		static CORE_API const FColor Red;
		static CORE_API const FColor Green;
		static CORE_API const FColor Blue;
		static CORE_API const FColor Yellow;
		static CORE_API const FColor Cyan;
		static CORE_API const FColor Magenta;
		static CORE_API const FColor Orange;
		static CORE_API const FColor Purple;
		static CORE_API const FColor Turquoise;
		static CORE_API const FColor Silver;
		static CORE_API const FColor Emerald;


	public:

		// Constructors.

		FORCEINLINE FColor();

		FORCEINLINE explicit FColor(EForceInit);

		FORCEINLINE FColor(uint8 InR, uint8 InG, uint8 InB, uint8 InA = 255);

		FORCEINLINE explicit FColor(uint32 InColor);

	private:

		// DWORD access.

		uint32& DWColor(void)
		{
			return *((uint32*)this);
		}

		const uint32& DWColor(void) const
		{
			return *((uint32*)this);
		}

	public:

		// Operators.

		FORCEINLINE bool operator==(const FColor& C) const;

		FORCEINLINE bool operator!=(const FColor& C) const;

		FORCEINLINE void operator+=(const FColor& C);

		FORCEINLINE void operator-=(const FColor& C);

	};

	/** FLinearColor functions. */

	// Contructors.

	FLinearColor::FLinearColor()
	{

	}

	FLinearColor::FLinearColor(EForceInit)
		: R(0.0f), G(0.0f), B(0.0f), A(0.0f)
	{

	}

	constexpr FLinearColor::FLinearColor(float InR, float InG, float InB, float InA)
		: R(InR), G(InG), B(InB), A(InA)
	{

	}

	FLinearColor::FLinearColor(const FVector& Vector)
		: R(Vector.X)
		, G(Vector.Y)
		, B(Vector.Z)
		, A(1.0f)
	{

	}

	FLinearColor::FLinearColor(const FVector4& Vector)
		: R(Vector.X)
		, G(Vector.Y)
		, B(Vector.Z)
		, A(Vector.W)
	{

	}

	FLinearColor::FLinearColor(const FColor& Color)
		: R(sRGBToLinearTable[Color.R])
		, G(sRGBToLinearTable[Color.G])
		, B(sRGBToLinearTable[Color.B])
		, A(float(Color.A) * 1.0f / 255.0f)
	{
	}

	// Index access.

	float& FLinearColor::Component(uint32 Index)
	{
		return (&R)[Index];
	}

	const float& FLinearColor::Component(uint32 Index) const
	{
		return (&R)[Index];
	}

	// Binary operators.

	FLinearColor FLinearColor::operator+(const FLinearColor& ColorB) const
	{
		return FLinearColor(
			R + ColorB.R,
			G + ColorB.G,
			B + ColorB.B,
			A + ColorB.A
		);
	}

	FLinearColor& FLinearColor::operator+=(const FLinearColor& ColorB)
	{
		R += ColorB.R;
		G += ColorB.G;
		B += ColorB.B;
		A += ColorB.A;

		return *this;
	}

	FLinearColor FLinearColor::operator-(const FLinearColor& ColorB) const
	{
		return FLinearColor(
			this->R - ColorB.R,
			this->G - ColorB.G,
			this->B - ColorB.B,
			this->A - ColorB.A
		);
	}

	FLinearColor& FLinearColor::operator-=(const FLinearColor& ColorB)
	{
		R -= ColorB.R;
		G -= ColorB.G;
		B -= ColorB.B;
		A -= ColorB.A;

		return *this;
	}

	FLinearColor FLinearColor::operator*(float Scalar) const
	{
		return FLinearColor(
			R * Scalar,
			G * Scalar,
			B * Scalar,
			A * Scalar
		);
	}

	FLinearColor FLinearColor::operator*(const FLinearColor& ColorB) const
	{
		return FLinearColor(
			R * ColorB.R,
			G * ColorB.G,
			B * ColorB.B,
			A * ColorB.A
		);
	}

	FLinearColor& FLinearColor::operator*=(float Scalar)
	{
		R *= Scalar;
		G *= Scalar;
		B *= Scalar;
		A *= Scalar;

		return *this;
	}

	FLinearColor& FLinearColor::operator*=(const FLinearColor& ColorB)
	{
		R *= ColorB.R;
		G *= ColorB.G;
		B *= ColorB.B;
		A *= ColorB.A;

		return *this;
	}

	FLinearColor FLinearColor::operator/(float Scalar) const
	{
		const float	InverseScalar = 1.0f / Scalar;

		return FLinearColor(
			R * InverseScalar,
			G * InverseScalar,
			B * InverseScalar,
			A * InverseScalar
		);
	}

	FLinearColor FLinearColor::operator/(const FLinearColor& ColorB) const
	{
		return FLinearColor(
			R / ColorB.R,
			G / ColorB.G,
			B / ColorB.B,
			A / ColorB.A
		);
	}


	FLinearColor& FLinearColor::operator/=(float Scalar)
	{
		const float	InverseScalar = 1.0f / Scalar;

		R *= InverseScalar;
		G *= InverseScalar;
		B *= InverseScalar;
		A *= InverseScalar;

		return *this;
	}

	FLinearColor& FLinearColor::operator/=(const FLinearColor& ColorB)
	{
		R /= ColorB.R;
		G /= ColorB.G;
		B /= ColorB.B;
		A /= ColorB.A;

		return *this;
	}

	// Equality operators.

	bool FLinearColor::operator==(const FLinearColor& ColorB) const
	{
		return R == ColorB.R
			&& G == ColorB.G
			&& B == ColorB.B
			&& A == ColorB.A;
	}

	bool FLinearColor::operator!=(const FLinearColor& ColorB) const
	{
		return R != ColorB.R
			|| G != ColorB.G
			|| B != ColorB.B
			|| A != ColorB.A;
	}

	// Error tolerant comparison.

	bool FLinearColor::Equals(const FLinearColor& ColorB, float Tolerance) const
	{
		return FMath::Abs(R - ColorB.R) < Tolerance
			&& FMath::Abs(G - ColorB.G) < Tolerance
			&& FMath::Abs(B - ColorB.B) < Tolerance
			&& FMath::Abs(A - ColorB.A) < Tolerance;
	}

	// Simple functions.

	float FLinearColor::ComputeLuminance() const
	{
		return R * 0.3f + G * 0.59f + B * 0.11f;
	}

	FLinearColor FLinearColor::GetClamped(float InMin, float InMax) const
	{
		FLinearColor Result;

		Result.R = FMath::Clamp(R, InMin, InMax);
		Result.G = FMath::Clamp(G, InMin, InMax);
		Result.B = FMath::Clamp(B, InMin, InMax);
		Result.A = FMath::Clamp(A, InMin, InMax);

		return Result;
	}

	// Utility functions.

	float FLinearColor::SRGBToLinearColor(uint8 Component) const
	{
		const float Color = float(Component) / 255.0f;
		return Color > 0.04045f ? FMath::Pow(Color * (1.0f / 1.055f) + 0.0521327f, 2.4f) : Color * (1.0f / 12.92f);
	}

	float FLinearColor::Pow22ToLinearColor(float Component) const
	{
		return FMath::Pow(Component / 255.0f, 2.2f);
	}

	/** FColor functions. */

	// Constructors.

	FColor::FColor()
	{

	}

	FColor::FColor(EForceInit)
	{
		// Put assignments into the body for proper ordering with INTEL- vs non-INTEL_BYTE_ORDER.
		R = G = B = A = 0;
	}

	FColor::FColor(uint8 InR, uint8 InG, uint8 InB, uint8 InA)
	{
		// Put assignments into the body for proper ordering with INTEL- vs non-INTEL_BYTE_ORDER.
		R = InR;
		G = InG;
		B = InB;
		A = InA;
	}

	FColor::FColor(uint32 InColor)
	{
		DWColor() = InColor;
	}

	bool FColor::operator==(const FColor& C) const
	{
		return DWColor() == C.DWColor();
	}

	bool FColor::operator!=(const FColor& C) const
	{
		return DWColor() != C.DWColor();
	}

	void FColor::operator+=(const FColor& C)
	{
		R = static_cast<uint8>(FMath::Min(static_cast<int32>(R) + static_cast<int32>(C.R), 255));
		G = static_cast<uint8>(FMath::Min(static_cast<int32>(G) + static_cast<int32>(C.G), 255));
		B = static_cast<uint8>(FMath::Min(static_cast<int32>(B) + static_cast<int32>(C.B), 255));
		A = static_cast<uint8>(FMath::Min(static_cast<int32>(A) + static_cast<int32>(C.A), 255));
	}

	void FColor::operator-=(const FColor& C)
	{
		R = static_cast<uint8>(FMath::Min(static_cast<int32>(R) - static_cast<int32>(C.R), 0));
		G = static_cast<uint8>(FMath::Min(static_cast<int32>(G) - static_cast<int32>(C.G), 0));
		B = static_cast<uint8>(FMath::Min(static_cast<int32>(B) - static_cast<int32>(C.B), 0));
		A = static_cast<uint8>(FMath::Min(static_cast<int32>(A) - static_cast<int32>(C.A), 0));
	}


}