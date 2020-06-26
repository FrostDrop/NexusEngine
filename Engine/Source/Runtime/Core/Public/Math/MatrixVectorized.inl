

namespace Nexus
{

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

		VectorRegister R0;
		VectorRegister R1;
		VectorRegister R2;
		VectorRegister R3;
		VectorRegister Temp;

		// First row of result (Matrix1[0] * Matrix2).
		Temp = VectorMultiply(VectorReplicate(V[0], 0), Other.V[0]);
		Temp = VectorMultiplyAdd(VectorReplicate(V[0], 1), Other.V[1], Temp);
		Temp = VectorMultiplyAdd(VectorReplicate(V[0], 2), Other.V[2], Temp);
		R0 = VectorMultiplyAdd(VectorReplicate(V[0], 3), Other.V[3], Temp);

		// Second row of result (Matrix1[1] * Matrix2).
		Temp = VectorMultiply(VectorReplicate(V[1], 0), Other.V[0]);
		Temp = VectorMultiplyAdd(VectorReplicate(V[1], 1), Other.V[1], Temp);
		Temp = VectorMultiplyAdd(VectorReplicate(V[1], 2), Other.V[2], Temp);
		R1 = VectorMultiplyAdd(VectorReplicate(V[1], 3), Other.V[3], Temp);

		// Third row of result (Matrix1[2] * Matrix2).
		Temp = VectorMultiply(VectorReplicate(V[2], 0), Other.V[0]);
		Temp = VectorMultiplyAdd(VectorReplicate(V[2], 1), Other.V[1], Temp);
		Temp = VectorMultiplyAdd(VectorReplicate(V[2], 2), Other.V[2], Temp);
		R2 = VectorMultiplyAdd(VectorReplicate(V[2], 3), Other.V[3], Temp);

		// Fourth row of result (Matrix1[3] * Matrix2).
		Temp = VectorMultiply(VectorReplicate(V[3], 0), Other.V[0]);
		Temp = VectorMultiplyAdd(VectorReplicate(V[3], 1), Other.V[1], Temp);
		Temp = VectorMultiplyAdd(VectorReplicate(V[3], 2), Other.V[2], Temp);
		R3 = VectorMultiplyAdd(VectorReplicate(V[3], 3), Other.V[3], Temp);

		// Store result
		Result.V[0] = R0;
		Result.V[1] = R1;
		Result.V[2] = R2;
		Result.V[3] = R3;

		return Result;
	}

	void FMatrix::operator*=(const FMatrix& Other) 
	{
		VectorRegister R0;
		VectorRegister R1;
		VectorRegister R2;
		VectorRegister R3;
		VectorRegister Temp;

		// First row of result (Matrix1[0] * Matrix2).
		Temp = VectorMultiply(VectorReplicate(V[0], 0), Other.V[0]);
		Temp = VectorMultiplyAdd(VectorReplicate(V[0], 1), Other.V[1], Temp);
		Temp = VectorMultiplyAdd(VectorReplicate(V[0], 2), Other.V[2], Temp);
		R0 = VectorMultiplyAdd(VectorReplicate(V[0], 3), Other.V[3], Temp);

		// Second row of result (Matrix1[1] * Matrix2).
		Temp = VectorMultiply(VectorReplicate(V[1], 0), Other.V[0]);
		Temp = VectorMultiplyAdd(VectorReplicate(V[1], 1), Other.V[1], Temp);
		Temp = VectorMultiplyAdd(VectorReplicate(V[1], 2), Other.V[2], Temp);
		R1 = VectorMultiplyAdd(VectorReplicate(V[1], 3), Other.V[3], Temp);

		// Third row of result (Matrix1[2] * Matrix2).
		Temp = VectorMultiply(VectorReplicate(V[2], 0), Other.V[0]);
		Temp = VectorMultiplyAdd(VectorReplicate(V[2], 1), Other.V[1], Temp);
		Temp = VectorMultiplyAdd(VectorReplicate(V[2], 2), Other.V[2], Temp);
		R2 = VectorMultiplyAdd(VectorReplicate(V[2], 3), Other.V[3], Temp);

		// Fourth row of result (Matrix1[3] * Matrix2).
		Temp = VectorMultiply(VectorReplicate(V[3], 0), Other.V[0]);
		Temp = VectorMultiplyAdd(VectorReplicate(V[3], 1), Other.V[1], Temp);
		Temp = VectorMultiplyAdd(VectorReplicate(V[3], 2), Other.V[2], Temp);
		R3 = VectorMultiplyAdd(VectorReplicate(V[3], 3), Other.V[3], Temp);

		// Store result
		V[0] = R0;
		V[1] = R1;
		V[2] = R2;
		V[3] = R3;
	}

	FORCEINLINE FMatrix FMatrix::operator*(float Other) const
	{
		FMatrix Result;
		VectorRegister ScalarVector = MakeVectorRegister(Other);

		Result.V[0] = VectorMultiply(V[0], ScalarVector);
		Result.V[1] = VectorMultiply(V[1], ScalarVector);
		Result.V[2] = VectorMultiply(V[2], ScalarVector);
		Result.V[3] = VectorMultiply(V[3], ScalarVector);

		return Result;
	}

	FORCEINLINE void FMatrix::operator*=(float Other)
	{
		VectorRegister ScalarVector = MakeVectorRegister(Other);

		V[0] = VectorMultiply(V[0], ScalarVector);
		V[1] = VectorMultiply(V[1], ScalarVector);
		V[2] = VectorMultiply(V[2], ScalarVector);
		V[3] = VectorMultiply(V[3], ScalarVector);
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

		Result.V[0] = VectorShuffle(X, Y, 3, 1, 3, 1);
		Result.V[1] = VectorShuffle(X, Y, 2, 0, 2, 0);
		Result.V[2] = VectorShuffle(Z, W, 3, 1, 3, 1);
		Result.V[3] = VectorShuffle(Z, W, 2, 0, 2, 0);

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