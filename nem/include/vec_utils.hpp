#pragma once

#include "config.hpp"
#include "utils.hpp"
#include "vec.hpp"
#include "power.hpp"

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