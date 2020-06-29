#pragma once

#include <cassert>

#include "CoreTypes.h"
#include "Math/MathUtility.h"


namespace Nexus
{

	/**
	 * A vector in 3-D space composed of components (X, Y, Z) with floating point precision.
	 */
	struct FVector
	{

	public:

		/** Vector's X component. */
		float X;

		/** Vector's Y component. */
		float Y;

		/** Vector's Z component. */
		float Z;

	public:

		/** A zero vector (0, 0, 0) */
		static CORE_API const FVector ZeroVector;

		/** One vector (1, 1, 1) */
		static CORE_API const FVector OneVector;

		/** Nexus up vector (0, 0, 1) */
		static CORE_API const FVector UpVector;

		/** Nexus down vector (0, 0, -1) */
		static CORE_API const FVector DownVector;

		/** Nexus forward vector (1, 0, 0) */
		static CORE_API const FVector ForwardVector;

		/** Nexus backward vector (-1, 0, 0) */
		static CORE_API const FVector BackwardVector;

		/** Nexus left vector (0, -1, 0) */
		static CORE_API const FVector LeftVector;

		/** Nexus right vector (0 ,1, 0) */
		static CORE_API const FVector RightVector;

	public:

#if ENABLE_NAN_DIAGNOSTIC

		FORCEINLINE void DiagnosticCheckNaN() const
		{
			if (ContainsNaN())
			{
				// TODO: Log message
				assert(false);
			}
		}

#else

		FORCEINLINE void DiagnosticCheckNaN() const { }

#endif

	public:

		/** Default constructor (no initialization). */
		FORCEINLINE FVector();

		/**
		 * Constructor which initializes all components to zero.
		 *
		 * @param EForceInit Force init enum
		 */
		explicit FORCEINLINE FVector(EForceInit);

		/**
		 * Constructor initializing all components to a single float value.
		 *
		 * @param InF Value to set all components to.
		 */
		explicit FORCEINLINE FVector(float InF);

		/**
		 * Constructor using initial values for each component.
		 *
		 * @param InX X Coordinate.
		 * @param InY Y Coordinate.
		 * @param InZ Z Coordinate.
		 */
		FORCEINLINE FVector(float InX, float InY, float InZ);

		// TODO:
		// explicit FORCEINLINE FVector(const FVector2 V, float InZ);

		// TODO:
		// explicit FORCEINLINE FVector(const FVector4& V);

		// TODO:
		// explicit FORCEINLINE FVector(const FLinearColor& InColor);

		/**
		 * Calculate cross product between this and another vector.
		 *
		 * @param V The other vector.
		 * @return The cross product.
		 */
		FORCEINLINE FVector operator^(const FVector& V) const;

		/**
		 * Calculate the cross product of two vectors.
		 *
		 * @param A The first vector.
		 * @param B The second vector.
		 * @return The cross product.
		 */
		FORCEINLINE static FVector CrossProduct(const FVector& A, const FVector& B);

		/**
		 * Calculate the dot product between this and another vector.
		 *
		 * @param V The other vector.
		 * @return The dot product.
		 */
		FORCEINLINE float operator|(const FVector& V) const;

		/**
		 * Calculate the dot product of two vectors.
		 *
		 * @param A The first vector.
		 * @param B The second vector.
		 * @return The dot product.
		 */
		FORCEINLINE static float DotProduct(const FVector& A, const FVector& B);

		/**
		 * Gets the result of component-wise addition of this and another vector.
		 *
		 * @param V The vector to add to this.
		 * @return The result of vector addition.
		 */
		FORCEINLINE FVector operator+(const FVector& V) const;

		/**
		 * Gets the result of adding to each component of the vector.
		 *
		 * @param Bias How much to add to each component.
		 * @return The result of addition.
		 */
		FORCEINLINE FVector operator+(float Bias) const;

		/**
		 * Gets the result of component-wise subtraction of this by another vector.
		 *
		 * @param V The vector to subtract from this.
		 * @return The result of vector subtraction.
		 */
		FORCEINLINE FVector operator-(const FVector& V) const;

		/**
		 * Gets the result of subtracting from each component of the vector.
		 *
		 * @param Bias How much to subtract from each component.
		 * @return The result of subtraction.
		 */
		FORCEINLINE FVector operator-(float Bias) const;

		/**
		 * Gets the result of component-wise multiplication of this vector by another.
		 *
		 * @param V The vector to multiply with.
		 * @return The result of multiplication.
		 */
		FORCEINLINE FVector operator*(const FVector& V) const;

		/**
		 * Gets the result of scaling the vector (multiplying each component by a value).
		 *
		 * @param Scale What to multiply each component by.
		 * @return The result of multiplication.
		 */
		FORCEINLINE FVector operator*(float Scale) const;

		/**
		 * Gets the result of component-wise division of this vector by another.
		 *
		 * @param V The vector to divide by.
		 * @return The result of division.
		 */
		FORCEINLINE FVector operator/(const FVector& V) const;

		/**
		 * Gets the result of dividing each component of the vector by a value.
		 *
		 * @param Scale What to divide each component by.
		 * @return The result of division.
		 */
		FORCEINLINE FVector operator/(float Scale) const;

		/**
		 * Check against another vector for equality.
		 *
		 * @param V The vector to check against.
		 * @return true if the vectors are equal, false otherwise.
		 */
		FORCEINLINE bool operator==(const FVector& V) const;

		/**
		 * Check against another vector for inequality.
		 *
		 * @param V The vector to check against.
		 * @return true if the vectors are not equal, false otherwise.
		 */
		FORCEINLINE bool operator!=(const FVector& V) const;

		/**
		 * Check against another vector for equality, within specified error limits.
		 *
		 * @param V The vector to check against.
		 * @param Tolerance Error tolerance.
		 * @return true if the vectors are equal within tolerance limits, false otherwise.
		 */
		FORCEINLINE bool Equals(const FVector& V, float Tolerance = KINDA_SMALL_NUMBER) const;

		/**
		 * Get a negated copy of the vector.
		 *
		 * @return A negated copy of the vector.
		 */
		FORCEINLINE FVector operator-() const;

		/**
		 * Adds another vector to this.
		 * Uses component-wise addition.
		 *
		 * @param V Vector to add to this.
		 * @return Copy of the vector after addition.
		 */
		FORCEINLINE FVector operator+=(const FVector& V);

		/**
		 * Subtracts another vector from this.
		 * Uses component-wise subtraction.
		 *
		 * @param V Vector to subtract from this.
		 * @return Copy of the vector after subtraction.
		 */
		FORCEINLINE FVector operator-=(const FVector& V);

		/**
		 * Multiplies the vector with another vector, using component-wise multiplication.
		 *
		 * @param V What to multiply this vector with.
		 * @return Copy of the vector after multiplication.
		 */
		FORCEINLINE FVector operator*=(const FVector& V);

		/**
		 * Scales the vector.
		 *
		 * @param Scale Amount to scale this vector by.
		 * @return Copy of the vector after scaling.
		 */
		FORCEINLINE FVector operator*=(float Scale);

		/**
		 * Divides the vector by another vector, using component-wise division.
		 *
		 * @param V What to divide vector by.
		 * @return Copy of the vector after division.
		 */
		FORCEINLINE FVector operator/=(const FVector& V);

		/**
		 * Divides the vector by a number.
		 *
		 * @param V What to divide this vector by.
		 * @return Copy of the vector after division.
		 */
		FORCEINLINE FVector operator/=(float V);

	public:

		/**
		 * Set the values of the vector directly.
		 *
		 * @param InX New X coordinate.
		 * @param InY New Y coordinate.
		 * @param InZ New Z coordinate.
		 */
		FORCEINLINE void Set(float InX, float InY, float InZ);

		/**
		 * Get the maximum value of the vector's components.
		 *
		 * @return The maximum value of the vector's components.
		 */
		FORCEINLINE float GetMax() const;

		/**
		 * Get the maximum absolute value of the vector's components.
		 *
		 * @return The maximum absolute value of the vector's components.
		 */
		FORCEINLINE float GetAbsMax() const;

		/**
		 * Get the minimum value of the vector's components.
		 *
		 * @return The minimum value of the vector's components.
		 */
		FORCEINLINE float GetMin() const;

		/**
		 * Get the minimum absolute value of the vector's components.
		 *
		 * @return The minimum absolute value of the vector's components.
		 */
		FORCEINLINE float GetAbsMin() const;

		/**
		 * Get a copy of this vector with absolute value of each component.
		 *
		 * @return A copy of this vector with absolute value of each component.
		 */
		FORCEINLINE FVector GetAbs() const;

		/**
		 * Get the length (magnitude) of this vector.
		 *
		 * @return The length of this vector.
		 */
		FORCEINLINE float Size() const;

		/**
		 * Get the squared length of this vector.
		 *
		 * @return The squared length of this vector.
		 */
		FORCEINLINE float SizeSquared() const;

		/**
		 * Checks whether vector is normalized.
		 *
		 * @return true if normalized, false otherwise.
		 */
		FORCEINLINE bool IsNormalized() const;

		/**
		 * Checks whether the components of the vector are nearly zero.
		 *
		 * @return true if nearly zero, false otherwise.
		 */
		FORCEINLINE bool IsNearlyZero(float Tolerance = KINDA_SMALL_NUMBER) const;

		/**
		 * Normalize this vector in-place if it is larger than a given tolerance. Leaves it unchanged if not.
		 *
		 * @param Tolerance Minimum squared length of vector for normalization.
		 * @return true if the vector was normalized correctly, false otherwise.
		 */
		FORCEINLINE bool Normalize(float Tolerance = SMALL_NUMBER);

		/**
		 * Calculates normalized version of vector without checking for zero length.
		 *
		 * @return Normalized version of vector.
		 * @see GetSafeNormal()
		 */
		FORCEINLINE FVector GetUnsafeNormal() const;

		/**
		 * Gets a normalized copy of the vector, checking it is safe to do so based on the length.
		 * Returns zero vector if vector length is too small to safely normalize.
		 *
		 * @param Tolerance Minimum squared vector length.
		 * @return A normalized copy if safe, (0,0,0) otherwise.
		 */
		FORCEINLINE FVector GetSafeNormal(float Tolerance = SMALL_NUMBER) const;

	public:

		/**
		 * Euclidean distance between two points.
		 *
		 * @param V1 The first point.
		 * @param V2 The second point.
		 * @return The distance between two points.
		 */
		static FORCEINLINE float Distance(const FVector& V1, const FVector& V2);

		/**
		 * Squared distance between two points.
		 *
		 * @param V1 The first point.
		 * @param V2 The second point.
		 * @return The squared distance between two points.
		 */
		static FORCEINLINE float DistanceSquared(const FVector& V1, const FVector& V2);

	public:

		/**
		 * Utility to check if there are any non-finite values (NaN or Inf) in this vector.
		 *
		 * @return true if there are any non-finite values in this vector, false otherwise.
		 */
		FORCEINLINE bool ContainsNaN() const;

	};

	FORCEINLINE FVector::FVector()
	{ }

	FORCEINLINE FVector::FVector(EForceInit)
		: X(0.0f), Y(0.0f), Z(0.0f)
	{ }

	FORCEINLINE FVector::FVector(float InF)
		: X(InF), Y(InF), Z(InF)
	{ }

	FORCEINLINE FVector::FVector(float InX, float InY, float InZ)
		: X(InX), Y(InY), Z(InZ)
	{ }

	FORCEINLINE FVector FVector::operator^(const FVector& V) const
	{
		return FVector
		(
			Y * V.Z - Z * V.Y,
			Z * V.X - X * V.Z,
			X * V.Y - Y * V.X
		);
	}

	FORCEINLINE FVector FVector::CrossProduct(const FVector& A, const FVector& B)
	{
		return A ^ B;
	}

	FORCEINLINE float FVector::operator|(const FVector& V) const
	{
		return X * V.X + Y * V.Y + Z * V.Z;
	}

	FORCEINLINE float FVector::DotProduct(const FVector& A, const FVector& B)
	{
		return A | B;
	}

	FORCEINLINE FVector FVector::operator+(const FVector& V) const
	{
		return FVector(X + V.X, Y + V.Y, Z + V.Z);
	}

	FORCEINLINE FVector FVector::operator+(float Bias) const
	{
		return FVector(X + Bias, Y + Bias, Z + Bias);
	}

	FORCEINLINE FVector FVector::operator-(const FVector& V) const
	{
		return FVector(X - V.X, Y - V.Y, Z - V.Z);
	}

	FORCEINLINE FVector FVector::operator-(float Bias) const
	{
		return FVector(X - Bias, Y - Bias, Z - Bias);
	}

	FORCEINLINE FVector FVector::operator*(const FVector& V) const
	{
		return FVector(X * V.X, Y * V.Y, Z * V.Z);
	}

	FORCEINLINE FVector FVector::operator*(float Scale) const
	{
		return FVector(X * Scale, Y * Scale, Z * Scale);
	}

	FORCEINLINE FVector FVector::operator/(const FVector& V) const
	{
		return FVector(X / V.X, Y / V.Y, Z / V.Z);
	}

	FORCEINLINE FVector FVector::operator/(float Scale) const
	{
		const float RScale = 1.f / Scale;
		return FVector(X * RScale, Y * RScale, Z * RScale);
	}

	FORCEINLINE bool FVector::operator==(const FVector& V) const
	{
		return X == V.X && Y == V.Y && Z == V.Z;
	}

	FORCEINLINE bool FVector::operator!=(const FVector& V) const
	{
		return X != V.X || Y != V.Y || Z != V.Z;
	}

	FORCEINLINE bool FVector::Equals(const FVector& V, float Tolerance) const
	{
		return FMath::Abs(X - V.X) <= Tolerance && FMath::Abs(Y - V.Y) <= Tolerance && FMath::Abs(Z - V.Z) <= Tolerance;
	}

	FORCEINLINE FVector FVector::operator-() const
	{
		return FVector(-X, -Y, -Z);
	}

	FORCEINLINE FVector FVector::operator+=(const FVector& V)
	{
		X += V.X; Y += V.Y; Z += V.Z;
		DiagnosticCheckNaN();

		return *this;
	}

	FORCEINLINE FVector FVector::operator-=(const FVector& V)
	{
		X -= V.X; Y -= V.Y; Z -= V.Z;
		DiagnosticCheckNaN();

		return *this;
	}

	FORCEINLINE FVector FVector::operator*=(const FVector& V)
	{
		X *= V.X; Y *= V.Y; Z *= V.Z;
		DiagnosticCheckNaN();

		return *this;
	}

	FORCEINLINE FVector FVector::operator*=(float Scale)
	{
		X *= Scale; Y *= Scale; Z *= Scale;
		DiagnosticCheckNaN();

		return *this;
	}

	FORCEINLINE FVector FVector::operator/=(const FVector& V)
	{
		X /= V.X; Y /= V.Y; Z /= V.Z;
		DiagnosticCheckNaN();

		return *this;
	}

	FORCEINLINE FVector FVector::operator/=(float V)
	{
		const float RV = 1.f / V;
		X *= RV; Y *= RV; Z *= RV;
		DiagnosticCheckNaN();

		return *this;
	}

	FORCEINLINE void FVector::Set(float InX, float InY, float InZ)
	{
		X = InX;
		Y = InY;
		Z = InZ;
		DiagnosticCheckNaN();
	}

	FORCEINLINE float FVector::GetMax() const
	{
		return FMath::Max(FMath::Max(X, Y), Z);
	}

	FORCEINLINE float FVector::GetAbsMax() const
	{
		return FMath::Max(FMath::Max(FMath::Abs(X), FMath::Abs(Y)), FMath::Abs(Z));
	}

	FORCEINLINE float FVector::GetMin() const
	{
		return FMath::Min(FMath::Min(X, Y), Z);
	}

	FORCEINLINE float FVector::GetAbsMin() const
	{
		return FMath::Min(FMath::Min(FMath::Abs(X), FMath::Abs(Y)), FMath::Abs(Z));
	}

	FORCEINLINE FVector FVector::GetAbs() const
	{
		return FVector(FMath::Abs(X), FMath::Abs(Y), FMath::Abs(Z));
	}

	FORCEINLINE float FVector::Size() const
	{
		return FMath::Sqrt(X * X + Y * Y + Z * Z);
	}

	FORCEINLINE float FVector::SizeSquared() const
	{
		return X * X + Y * Y + Z * Z;
	}

	FORCEINLINE bool FVector::IsNormalized() const
	{
		return (FMath::Abs(1.f - SizeSquared()) < THRESHOLD_VECTOR_NORMALIZED);
	}

	FORCEINLINE bool FVector::IsNearlyZero(float Tolerance) const
	{
		return FMath::Abs(X) <= Tolerance
			&& FMath::Abs(Y) <= Tolerance
			&& FMath::Abs(Z) <= Tolerance;
	}

	FORCEINLINE bool FVector::Normalize(float Tolerance)
	{
		const float SquareSum = X * X + Y * Y + Z * Z;
		if (SquareSum > Tolerance)
		{
			const float Scale = FMath::InvSqrt(SquareSum);
			X *= Scale; Y *= Scale; Z *= Scale;

			return true;
		}

		return false;
	}

	FORCEINLINE FVector FVector::GetUnsafeNormal() const
	{
		const float Scale = FMath::InvSqrt(X * X + Y * Y + Z * Z);
		return FVector(X * Scale, Y * Scale, Z * Scale);
	}

	FORCEINLINE FVector FVector::GetSafeNormal(float Tolerance) const
	{
		const float SquareSum = X * X + Y * Y + Z * Z;

		// Not sure if it's safe to add tolerance in there. Might introduce too many errors.
		if (SquareSum == 1.f)
		{
			return *this;
		}
		else if (SquareSum < Tolerance)
		{
			return FVector::ZeroVector;
		}

		const float Scale = FMath::InvSqrt(SquareSum);
		return FVector(X * Scale, Y * Scale, Z * Scale);
	}

	FORCEINLINE float FVector::Distance(const FVector& V1, const FVector& V2)
	{
		return FMath::Sqrt(FVector::DistanceSquared(V1, V2));
	}

	FORCEINLINE float FVector::DistanceSquared(const FVector& V1, const FVector& V2)
	{
		return FMath::Square(V2.X - V1.X) + FMath::Square(V2.Y - V1.Y) + FMath::Square(V2.Z - V1.Z);
	}

	FORCEINLINE bool FVector::ContainsNaN() const
	{
		return (!FMath::IsFinite(X) ||
			!FMath::IsFinite(Y) ||
			!FMath::IsFinite(Z));
	}


}