#pragma once

#include "CoreTypes.h"


namespace Nexus
{

    /**
     * TRemoveCV<type> will remove any const/volatile qualifiers from a type.
     * (based on std::remove_cv<>
     * note: won't remove the const from "const int*", as the pointer is not const
     */
    template <typename T> struct TRemoveConstVolatile                   { typedef T Type; };
    template <typename T> struct TRemoveConstVolatile<const T>          { typedef T Type; };
    template <typename T> struct TRemoveConstVolatile<volatile T>       { typedef T Type; };
    template <typename T> struct TRemoveConstVolatile<const volatile T> { typedef T Type; };

}