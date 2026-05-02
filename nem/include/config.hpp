#pragma once

// options can be defined here, in CMake, in IDE project settings preprocessor definitions or in building arguments

#include <concepts>
#include <cassert>

namespace nem
{
#if defined(NEM_ERR_THROW) 
    constexpr bool ERR_THROW = true;
#else
    constexpr bool ERR_THROW = false;
#endif

#if defined(NEM_ERR_LOG) 
    constexpr bool ERR_LOG = true;
#else
    constexpr bool ERR_LOG = false;
#endif

#if defined(NEM_ERR_USE_NAN) 
    constexpr bool ERR_USE_NAN = true;
#else
    constexpr bool ERR_USE_NAN = false;
#endif

#if defined(NEM_ERR_SAFE_FALLBACK) 
    constexpr bool ERR_SAFE_FALLBACK = true;
#else
    constexpr bool ERR_SAFE_FALLBACK = false;
#endif

#if defined(NEM_CPP_STRING)
#include <string>
    using nem_string = std::string;
    constexpr bool USE_C_STRING = false;
    inline const char* GET_C_STRING(nem_string str) { return str.c_str(); }
#else
    using nem_string = const char*;
    constexpr bool USE_C_STRING = true;
    inline const char* GET_C_STRING(nem_string str) { return str; }
#endif

#if defined(NEM_USE_DOUBLE_PRECISION)
    using real = double;
#else
    using real = float;
#endif

    constexpr float  kEps  = 1e-5f;
    constexpr double kEpsD = 1e-9;

    template <typename T>
    constexpr T Eps()
    {
        if constexpr (std::is_same_v<T, float>)
            return T{ kEps };
        else if constexpr (std::is_floating_point_v<T>)
            return T{ kEpsD };
        else if constexpr (std::is_integral_v<T>)
            return T{ 0 };
        else
        {
            assert(false);
            return T{ kEpsD };
        }
    }
}
