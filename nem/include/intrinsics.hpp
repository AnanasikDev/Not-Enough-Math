#pragma once

#include <concepts>
#include <type_traits>

#if defined(_MSC_VER)
    #include <intrin.h>
    #include <math.h>
#endif

// implements compiler/platform specific low-level instructions that are then used in the API. Uses compiler-specific
// builtins, SIMD instrinsics or standard math inlinement to avoid dependencies.
// MSVC implementation isn't worked on as much as Clang/GCC are, so issues with it may be overseen. It is tested in
// CI/CD however.
// This code was restructured by Anthropic Claude and until fully tested and refactored may contain artifacts.

namespace nem
{
    namespace intr
    {
#if defined(__clang__) || defined(__GNUC__)
    #define NEM_TRAP()        __builtin_trap()
    #ifdef _DEBUG
        #define NEM_UNREACHABLE() NEM_TRAP()
    #else
        #define NEM_UNREACHABLE() __builtin_unreachable()
    #endif

#elif defined(_MSC_VER)
    #define NEM_TRAP()        __debugbreak()
    #define NEM_UNREACHABLE() __assume(0)

#else
    #error "Unsupported compiler"
#endif

#if defined(__clang__) || defined(__GNUC__)
    template <std::floating_point T>
    T _nem_sqrt(T x) noexcept
    {
        if constexpr (std::is_same_v<T, float>)
        {
            return __builtin_sqrtf(x);
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return __builtin_sqrt(x);
        }
        else
        {
            return __builtin_sqrtl(x);
        }
    }

#elif defined(_MSC_VER)
    template <std::floating_point T>
    T _nem_sqrt(T x) noexcept
    {
        if constexpr (std::is_same_v<T, float>)
        {
            return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x)));
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return ::sqrt(x);
        }
        else
        {
            return ::sqrtl(x);
        }
    }
#endif

#if defined(__clang__) || defined(__GNUC__)
    template <std::floating_point T>
    constexpr T _nem_fabs(T x) noexcept
    {
        if constexpr (std::is_same_v<T, float>)
        {
            return __builtin_fabsf(x);
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return __builtin_fabs(x);
        }
        else
        {
            return __builtin_fabsl(x);
        }
    }

#elif defined(_MSC_VER)
    template <std::floating_point T>
    T _nem_fabs(T x) noexcept
    {
        if constexpr (std::is_same_v<T, float>)
        {
            return ::fabsf(x);
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return ::fabs(x);
        }
        else
        {
            return ::fabsl(x);
        }
    }
#endif

    template <std::floating_point T> bool _nem_isnan(T x) noexcept { return x != x; }
    template <std::integral T> bool _nem_isnan(T) noexcept { return false;  }

    template <std::floating_point T>
    bool _nem_isfinite(T x) noexcept
    {
        return (x == x) && (x - x == T{0});
    }
    template <std::integral T> bool _nem_isfinite(T) noexcept { return true; }

#if defined(__clang__) || defined(__GNUC__)
    template <typename T>
    constexpr T _nem_copysign(T to, T from) noexcept
    {
        if constexpr (std::is_same_v<T, float>)
        {
            return __builtin_copysignf(to, from);
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return __builtin_copysign(to, from);
        }
        else if constexpr (std::is_same_v<T, long double>)
        {
            return __builtin_copysignl(to, from);
        }
        else if constexpr (std::is_integral_v<T>)
        {
            const bool flip = (to < T{0}) ^ (from < T{0});
            return flip ? -to : to;
        }
        else
        {
            NEM_UNREACHABLE();
        }
    }

#elif defined(_MSC_VER)
    template <typename T>
    T _nem_copysign(T to, T from) noexcept
    {
        if constexpr (std::is_same_v<T, float>)
        {
            return ::copysignf(to, from);
        }
        else if constexpr (std::is_same_v<T, double>)
        {
            return ::copysign(to, from);
        }
        else if constexpr (std::is_same_v<T, long double>)
        {
            return ::copysignl(to, from);
        }
        else if constexpr (std::is_integral_v<T>)
        {
            const bool flip = (to < T{0}) ^ (from < T{0});
            return flip ? -to : to;
        }
        else { NEM_UNREACHABLE(); }
    }
#endif

    } // namespace intr
} // namespace nem