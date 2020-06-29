#pragma once

#include "CoreTypes.h"
#include "MathUtility.h"

#include "Vector.h"
#include "MathSSE.h"

#if PLATFORM_ENABLE_VECTORINTRINSICS
	#include "MatrixSSE.h"
#else
	#include "MatrixFPU.h"
#endif

namespace Nexus
{

	/**
	 * 4x4 matrix of floating point values.
	 * Elements are accessed with M[Row][Column].
	 */
	struct alignas(16) FMatrix
	{

	public:

		union
		{

			float M[4][4];
			VectorRegister V[4];

		};

	public:

		// Constructors.

		/**
		 *
		 */
		FORCEINLINE FMatrix();

		/**
		 *
		 */
		FORCEINLINE FMatrix(EForceInit);

		/**
		 * Constructor.
		 *
		 * @param InX X vector
		 * @param InY Y vector
		 * @param InZ Z vector
		 * @param InW W vector
		 */
		FORCEINLINE FMatrix(const FVector& InX, const FVector& InY, const FVector& InZ, const FVector& InW);

	public:

		// Binary operators.

		/**
		 * Gets the result of multiplying a Matrix to this.
		 *
		 * @param Other The matrix to multiply this by.
		 * @return The result of multiplication.
		 */
		FORCEINLINE FMatrix operator*(const FMatrix& Other) const;

		/**
		 * Multiply this by a matrix.
		 *
		 * @param Other the matrix to multiply by this.
		 * @return reference to this after multiply.
		 */
		FORCEINLINE void operator*=(const FMatrix& Other);

		/**
		  * This isn't applying SCALE, just multiplying the value to all members - i.e. weighting
		  */
		FORCEINLINE FMatrix operator*(float Other) const;

		/**
		 * Multiply this matrix by a weighting factor.
		 *
		 * @param other The weight.
		 * @return a reference to this after weighting.
		 */
		FORCEINLINE void operator*=(float Other);

		/**
		 * Gets the result of adding a matrix to this.
		 *
		 * @param Other The Matrix to add.
		 * @return The result of addition.
		 */
		FORCEINLINE FMatrix operator+(const FMatrix& Other) const;

		/**
		 * Adds to this matrix.
		 *
		 * @param Other The matrix to add to this.
		 * @return Reference to this after addition.
		 */
		FORCEINLINE void operator+=(const FMatrix& Other);

	public:

		// Comparison operators.

		/**
		 * Checks whether two matrix are identical.
		 *
		 * @param Other The other matrix.
		 * @return true if two matrix are identical, otherwise false.
		 */
		inline bool operator==(const FMatrix& Other) const;

	
		/**
		 * Checks whether another Matrix is not equal to this, within specified tolerance.
		 *
		 * @param Other The other Matrix.
		 * @return true if two Matrix are not equal, within specified tolerance, otherwise false.
		 */
		inline bool operator!=(const FMatrix& Other) const;

		/**
		 * Checks whether another Matrix is equal to this, within specified tolerance.
		 *
		 * @param Other The other Matrix.
		 * @param Tolerance Error Tolerance.
		 * @return true if two Matrix are equal, within specified tolerance, otherwise false.
		 */
		inline bool Equals(const FMatrix& Other, float Tolerance = KINDA_SMALL_NUMBER) const;

	public:

		// Simple functions.

		/**
		 * Set this matrix to the identity matrix.
		 */
		inline void SetIdentity();

	public:

		// Complex functions.

		/**
		 * Gets the transposed matrix.
		 */
		FORCEINLINE FMatrix GetTransposed() const;

		/**
		 * Calculates the inverse matrix using the fast path.
		 * Handles nil matrices.
		 */
		inline FMatrix GetInverse() const;

		/**
		 * Calculates the inverse matrix using the fast path.
		 * Does not handles nil matrices in release builds.
		 */
		inline FMatrix GetInverseFast() const;

		/**
		 * Computes the determinant.
		 */
		inline float GetDeterminant() const;


	};

	FMatrix::FMatrix()
	{

	}

	FMatrix::FMatrix(EForceInit)
	{

	}

	FMatrix::FMatrix(const FVector& InX, const FVector& InY, const FVector& InZ, const FVector& InW)
	{
		M[0][0] = InX.X; M[0][1] = InX.Y;  M[0][2] = InX.Z;  M[0][3] = 0.0f;
		M[1][0] = InY.X; M[1][1] = InY.Y;  M[1][2] = InY.Z;  M[1][3] = 0.0f;
		M[2][0] = InZ.X; M[2][1] = InZ.Y;  M[2][2] = InZ.Z;  M[2][3] = 0.0f;
		M[3][0] = InW.X; M[3][1] = InW.Y;  M[3][2] = InW.Z;  M[3][3] = 1.0f;
	}

	FMatrix FMatrix::operator*(const FMatrix& Other) const
	{
		FMatrix Result;
		FMatrixArithmetic::MatrixMultiply(&Result, this, &Other);

		return Result;
	}

	void FMatrix::operator*=(const FMatrix& Other)
	{
		FMatrixArithmetic::MatrixMultiply(this, this, &Other);
	}

	FMatrix FMatrix::operator*(float Other) const
	{
		FMatrix Result;
		FMatrixArithmetic::MatrixScalarMultiply(&Result, this, Other);

		return Result;
	}

	void FMatrix::operator*=(float Other)
	{
		FMatrixArithmetic::MatrixScalarMultiply(this, this, Other);
	}

	FMatrix FMatrix::operator+(const FMatrix& Other) const
	{
		FMatrix Result;
		FMatrixArithmetic::MatrixAdd(&Result, this, &Other);

		return Result;
	}

	void FMatrix::operator+=(const FMatrix& Other)
	{
		FMatrixArithmetic::MatrixAdd(this, this, &Other);
	}

	bool FMatrix::operator==(const FMatrix& Other) const
	{
		for (uint32 X = 0; X < 4; X++)
		{
			for (uint32 Y = 0; Y < 4; Y++)
			{
				if (M[X][Y] != Other.M[X][Y])
				{
					return false;
				}
			}
		}

		return true;
	}

	bool FMatrix::operator!=(const FMatrix& Other) const
	{
		return !(*this == Other);
	}

	inline bool FMatrix::Equals(const FMatrix& Other, float Tolerance) const
	{
		for (uint32 X = 0; X < 4; X++)
		{
			for (uint32 Y = 0; Y < 4; Y++)
			{
				if (FMath::Abs(M[X][Y] - Other.M[X][Y]) > Tolerance)
				{
					return false;
				}
			}
		}

		return true;
	}

	void FMatrix::SetIdentity()
	{
		M[0][0] = 1; M[0][1] = 0;  M[0][2] = 0;  M[0][3] = 0;
		M[1][0] = 0; M[1][1] = 1;  M[1][2] = 0;  M[1][3] = 0;
		M[2][0] = 0; M[2][1] = 0;  M[2][2] = 1;  M[2][3] = 0;
		M[3][0] = 0; M[3][1] = 0;  M[3][2] = 0;  M[3][3] = 1;
	}

	FMatrix FMatrix::GetTransposed() const
	{
		FMatrix	Result;

		Result.M[0][0] = M[0][0];
		Result.M[0][1] = M[1][0];
		Result.M[0][2] = M[2][0];
		Result.M[0][3] = M[3][0];

		Result.M[1][0] = M[0][1];
		Result.M[1][1] = M[1][1];
		Result.M[1][2] = M[2][1];
		Result.M[1][3] = M[3][1];

		Result.M[2][0] = M[0][2];
		Result.M[2][1] = M[1][2];
		Result.M[2][2] = M[2][2];
		Result.M[2][3] = M[3][2];

		Result.M[3][0] = M[0][3];
		Result.M[3][1] = M[1][3];
		Result.M[3][2] = M[2][3];
		Result.M[3][3] = M[3][3];

		return Result;
	}

	FMatrix FMatrix::GetInverse() const
	{
		FMatrix Result;
		FMatrixArithmetic::MatrixInverse(&Result, this);

		return Result;
	}

	FMatrix FMatrix::GetInverseFast() const
	{
		return GetInverse();
	}

	float FMatrix::GetDeterminant() const
	{
		return	M[0][0] * (
			M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
			M[2][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) +
			M[3][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
			) -
			M[1][0] * (
				M[0][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
				M[2][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
				M[3][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2])
				) +
			M[2][0] * (
				M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) -
				M[1][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
				M[3][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
				) -
			M[3][0] * (
				M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) -
				M[1][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2]) +
				M[2][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
				);
	}

}

