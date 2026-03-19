#pragma once

// options can be defined here, in CMake, in IDE project settings preprocessor definitions or in building arguments

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
    const char* GET_C_STRING(nem_string str) { return str.c_str(); }
#else
    using nem_string = const char*;
    constexpr bool USE_C_STRING = true;
    const char* GET_C_STRING(nem_string str) { return str; }
#endif

#if defined(NEM_USE_DOUBLE_PRECISION)
    using real = double;
#else
    using real = float;
#endif
}
