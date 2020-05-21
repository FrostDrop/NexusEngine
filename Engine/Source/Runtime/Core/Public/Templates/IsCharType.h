#pragma once

#include "CoreTypes.h"


namespace Nexus
{

    /**
     * TIsCharType
     */
    template<typename T> struct TIsCharType { enum { Value = false }; };
    template<>           struct TIsCharType<AnsiChar> { enum { Value = true }; };
    template<>           struct TIsCharType<WideChar> { enum { Value = true }; };

}