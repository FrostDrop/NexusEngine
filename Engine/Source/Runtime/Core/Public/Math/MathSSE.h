#pragma once

#include "CoreTypes.h"

/** Require SSE2. */
#include <emmintrin.h>
#include <pmmintrin.h>


namespace Nexus
{

	using VectorRegister = __m128;
	using VectorRegisterInt = __m128i;
	using VectorRegisterDouble = __m128d;

    /**
     * @param A0	Selects which element (0-3) from 'A' into 1st slot in the result
     * @param A1	Selects which element (0-3) from 'A' into 2nd slot in the result
     * @param B2	Selects which element (0-3) from 'B' into 3rd slot in the result
     * @param B3	Selects which element (0-3) from 'B' into 4th slot in the result
     */
    #define VECTOR_SHUFFLE_MASK(A0, A1, B2, B3) ( (A0) | ((A1) << 2) | ((B2) << 4) | ((B3) << 6) )

    /**
     *
     */
    #define VectorShuffle0101(Vec1, Vec2) _mm_movelh_ps(Vec1, Vec2)

    /**
     *
     */
    #define VectorShuffle2323(Vec1, Vec2) _mm_movehl_ps(Vec2, Vec1)

    /**
     * Creates a vector through selecting two components from each vector via a shuffle mask.
     *
     * @param Vec1		Source vector1
     * @param Vec2		Source vector2
     * @param X			Index for which component of Vector1 to use for X (literal 0-3)
     * @param Y			Index for which component of Vector1 to use for Y (literal 0-3)
     * @param Z			Index for which component of Vector2 to use for Z (literal 0-3)
     * @param W			Index for which component of Vector2 to use for W (literal 0-3)
     * @return			The swizzled vector
     */
    #define VectorShuffle( Vec1, Vec2, X, Y, Z, W )	_mm_shuffle_ps( Vec1, Vec2, VECTOR_SHUFFLE_MASK(X, Y, Z, W) )

    /**
     * Swizzles the 4 components of a vector and returns the result.
     *
     * @param Vec		Source vector
     * @param X			Index for which component to use for X (literal 0-3)
     * @param Y			Index for which component to use for Y (literal 0-3)
     * @param Z			Index for which component to use for Z (literal 0-3)
     * @param W			Index for which component to use for W (literal 0-3)
     * @return			The swizzled vector
     */
    #define VectorSwizzle( Vec, X, Y, Z, W )	_mm_shuffle_ps( Vec, Vec, VECTOR_SHUFFLE_MASK(X, Y, Z, W) )

    /**
     * Returns a bitwise equivalent vector based on 4 DWORDs.
     *
     * @param X		1st uint32 component
     * @param Y		2nd uint32 component
     * @param Z		3rd uint32 component
     * @param W		4th uint32 component
     * @return		Bitwise equivalent vector with 4 floats
     */
    FORCEINLINE VectorRegister MakeVectorRegister(uint32 X, uint32 Y, uint32 Z, uint32 W)
    {
        union { VectorRegister v; VectorRegisterInt i; } Tmp;

        Tmp.i = _mm_setr_epi32(X, Y, Z, W);
        return Tmp.v;
    }

    /**
     * Returns a vector based on 4 FLOATs.
     *
     * @param X		1st float component
     * @param Y		2nd float component
     * @param Z		3rd float component
     * @param W		4th float component
     * @return		Vector of the 4 FLOATs
     */
    FORCEINLINE VectorRegister MakeVectorRegister(float X, float Y, float Z, float W)
    {
        return _mm_setr_ps(X, Y, Z, W);
    }

    /**
    * Returns a vector based on 4 int32.
    *
    * @param X		1st int32 component
    * @param Y		2nd int32 component
    * @param Z		3rd int32 component
    * @param W		4th int32 component
    * @return		Vector of the 4 int32
    */
    FORCEINLINE VectorRegisterInt MakeVectorRegisterInt(int32 X, int32 Y, int32 Z, int32 W)
    {
        return _mm_setr_epi32(X, Y, Z, W);
    }

    /**
     * Returns a vector with all zeros.
     *
     * @return		VectorRegister(0.0f, 0.0f, 0.0f, 0.0f)
     */
    FORCEINLINE VectorRegister VectorZero(void)
    {
        return _mm_setzero_ps();
    }

    /**
     * Returns an component from a vector.
     *
     * @param Vec				Vector register
     * @param ComponentIndex	Which component to get, X=0, Y=1, Z=2, W=3
     * @return					The component as a float
     */
    FORCEINLINE float VectorGetComponent(VectorRegister Vec, uint32 ComponentIndex)
    {
        return (((float*)&(Vec))[ComponentIndex]);
    }

    /**
     * Loads 4 FLOATs from unaligned memory.
     *
     * @param Ptr	Unaligned memory pointer to the 4 FLOATs
     * @return		VectorRegister(Ptr[0], Ptr[1], Ptr[2], Ptr[3])
     */
    FORCEINLINE VectorRegister VectorLoad(const void* Ptr)
    {
        return _mm_loadu_ps((float*)(Ptr));
    }

    /**
     * Adds two vectors (component-wise) and returns the result.
     *
     * @param Vec1	1st vector
     * @param Vec2	2nd vector
     * @return		VectorRegister( Vec1.x + Vec2.x, Vec1.y + Vec2.y, Vec1.z + Vec2.z, Vec1.w + Vec2.w )
     */
    FORCEINLINE VectorRegister VectorAdd(const VectorRegister& Vec1, const VectorRegister& Vec2)
    {
        return _mm_add_ps(Vec1, Vec2);
    }

    // This is only marked with inline, because GCC cannot inline this vector intrinsic function.
    inline VectorRegister VectorHorizontalAdd(const VectorRegister& Vec1, const VectorRegister& Vec2)
    {
        return _mm_hadd_ps(Vec1, Vec2);
    }

    /**
     * Subtracts a vector from another (component-wise) and returns the result.
     *
     * @param Vec1	1st vector
     * @param Vec2	2nd vector
     * @return		VectorRegister( Vec1.x - Vec2.x, Vec1.y - Vec2.y, Vec1.z - Vec2.z, Vec1.w - Vec2.w )
     */
    FORCEINLINE VectorRegister VectorSubtract(const VectorRegister& Vec1, const VectorRegister& Vec2)
    {
        return _mm_sub_ps(Vec1, Vec2);
    }

    /**
     * Multiplies two vectors (component-wise) and returns the result.
     *
     * @param Vec1	1st vector
     * @param Vec2	2nd vector
     * @return		VectorRegister( Vec1.x * Vec2.x, Vec1.y * Vec2.y, Vec1.z * Vec2.z, Vec1.w * Vec2.w )
     */
    FORCEINLINE VectorRegister VectorMultiply(const VectorRegister& Vec1, const VectorRegister& Vec2)
    {
        return _mm_mul_ps(Vec1, Vec2);
    }

    /**
     * Divides two vectors (component-wise) and returns the result.
     *
     * @param Vec1	1st vector
     * @param Vec2	2nd vector
     * @return		VectorRegister( Vec1.x / Vec2.x, Vec1.y / Vec2.y, Vec1.z / Vec2.z, Vec1.w / Vec2.w )
     */
    FORCEINLINE VectorRegister VectorDivide(const VectorRegister& Vec1, const VectorRegister& Vec2)
    {
        return _mm_div_ps(Vec1, Vec2);
    }

}