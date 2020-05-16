#pragma once

#include "CoreTypes.h"

#include "RemoveReference.h"
#include "AreTypesEqual.h"
#include "IsLValueReference.h"

namespace Nexus
{

    /**
     * MoveTemp will cast a reference to an rvalue reference.
     * This is UE's equivalent of std::move except that it will not compile when passed an rvalue or
     * const object, because we would prefer to be informed when MoveTemp will have no effect.
     */
    template <typename T>
    FORCEINLINE typename TRemoveReference<T>::Type&& MoveTemp(T&& Obj)
    {
        using FCastType = typename TRemoveReference<T>::Type;

        // Validate that we're not being passed an rvalue or a const object - the former is redundant, the latter is almost certainly a mistake
        static_assert(TIsLValueReferenceType<T>::Value, "MoveTemp called on an rvalue.");
        static_assert(!TAreTypesEqual<FCastType&, const FCastType&>::Value, "MoveTemp called on a const object.");

        return static_cast<FCastType&&>(Obj);
    }

    /**
     * MoveTemp will cast a reference to an rvalue reference.
     * This is UE's equivalent of std::move.  It doesn't static assert like MoveTemp, because it is useful in
     * templates or macros where it's not obvious what the argument is, but you want to take advantage of move semantics
     * where you can but not stop compilation.
     */
    template <typename T>
    FORCEINLINE typename TRemoveReference<T>::Type&& MoveTempIfPossible(T&& Obj)
    {
        using FCastType = typename TRemoveReference<T>::Type;

        return static_cast<FCastType&&>(Obj);
    }

}