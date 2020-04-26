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

		// Operators.

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
		// TODO: Not correct yet!
		FMatrix Result;

		//VectorRegister R0 = VectorShuffle0101(V[0], V[1]);
		//VectorRegister R1 = VectorShuffle2323(V[0], V[1]);

		//Result.V[0] = VectorShuffle(R0, V[2], 0, 2, 0, 3);
		//Result.V[1] = VectorShuffle(R0, V[2], 1, 3, 1, 3);
		//Result.V[2] = VectorShuffle(R1, V[2], 0, 2, 2, 3);

		//VectorRegister SizeSquared;
		//SizeSquared = VectorMultiply(Result.V[0], Result.V[0]);
		//SizeSquared = VectorAdd(SizeSquared, VectorMultiply(Result.V[1], Result.V[1]));
		//SizeSquared = VectorAdd(SizeSquared, VectorMultiply(Result.V[2], Result.V[2]));

		//Result.V[3] = VectorMultiply(Result.V[0], VectorSwizzle(V[3], 0, 0, 0, 0));
		//Result.V[3] = VectorAdd(Result.V[3], VectorMultiply(Result.V[1], VectorSwizzle(V[3], 1, 1, 1, 1)));
		//Result.V[3] = VectorAdd(Result.V[3], VectorMultiply(Result.V[2], VectorSwizzle(V[3], 2, 2, 2, 2)));
		//Result.V[3] = VectorSubtract(MakeVectorRegister(0.0f, 0.0f, 0.0f, 1.0f), Result.V[3]);


		VectorRegister A = VectorShuffle0101(V[0], V[1]);
		VectorRegister B = VectorShuffle2323(V[0], V[1]);
		VectorRegister C = VectorShuffle0101(V[2], V[3]);
		VectorRegister D = VectorShuffle2323(V[2], V[3]);

#if 0
		__m128 detA = _mm_set1_ps(inM.m[0][0] * inM.m[1][1] - inM.m[0][1] * inM.m[1][0]);
		__m128 detB = _mm_set1_ps(inM.m[0][2] * inM.m[1][3] - inM.m[0][3] * inM.m[1][2]);
		__m128 detC = _mm_set1_ps(inM.m[2][0] * inM.m[3][1] - inM.m[2][1] * inM.m[3][0]);
		__m128 detD = _mm_set1_ps(inM.m[2][2] * inM.m[3][3] - inM.m[2][3] * inM.m[3][2]);
#else
		// determinant as (|A| |B| |C| |D|)
		VectorRegister DetSub = VectorSubtract(
			VectorMultiply(VectorShuffle(V[0], V[2], 0, 2, 0, 2), VectorShuffle(V[1], V[3], 1, 3, 1, 3)),
			VectorMultiply(VectorShuffle(V[0], V[2], 1, 3, 1, 3), VectorShuffle(V[1], V[3], 0, 2, 0, 2))
		);

		VectorRegister DetA = VectorSwizzle(DetSub, 0, 0, 0, 0);
		VectorRegister DetB = VectorSwizzle(DetSub, 1, 1, 1, 1);
		VectorRegister DetC = VectorSwizzle(DetSub, 2, 2, 2, 2);
		VectorRegister DetD = VectorSwizzle(DetSub, 3, 3, 3, 3);
#endif


		VectorRegister DC = VectorSubtract(VectorMultiply(VectorSwizzle(D, 3, 3, 0, 0), C), VectorMultiply(VectorSwizzle(D, 1, 1, 2, 2), VectorSwizzle(C, 2, 3, 0, 1)));
		VectorRegister AB = VectorSubtract(VectorMultiply(VectorSwizzle(A, 3, 3, 0, 0), B), VectorMultiply(VectorSwizzle(A, 1, 1, 2, 2), VectorSwizzle(B, 2, 3, 0, 1)));
		VectorRegister X = VectorSubtract(VectorMultiply(DetD, A), VectorAdd(VectorMultiply(B, VectorSwizzle(DC, 0, 3, 0, 3)), VectorMultiply(VectorSwizzle(B, 1, 0, 3, 2), VectorSwizzle(DC, 2, 1, 2, 1))));
		VectorRegister W = VectorSubtract(VectorMultiply(DetA, D), VectorAdd(VectorMultiply(C, VectorSwizzle(AB, 0, 3, 0, 3)), VectorMultiply(VectorSwizzle(C, 1, 0, 3, 2), VectorSwizzle(AB, 2, 1, 2, 1))));

		VectorRegister DetM = VectorMultiply(DetA, DetD);
		VectorRegister Y = VectorSubtract(VectorMultiply(DetB, C), VectorSubtract(VectorMultiply(D, VectorSwizzle(AB, 3, 0, 3, 0)), VectorMultiply(VectorSwizzle(D, 1, 0, 3, 2), VectorSwizzle(AB, 2, 1, 2, 1))));
		VectorRegister Z = VectorSubtract(VectorMultiply(DetC, B), VectorSubtract(VectorMultiply(A, VectorSwizzle(DC, 3, 0, 3, 0)), VectorMultiply(VectorSwizzle(A, 1, 0, 3, 2), VectorSwizzle(DC, 2, 1, 2, 1))));

		
		DetM = VectorAdd(DetM, VectorMultiply(DetB, DetC));


		VectorRegister TR = VectorMultiply(AB, VectorSwizzle(DC, 0, 2, 1, 3));
		TR = VectorHorizontalAdd(TR, TR);
		TR = VectorHorizontalAdd(TR, TR);
		
		DetM = VectorSubtract(DetM, TR);

		const VectorRegister AdjSignMask = MakeVectorRegister(1.0f, -1.0f, -1.0f, 1.0f);
		VectorRegister RDetM = VectorDivide(AdjSignMask, DetM);

		X = VectorMultiply(X, RDetM);
		Y = VectorMultiply(Y, RDetM);
		Z = VectorMultiply(Z, RDetM);
		W = VectorMultiply(W, RDetM);

		Result.V[0] = VectorShuffle(X, Y, 3, 1, 3, 1);
		Result.V[1] = VectorShuffle(X, Y, 2, 0, 2, 0);
		Result.V[2] = VectorShuffle(Z, W, 3, 1, 3, 1);
		Result.V[3] = VectorShuffle(Z, W, 2, 0, 2, 0);

		return Result;
	}

	FMatrix FMatrix::GetInverseFast() const
	{

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