#pragma once

#include <concepts>

namespace nem
{
    #if defined(__clang__) || defined(__GNUC__)

        #define NEM_TRAP() __builtin_trap()
        #ifdef _DEBUG
            #define NEM_UNREACHABLE() NEM_TRAP()
        #else
            #define NEM_UNREACHABLE() __builtin_unreachable()
        #endif

        template <std::floating_point T> T _nem_sqrt(T x) noexcept
        {
            if constexpr (std::is_same_v<T, float>)
            {
                return __builtin_sqrtf(x);
            }
            else if constexpr (std::is_same_v<T, double>)
            {
                return __builtin_sqrt(x);
            }
            else if constexpr (std::is_same_v<T, long double>)
            {
                return __builtin_sqrtl(x);
            }
            NEM_UNREACHABLE();
        }

        template <std::floating_point T> constexpr T _nem_fabs(T x) noexcept
        {
            if constexpr (std::is_same_v<T, float>)
            {
                return __builtin_fabsf(x);
            }
            else if constexpr (std::is_same_v<T, double>)
            {
                return __builtin_fabs(x);
            }
            else if constexpr (std::is_same_v<T, long double>)
            {
                return __builtin_fabsl(x);
            }
            NEM_UNREACHABLE();
        }

        template <std::floating_point T> constexpr bool  _nem_isnan(T x) noexcept    { return __builtin_isnan(x);    }
        template <std::floating_point T> constexpr bool  _nem_isfinite(T x) noexcept { return __builtin_isfinite(x); }

        template <typename T> constexpr T _nem_copysign(T to, const T from) noexcept
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
                const bool diff = (to < 0) ^ (from < 0);
                return diff ? -to : to;
            }
            else
            {
                NEM_UNREACHABLE();
            }
        }
        
    #elif defined(_MSC_VER)
        #include <intrin.h>
        #include <math.h>
        inline float _nem_sqrtf(float x)    noexcept { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x))); }
        inline float _nem_fabsf(float x)    noexcept { return fabsf(x);    }
        inline bool  _nem_isnan(float x)    noexcept { return x != x;      }
        inline bool  _nem_isfinite(float x) noexcept { return (x == x) && (x - x == 0.0f); }
        #define NEM_TRAP() __debugbreak()
        #define NEM_UNREACHABLE() __assume(0)
    #else
        #error "Unsupported compiler"
    #endif
}