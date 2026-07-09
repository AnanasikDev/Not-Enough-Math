#pragma once

#include "config.hpp"
#include "utils.hpp"
#include "vec.hpp"
#include "power.hpp"
#include <concepts>

namespace nem
{
    template<typename T, size_t N>
    NEM_INLINE bool is_zero(const nem::vec<T, N>& v)
    {
        for (size_t c = 0; c < N; ++c)
        {
            if (!nem::is_zero(v[c]))
            {
                return false;
            }
        }
        return true;
    }

    template<typename T, size_t N>
    NEM_INLINE bool is_zero(const nem::vec<T, N>&& v)
    {
        for (size_t c = 0; c < N; ++c)
        {
            if (!nem::is_zero(v[c]))
            {
                return false;
            }
        }
        return true;
    }

    /// -------------------------------------------
    /// Metadata
    /// -------------------------------------------

    template<typename T, size_t N>
    constexpr nem::vec<T, N> is_infinite(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::is_infinite(v[i]);
        }
        return result;
    }

    template<typename T, size_t N>
    constexpr nem::vec<T, N> is_nan(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::is_nan(v[i]);
        }
        return result;
    }

    /// -------------------------------------------
    /// Sign operations
    /// -------------------------------------------

    template<std::floating_point T, size_t N>
    constexpr nem::vec<T, N> copysign(const nem::vec<T, N>& to, const nem::vec<T, N>& from)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::copysign(to[i], from[i]);
        }
        return result;
    }

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> sign(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::sign(v[i]);
        }
        return result;
    }

    template<typename T, size_t N>
    constexpr nem::vec<T, N> abs(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::abs(v[i]);
        }
        return result;
    }

    /// -------------------------------------------
    /// Comparisons
    /// -------------------------------------------

    template<nem::scalar_type T, size_t N>
    constexpr bool is_zero_or_neg(const nem::vec<T, N>& v)
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (!nem::is_zero_or_neg(v[i]))
            {
                return false;
            }
        }
        return true;
    }

    template<nem::scalar_type T, size_t N>
    constexpr bool equal(const nem::vec<T, N>& a, const nem::vec<T, N>& b)
    {
        for (size_t i = 0; i < N; ++i)
        {
            if (!nem::equal(a[i], b[i]))
            {
                return false;
            }
        }
        return true;
    }

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> get_max(const nem::vec<T, N>& a, const nem::vec<T, N>& b)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::get_max(a[i], b[i]);
        }
        return result;
    }

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> get_min(const nem::vec<T, N>& a, const nem::vec<T, N>& b)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::get_min(a[i], b[i]);
        }
        return result;
    }

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> average(const nem::vec<T, N>& a, const nem::vec<T, N>& b)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::average(a[i], b[i]);
        }
        return result;
    }

    /// -------------------------------------------
    /// Powers
    /// -------------------------------------------

    template<typename T, size_t N>
    constexpr nem::vec<T, N> pow2(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::pow2(v[i]);
        }
        return result;
    }

    template<typename T, size_t N>
    constexpr nem::vec<T, N> pow3(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::pow3(v[i]);
        }
        return result;
    }

    template<typename T, size_t N>
    constexpr nem::vec<T, N> pow4(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::pow4(v[i]);
        }
        return result;
    }

    template<typename T, size_t N>
    constexpr nem::vec<T, N> sqr(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::sqr(v[i]);
        }
        return result;
    }

    template<typename T, size_t N>
    constexpr nem::vec<T, N> cube(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::cube(v[i]);
        }
        return result;
    }

    /// --------------------------------------------------------------------------------------
    /// Float truncation, fractional part, modulo (remainder), rounding, flooring, ceiling
    /// --------------------------------------------------------------------------------------

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> truncate(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::truncate(v[i]);
        }
        return result;
    }

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> floor(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::floor(v[i]);
        }
        return result;
    }

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> ceil(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::ceil(v[i]);
        }
        return result;
    }

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> mod(const nem::vec<T, N>& a, const nem::vec<T, N>& b)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::mod(a[i], b[i]);
        }
        return result;
    }

    template<std::floating_point T, size_t N>
    constexpr nem::vec<T, N> frac(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::frac(v[i]);
        }
        return result;
    }

    template<std::floating_point T, size_t N>
    constexpr nem::vec<T, N> round(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::round(v[i]);
        }
        return result;
    }

    /// -------------------------------------------
    /// Rounding, flooring and ceiling with step
    /// -------------------------------------------

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> floor(const nem::vec<T, N>& v, const nem::vec<T, N>& step)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::floor(v[i], step[i]);
        }
        return result;
    }

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> ceil(const nem::vec<T, N>& v, const nem::vec<T, N>& step)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::ceil(v[i], step[i]);
        }
        return result;
    }

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> round(const nem::vec<T, N>& v, const nem::vec<T, N>& step)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::round(v[i], step[i]);
        }
        return result;
    }

    /// -------------------------------------------
    /// Repeat, pingpong, clamp
    /// -------------------------------------------

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> repeat(const nem::vec<T, N>& value, const nem::vec<T, N>& lengthExcl)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::repeat(value[i], lengthExcl[i]);
        }
        return result;
    }

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> repeat(const nem::vec<T, N>& value, const nem::vec<T, N>& minIncl, const nem::vec<T, N>& maxExcl)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::repeat(value[i], minIncl[i], maxExcl[i]);
        }
        return result;
    }

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> pingpong(const nem::vec<T, N>& value, const nem::vec<T, N>& length)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::pingpong(value[i], length[i]);
        }
        return result;
    }

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> pingpong(const nem::vec<T, N>& value, const nem::vec<T, N>& minIncl, const nem::vec<T, N>& maxExcl)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::pingpong(value[i], minIncl[i], maxExcl[i]);
        }
        return result;
    }

    template<std::totally_ordered T, size_t N>
    constexpr nem::vec<T, N> clamp(const nem::vec<T, N>& value, const nem::vec<T, N>& minIncl, const nem::vec<T, N>& maxIncl)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::clamp(value[i], minIncl[i], maxIncl[i]);
        }
        return result;
    }

    template<std::totally_ordered T, size_t N>
    constexpr nem::vec<T, N> clamp01(const nem::vec<T, N>& value)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::clamp01(value[i]);
        }
        return result;
    }

    /// -------------------------------------------
    /// Interpolation
    /// -------------------------------------------

    template<typename T, size_t N>
    constexpr nem::vec<T, N> smoothstep(const nem::vec<T, N>& edge0, const nem::vec<T, N>& edge1, const nem::vec<T, N>& x)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::smoothstep(edge0[i], edge1[i], x[i]);
        }
        return result;
    }

    /// -------------------------------------------
    /// Linear mapping
    /// -------------------------------------------

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> remap(const nem::vec<T, N>& value, const nem::vec<T, N>& fromMin, const nem::vec<T, N>& fromMax,
                                    const nem::vec<T, N>& toMin, const nem::vec<T, N>& toMax)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::remap(value[i], fromMin[i], fromMax[i], toMin[i], toMax[i]);
        }
        return result;
    }

    /// -------------------------------------------
    /// Properties
    /// -------------------------------------------

    template<nem::scalar_type T, size_t N>
    constexpr nem::vec<T, N> is_whole(const nem::vec<T, N>& v)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = nem::is_whole(v[i]);
        }
        return result;
    }

    template<typename T, size_t N>
    NEM_INLINE T dot(const nem::vec<T, N>& a, const nem::vec<T, N>& b)
    {
        T result = (T)0.0;
        for (size_t c = 0; c < N; ++c)
        {
            result += a[c] * b[c];
        }
        return result;
    }

    template <typename T>
    NEM_INLINE nem::vec<T, 3> cross(const nem::vec<T, 3>& a, const nem::vec<T, 3>& b)
    {
        return nem::vec<T, 3>(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    template<typename T, size_t N>
    NEM_INLINE T horizontal_sum(const nem::vec<T, N>& v)
    {
        T result = (T)0.0;
        for (size_t c = 0; c < N; ++c)
        {
            result += v[c];
        }
        return result;
    }

    template<typename T, size_t N>
    NEM_INLINE T horizontal_mul(const nem::vec<T, N>& v)
    {
        T result = (T)1.0;
        for (size_t c = 0; c < N; ++c)
        {
            result *= v[c];
        }
        return result;
    }

    template<typename T, size_t N>
    NEM_INLINE nem::vec<T, N> reflect(const nem::vec<T, N>& vector, const nem::vec<T, N>& normal)
    {
        return vector - (T)2.0 * nem::dot(vector, normal) * normal;
    }

    template<typename T, size_t N>
    static constexpr nem::vec<T, N> lerp(const nem::vec<T, N>& a, const nem::vec<T, N>& b, float t)
    {
        nem::vec<T, N> result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = (T)nem::lerp(a[i], b[i], t);
        }
        return result;
    }

    template<typename T, size_t N>
    constexpr T sqr_length(const nem::vec<T, N>& vec)
    {
        T sum{};
        for (size_t i = 0; i < N; ++i)
        {
            sum += vec[i] * vec[i];
        }
        return sum;
    }

    template<typename T, size_t N>
    T length(const nem::vec<T, N>& vec)
    {
        return nem::sqrt(nem::sqr_length(vec));
    }

    template<typename T, size_t N>
    nem::vec<T, N> normalize(const nem::vec<T, N>& vec)
    {
        nem::vec<T, N> result;
        const T len = nem::length(vec);

        if (nem::is_zero(len))
        {
            return nem::error::invalid_result<nem::vec<T, N>>();
        }

        if constexpr (std::is_floating_point_v<T>)
        {
            const T fac = (T)1.0 / len;
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = vec[i] * fac;
            }
        }
        else
        {
            for (size_t i = 0; i < N; ++i)
            {
                result[i] = vec[i] / len;
            }
        }

        return result;
    }

    template<typename T>
    bool orthogonal_3d_basis(const nem::vec<T, 3>& vector, nem::vec<T, 3>& b1, nem::vec<T, 3>& b2)
    {
        if (nem::is_zero(vector))
        {
            nem::error::report_invalid(nem::error::Kind::ZeroVector);
            return false;
        }

        if (nem::abs(vector.z) < 0.999f) // TODO : fix magic precision number
        {
            b1 = nem::normalize(nem::cross(vector, nem::vec<T, 3>(0, 0, 1)));
        }
        else
        {
            b1 = nem::normalize(nem::cross(vector, nem::vec<T, 3>(1, 0, 0)));
        }

        b2 = nem::cross(vector, b1);

        return true;
    }
}