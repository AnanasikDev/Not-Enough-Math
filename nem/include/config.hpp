#pragma once

// options can be defined here, in CMake, in IDE project settings preprocessor definitions or in building arguments

#include <concepts>
#include <cassert>

#ifdef NEM_NO_INLINE
    #define NEM_INLINE
#else
    #define NEM_INLINE inline
#endif

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
    NEM_INLINE const char* GET_C_STRING(nem_string str) { return str.c_str(); }
#else
    using nem_string = const char*;
    constexpr bool USE_C_STRING = true;
    NEM_INLINE const char* GET_C_STRING(nem_string str) { return str; }
#endif

#if defined(NEM_USE_DOUBLE_PRECISION)
    using real = double;
#else
    using real = float;
#endif

    constexpr float  fEps  = 1e-6f;
    constexpr double dEps = 1e-9;
    constexpr long double ldEps = 1e-14;

    template <typename T>
    concept scalar_type = std::integral<T> || std::floating_point<T>;

    template <nem::scalar_type T>
    constexpr T Eps()
    {
        if      constexpr (std::is_same_v<T, float>) return T{ nem::fEps };
        else if constexpr (std::is_same_v<T, double>) return T{ nem::dEps };
        else if constexpr (std::is_same_v<T, long double>) return T{ nem::ldEps };
        return (T)0;
    }
}
