#pragma once

#include "CoreTypes.h"

namespace Nexus
{

	/**
	 *
	 */
	struct FMatrixArithmetic
	{

	private:

		/**
		 *
		 */
		using Float4 = float[4];

		/**
		 *
		 */
		using Float4x4 = float[4][4];

	public:

		static FORCEINLINE void MatrixScalarMultiply(void* DstMatrix, const void* SrcMatrix, float Scalar)
		{
			const Float4x4& M = *static_cast<const Float4x4*>(SrcMatrix);
			Float4x4& Result = *static_cast<Float4x4*>(DstMatrix);

			for (uint32 X = 0; X < 4; X++)
			{
				for (uint32 Y = 0; Y < 4; Y++)
				{
					Result[X][Y] = M[X][Y] * Scalar;
				}
			}
		}

		static FORCEINLINE void MatrixAdd(void* DstMatrix, const void* Matrix1, const void* Matrix2)
		{
			const Float4x4& M = *static_cast<const Float4x4*>(Matrix1);
			const Float4x4& Other = *static_cast<const Float4x4*>(Matrix2);

			Float4x4& Result = *static_cast<Float4x4*>(DstMatrix);

			for (uint32 X = 0; X < 4; X++)
			{
				for (uint32 Y = 0; Y < 4; Y++)
				{
					Result[X][Y] = M[X][Y] + Other[X][Y];
				}
			}
		}

		static FORCEINLINE void MatrixMultiply(void* DstMatrix, const void* Matrix1, const void* Matrix2)
		{
			const Float4x4& M = *static_cast<const Float4x4*>(Matrix1);
			const Float4x4& Other = *static_cast<const Float4x4*>(Matrix2);

			Float4x4& Result = *static_cast<Float4x4*>(DstMatrix);

			Result[0][0] = M[0][0] * Other[0][0] + M[0][1] * Other[1][0] + M[0][2] * Other[2][0] + M[0][3] * Other[3][0];
			Result[0][1] = M[0][0] * Other[0][1] + M[0][1] * Other[1][1] + M[0][2] * Other[2][1] + M[0][3] * Other[3][1];
			Result[0][2] = M[0][0] * Other[0][2] + M[0][1] * Other[1][2] + M[0][2] * Other[2][2] + M[0][3] * Other[3][2];
			Result[0][3] = M[0][0] * Other[0][3] + M[0][1] * Other[1][3] + M[0][2] * Other[2][3] + M[0][3] * Other[3][3];

			Result[1][0] = M[1][0] * Other[0][0] + M[1][1] * Other[1][0] + M[1][2] * Other[2][0] + M[1][3] * Other[3][0];
			Result[1][1] = M[1][0] * Other[0][1] + M[1][1] * Other[1][1] + M[1][2] * Other[2][1] + M[1][3] * Other[3][1];
			Result[1][2] = M[1][0] * Other[0][2] + M[1][1] * Other[1][2] + M[1][2] * Other[2][2] + M[1][3] * Other[3][2];
			Result[1][3] = M[1][0] * Other[0][3] + M[1][1] * Other[1][3] + M[1][2] * Other[2][3] + M[1][3] * Other[3][3];

			Result[2][0] = M[2][0] * Other[0][0] + M[2][1] * Other[1][0] + M[2][2] * Other[2][0] + M[2][3] * Other[3][0];
			Result[2][1] = M[2][0] * Other[0][1] + M[2][1] * Other[1][1] + M[2][2] * Other[2][1] + M[2][3] * Other[3][1];
			Result[2][2] = M[2][0] * Other[0][2] + M[2][1] * Other[1][2] + M[2][2] * Other[2][2] + M[2][3] * Other[3][2];
			Result[2][3] = M[2][0] * Other[0][3] + M[2][1] * Other[1][3] + M[2][2] * Other[2][3] + M[2][3] * Other[3][3];

			Result[3][0] = M[3][0] * Other[0][0] + M[3][1] * Other[1][0] + M[3][2] * Other[2][0] + M[3][3] * Other[3][0];
			Result[3][1] = M[3][0] * Other[0][1] + M[3][1] * Other[1][1] + M[3][2] * Other[2][1] + M[3][3] * Other[3][1];
			Result[3][2] = M[3][0] * Other[0][2] + M[3][1] * Other[1][2] + M[3][2] * Other[2][2] + M[3][3] * Other[3][2];
			Result[3][3] = M[3][0] * Other[0][3] + M[3][1] * Other[1][3] + M[3][2] * Other[2][3] + M[3][3] * Other[3][3];
		}

		/**
		 * Calculates the inverse of SrcMatrix and stores it into DstMatrix.
		 */
		static FORCEINLINE void MatrixInverse(void* DstMatrix, const void* SrcMatrix)
		{
			const Float4x4& M = *static_cast<const Float4x4*>(SrcMatrix);
			Float4x4& Result = *static_cast<Float4x4*>(DstMatrix);

			Float4x4 Temp;
			Float4 Det;

			Temp[0][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
			Temp[0][1] = M[1][2] * M[3][3] - M[1][3] * M[3][2];
			Temp[0][2] = M[1][2] * M[2][3] - M[1][3] * M[2][2];

			Temp[1][0] = M[2][2] * M[3][3] - M[2][3] * M[3][2];
			Temp[1][1] = M[0][2] * M[3][3] - M[0][3] * M[3][2];
			Temp[1][2] = M[0][2] * M[2][3] - M[0][3] * M[2][2];

			Temp[2][0] = M[1][2] * M[3][3] - M[1][3] * M[3][2];
			Temp[2][1] = M[0][2] * M[3][3] - M[0][3] * M[3][2];
			Temp[2][2] = M[0][2] * M[1][3] - M[0][3] * M[1][2];

			Temp[3][0] = M[1][2] * M[2][3] - M[1][3] * M[2][2];
			Temp[3][1] = M[0][2] * M[2][3] - M[0][3] * M[2][2];
			Temp[3][2] = M[0][2] * M[1][3] - M[0][3] * M[1][2];

			Det[0] = M[1][1] * Temp[0][0] - M[2][1] * Temp[0][1] + M[3][1] * Temp[0][2];
			Det[1] = M[0][1] * Temp[1][0] - M[2][1] * Temp[1][1] + M[3][1] * Temp[1][2];
			Det[2] = M[0][1] * Temp[2][0] - M[1][1] * Temp[2][1] + M[3][1] * Temp[2][2];
			Det[3] = M[0][1] * Temp[3][0] - M[1][1] * Temp[3][1] + M[2][1] * Temp[3][2];

			float Determinant = M[0][0] * Det[0] - M[1][0] * Det[1] + M[2][0] * Det[2] - M[3][0] * Det[3];
			const float	RDet = 1.0f / Determinant;

			{
				Result[0][0] =  RDet * Det[0];
				Result[0][1] = -RDet * Det[1];
				Result[0][2] =  RDet * Det[2];
				Result[0][3] = -RDet * Det[3];
			}

			{
				Result[1][0] = -RDet * (M[1][0] * Temp[0][0] - M[2][0] * Temp[0][1] + M[3][0] * Temp[0][2]);
				Result[1][1] =  RDet * (M[0][0] * Temp[1][0] - M[2][0] * Temp[1][1] + M[3][0] * Temp[1][2]);
				Result[1][2] = -RDet * (M[0][0] * Temp[2][0] - M[1][0] * Temp[2][1] + M[3][0] * Temp[2][2]);
				Result[1][3] =  RDet * (M[0][0] * Temp[3][0] - M[1][0] * Temp[3][1] + M[2][0] * Temp[3][2]);
			}

			{
				Result[2][0] = RDet * (
					M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
					M[2][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) +
					M[3][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1])
					);

				Result[2][1] = -RDet * (
					M[0][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
					M[2][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
					M[3][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1])
					);

				Result[2][2] = RDet * (
					M[0][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) -
					M[1][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
					M[3][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1])
					);

				Result[2][3] = -RDet * (
					M[0][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]) -
					M[1][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1]) +
					M[2][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1])
					);
			}

			{
				Result[3][0] = -RDet * (
					M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
					M[2][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) +
					M[3][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])
					);

				Result[3][1] = RDet * (
					M[0][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
					M[2][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
					M[3][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1])
					);

				Result[3][2] = -RDet * (
					M[0][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) -
					M[1][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
					M[3][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
					);

				Result[3][3] = RDet * (
					M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
					M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
					M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
					);
			}
		}

	};



}