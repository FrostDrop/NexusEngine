#pragma once

#include "CoreTypes.h"
#include "IsIntegral.h"
#include "IsPointer.h"

namespace Nexus
{

    /**
     *
     */
    struct CORE_API FAlign
    {

        /**
         * Aligns a value to the nearest higher multiple of 'Alignment', which must be a power of two.
         *
         * @param  Val        The value to align.
         * @param  Alignment  The alignment value, must be a power of two.
         *
         * @return The value aligned up to the specified alignment.
         */
        template <typename T>
        static FORCEINLINE constexpr T Align(T Val, uint64 Alignment)
        {
            static_assert(TIsIntegral<T>::Value || TIsPointer<T>::Value, "Align expects an integer or pointer type.");

            return (T)(((uint64)Val + Alignment - 1) & ~(Alignment - 1));
        }

    };



}