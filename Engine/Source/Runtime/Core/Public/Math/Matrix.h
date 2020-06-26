#pragma once

#include "CoreTypes.h"
#include "MathUtility.h"

#include "Vector.h"
#include "MathSSE.h"


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

}

#if PLATFORM_ENABLE_VECTORINTRINSICS
	#include "MatrixVectorized.inl"
#else
	#include "MatrixNonVectorized.inl"
#endif