#pragma once

#include "CoreTypes.h"


namespace Nexus
{

    /**
     * TIsLValueReferenceType
     */
    template<typename T> struct TIsLValueReferenceType { enum { Value = false }; };
    template<typename T> struct TIsLValueReferenceType<T&> { enum { Value = true }; };

}