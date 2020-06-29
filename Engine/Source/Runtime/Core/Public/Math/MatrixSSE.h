#pragma once

#include "CoreTypes.h"


namespace Nexus
{

	struct FMatrixArithmetic
	{

	private:

		using Float4 = float[4];
		using Float4x4 = float[4][4];


		using Vector = VectorRegister;
		using Vector4 = VectorRegister[4];

	public:

		static FORCEINLINE void MatrixScalarMultiply(void* DstMatrix, const void* SrcMatrix, float Scalar)
		{
			const Vector4& V = *static_cast<const Vector4*>(SrcMatrix);
			Vector4& Result = *static_cast<Vector4*>(DstMatrix);

			VectorRegister ScalarVector = MakeVectorRegister(Scalar);

			Result[0] = VectorMultiply(V[0], ScalarVector);
			Result[1] = VectorMultiply(V[1], ScalarVector);
			Result[2] = VectorMultiply(V[2], ScalarVector);
			Result[3] = VectorMultiply(V[3], ScalarVector);
		}

		static FORCEINLINE void MatrixAdd(void* DstMatrix, const void* Matrix1, const void* Matrix2)
		{
			const Vector4& V = *static_cast<const Vector4*>(Matrix1);
			const Vector4& Other = *static_cast<const Vector4*>(Matrix2);

			Vector4& Result = *static_cast<Vector4*>(DstMatrix);

			Result[0] = VectorAdd(V[0], Other[0]);
			Result[1] = VectorAdd(V[1], Other[1]);
			Result[2] = VectorAdd(V[2], Other[2]);
			Result[3] = VectorAdd(V[3], Other[3]);
		}

		static FORCEINLINE void MatrixMultiply(void* DstMatrix, const void* Matrix1, const void* Matrix2)
		{
			const Vector4& V = *static_cast<const Vector4*>(Matrix1);
			const Vector4& Other = *static_cast<const Vector4*>(Matrix2);

			Vector4& Result = *static_cast<Vector4*>(DstMatrix);

			VectorRegister R0;
			VectorRegister R1;
			VectorRegister R2;
			VectorRegister R3;
			VectorRegister Temp;

			// First row of result (Matrix1[0] * Matrix2).
			Temp = VectorMultiply(VectorReplicate(V[0], 0), Other[0]);
			Temp = VectorMultiplyAdd(VectorReplicate(V[0], 1), Other[1], Temp);
			Temp = VectorMultiplyAdd(VectorReplicate(V[0], 2), Other[2], Temp);
			R0 = VectorMultiplyAdd(VectorReplicate(V[0], 3), Other[3], Temp);

			// Second row of result (Matrix1[1] * Matrix2).
			Temp = VectorMultiply(VectorReplicate(V[1], 0), Other[0]);
			Temp = VectorMultiplyAdd(VectorReplicate(V[1], 1), Other[1], Temp);
			Temp = VectorMultiplyAdd(VectorReplicate(V[1], 2), Other[2], Temp);
			R1 = VectorMultiplyAdd(VectorReplicate(V[1], 3), Other[3], Temp);

			// Third row of result (Matrix1[2] * Matrix2).
			Temp = VectorMultiply(VectorReplicate(V[2], 0), Other[0]);
			Temp = VectorMultiplyAdd(VectorReplicate(V[2], 1), Other[1], Temp);
			Temp = VectorMultiplyAdd(VectorReplicate(V[2], 2), Other[2], Temp);
			R2 = VectorMultiplyAdd(VectorReplicate(V[2], 3), Other[3], Temp);

			// Fourth row of result (Matrix1[3] * Matrix2).
			Temp = VectorMultiply(VectorReplicate(V[3], 0), Other[0]);
			Temp = VectorMultiplyAdd(VectorReplicate(V[3], 1), Other[1], Temp);
			Temp = VectorMultiplyAdd(VectorReplicate(V[3], 2), Other[2], Temp);
			R3 = VectorMultiplyAdd(VectorReplicate(V[3], 3), Other[3], Temp);

			// Store result
			Result[0] = R0;
			Result[1] = R1;
			Result[2] = R2;
			Result[3] = R3;
		}

		static FORCEINLINE void MatrixInverse(void* DstMatrix, const void* SrcMatrix)
		{
			const Vector4& V = *static_cast<const Vector4*>(SrcMatrix);
			Vector4& Result = *static_cast<Vector4*>(DstMatrix);

			VectorRegister A = VectorShuffle0101(V[0], V[1]);
			VectorRegister B = VectorShuffle2323(V[0], V[1]);
			VectorRegister C = VectorShuffle0101(V[2], V[3]);
			VectorRegister D = VectorShuffle2323(V[2], V[3]);

			VectorRegister DetSub = VectorSubtract(
				VectorMultiply(VectorShuffle(V[0], V[2], 0, 2, 0, 2), VectorShuffle(V[1], V[3], 1, 3, 1, 3)),
				VectorMultiply(VectorShuffle(V[0], V[2], 1, 3, 1, 3), VectorShuffle(V[1], V[3], 0, 2, 0, 2))
			);

			VectorRegister DetA = VectorSwizzle(DetSub, 0, 0, 0, 0);
			VectorRegister DetB = VectorSwizzle(DetSub, 1, 1, 1, 1);
			VectorRegister DetC = VectorSwizzle(DetSub, 2, 2, 2, 2);
			VectorRegister DetD = VectorSwizzle(DetSub, 3, 3, 3, 3);

			VectorRegister DC = VectorSubtract(
				VectorMultiply(VectorSwizzle(D, 3, 3, 0, 0), C),
				VectorMultiply(VectorSwizzle(D, 1, 1, 2, 2), VectorSwizzle(C, 2, 3, 0, 1))
			);

			VectorRegister AB = VectorSubtract(
				VectorMultiply(VectorSwizzle(A, 3, 3, 0, 0), B),
				VectorMultiply(VectorSwizzle(A, 1, 1, 2, 2), VectorSwizzle(B, 2, 3, 0, 1))
			);

			VectorRegister X = VectorSubtract(
				VectorMultiply(DetD, A),
				VectorAdd(
					VectorMultiply(B, VectorSwizzle(DC, 0, 3, 0, 3)),
					VectorMultiply(VectorSwizzle(B, 1, 0, 3, 2), VectorSwizzle(DC, 2, 1, 2, 1))
				)
			);

			VectorRegister W = VectorSubtract(
				VectorMultiply(DetA, D),
				VectorAdd(
					VectorMultiply(C, VectorSwizzle(AB, 0, 3, 0, 3)),
					VectorMultiply(VectorSwizzle(C, 1, 0, 3, 2), VectorSwizzle(AB, 2, 1, 2, 1))
				)
			);

			VectorRegister DetM = VectorMultiply(DetA, DetD);

			VectorRegister Y = VectorSubtract(
				VectorMultiply(DetB, C),
				VectorSubtract(
					VectorMultiply(D, VectorSwizzle(AB, 3, 0, 3, 0)),
					VectorMultiply(VectorSwizzle(D, 1, 0, 3, 2), VectorSwizzle(AB, 2, 1, 2, 1))
				)
			);

			VectorRegister Z = VectorSubtract(
				VectorMultiply(DetC, B),
				VectorSubtract(
					VectorMultiply(A, VectorSwizzle(DC, 3, 0, 3, 0)),
					VectorMultiply(VectorSwizzle(A, 1, 0, 3, 2), VectorSwizzle(DC, 2, 1, 2, 1))
				)
			);


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

			Result[0] = VectorShuffle(X, Y, 3, 1, 3, 1);
			Result[1] = VectorShuffle(X, Y, 2, 0, 2, 0);
			Result[2] = VectorShuffle(Z, W, 3, 1, 3, 1);
			Result[3] = VectorShuffle(Z, W, 2, 0, 2, 0);
		}
	
	};

}