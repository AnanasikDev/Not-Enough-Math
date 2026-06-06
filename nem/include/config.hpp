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
    template <typename T>
    concept scalar_type = std::integral<T> || std::floating_point<T>;

    struct safe_t   { explicit constexpr safe_t()   = default; };
    struct unsafe_t { explicit constexpr unsafe_t() = default; };

    inline constexpr safe_t   safe{};
    inline constexpr unsafe_t unsafe{};

    enum class Precision : unsigned char
    {
        Fast = 0,
        Accurate = 1
    };

    inline constexpr nem::Precision default_precision = nem::Precision::Fast;

    template <nem::scalar_type T>
    constexpr T abs_to_rel_error(T x, T abs_error)
    {
        if (x < 0)
            x = -x;
        if constexpr (std::is_floating_point_v<T>)
        {
            return (x + abs_error) * abs_error;
        }
        else
        {
            return (T)0;
        }
    }

    template <nem::scalar_type T>
    constexpr T eps()
    {
        if      constexpr (std::is_same_v<T, float>) return T{ 1e-6f };
        else if constexpr (std::is_same_v<T, double>) return T{ 1e-9 };
        else if constexpr (std::is_same_v<T, long double>) return T{ 1e-14 };
        return (T)0;
    }

    namespace fast
    {
    
    inline constexpr nem::Precision mode = nem::default_precision;

    template <nem::scalar_type T>
    constexpr T abs_error()
    {
        if      constexpr (std::is_same_v<T, float>) return T{ 3.0e-2f }; // absolute 0.03 or 3.0% relative
        else if constexpr (std::is_same_v<T, double>) return T{ 3e-3 }; // absolute 0.003 or 0.3% relative
        else if constexpr (std::is_same_v<T, long double>) return T{ 1e-4 }; // absolute 0.001 or 0.01% relative
        return (T)0;
    }
    
    template <nem::scalar_type T>
    constexpr T rel_error(T x)
    {
        return nem::abs_to_rel_error(x, nem::fast::abs_error<T>());
    }

    } // namespace fast


    namespace accurate
    {

    inline constexpr nem::Precision mode = nem::Precision::Accurate;

    template <nem::scalar_type T>
    constexpr T abs_error()
    {
        if      constexpr (std::is_same_v<T, float>) return T{ 8.0e-3f }; // absolute 0.008 or 0.8% relative
        else if constexpr (std::is_same_v<T, double>) return T{ 5e-4 }; // absolute 0.0005 or 0.05% relative
        else if constexpr (std::is_same_v<T, long double>) return T{ 1e-5 }; // absolute 0.00001 or 0.001% relative
        return (T)0;
    }
    
    template <nem::scalar_type T>
    constexpr T rel_error(T x)
    {
        return nem::abs_to_rel_error(x, nem::fast::abs_error<T>());
    }

    } // namespace accurate

    template <nem::scalar_type T, nem::Precision Prec = nem::default_precision>
    constexpr T abs_error()
    {
        if constexpr (Prec == nem::fast::mode)
        {
            return nem::fast::abs_error<T>();
        }

        if constexpr (Prec == nem::accurate::mode)
        {
            return nem::accurate::abs_error<T>();
        }
    }
    
    template <nem::scalar_type T, nem::Precision Prec = nem::default_precision>
    constexpr T rel_error(T x)
    {
        if constexpr (Prec == nem::fast::mode)
        {
            return nem::fast::rel_error<T>(x);
        }

        if constexpr (Prec == nem::accurate::mode)
        {
            return nem::accurate::rel_error<T>(x);
        }
    }
}
