#pragma once

#include "CoreTypes.h"


namespace Nexus
{

    /**
     * TIsReferenceType
     */
    template<typename T> struct TIsReferenceType        { enum { Value = false }; };
    template<typename T> struct TIsReferenceType<T&>    { enum { Value = true }; };
    template<typename T> struct TIsReferenceType<T&&>   { enum { Value = true }; };

}