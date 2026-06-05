#pragma once

#include "config.hpp"
#include "utils.hpp"
#include "vec.hpp"
#include "power.hpp"

namespace nem
{
    template<typename vec_derived_t, typename T, size_t N>
    NEM_INLINE bool is_zero(const nem::base_vector_t<vec_derived_t, T, N>& v)
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

    template<typename vec_derived_t, typename T, size_t N>
    NEM_INLINE bool is_zero(const nem::base_vector_t<vec_derived_t, T, N>&& v)
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

    template<typename vec_derived_t, typename T, size_t N>
    NEM_INLINE T dot(const nem::base_vector_t<vec_derived_t, T, N>& a, const nem::base_vector_t<vec_derived_t, T, N>& b)
    {
        T result = (T)0.0;
        for (size_t c = 0; c < N; ++c)
        {
            result += a[c] * b[c];
        }
        return result;
    }

    template <typename T>
    NEM_INLINE nem::base_vector_3<T> cross(const nem::base_vector_3<T>& a, const nem::base_vector_3<T>& b)
    {
        return nem::base_vector_3<T>(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    template<typename vec_derived_t, typename T, size_t N>
    NEM_INLINE T horizontal_sum(const nem::base_vector_t<vec_derived_t, T, N>& v)
    {
        T result = (T)0.0;
        for (size_t c = 0; c < N; ++c)
        {
            result += v[c];
        }
        return result;
    }

    template<typename vec_derived_t, typename T, size_t N>
    NEM_INLINE T horizontal_mul(const nem::base_vector_t<vec_derived_t, T, N>& v)
    {
        T result = (T)1.0;
        for (size_t c = 0; c < N; ++c)
        {
            result *= v[c];
        }
        return result;
    }

    template<typename vec_derived_t, typename T, size_t N>
    NEM_INLINE vec_derived_t reflect(const nem::base_vector_t<vec_derived_t, T, N>& vector, const nem::base_vector_t<vec_derived_t, T, N>& normal)
    {
        return vector - (T)2.0 * nem::dot(vector, normal) * normal;
    }

    template<typename vec_derived_t, typename T, size_t N>
    static constexpr vec_derived_t lerp(const nem::base_vector_t<vec_derived_t, T, N>& a, const nem::base_vector_t<vec_derived_t, T, N>& b, float t)
    {
        vec_derived_t result;
        for (size_t i = 0; i < N; ++i)
        {
            result[i] = (T)nem::lerp(a[i], b[i], t);
        }
        return result;
    }

    template<typename vec_derived_t, typename T, size_t N>
    constexpr T sqrLength(const nem::base_vector_t<vec_derived_t, T, N>& vec)
    {
        T sum{};
        for (size_t i = 0; i < N; ++i)
        {
            sum += vec[i] * vec[i];
        }
        return sum;
    }

    template<typename vec_derived_t, typename T, size_t N>
    T length(const nem::base_vector_t<vec_derived_t, T, N>& vec)
    {
        return nem::sqrt(nem::sqrLength(vec));
    }

    template<typename vec_derived_t, typename T, size_t N>
    vec_derived_t normalize(const nem::base_vector_t<vec_derived_t, T, N>& vec)
    {
        vec_derived_t result;
        T len = nem::length(vec);

        if (nem::is_zero(len))
        {
            return nem::error::invalid_result<vec_derived_t>();
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
    bool orthogonal_3d_basis(const nem::base_vector_3<T>& vector, nem::base_vector_3<T>& b1, nem::base_vector_3<T>& b2)
    {
        if (nem::is_zero(vector))
        {
            nem::error::report_invalid(nem::error::Kind::ZeroVector);
            return false;
        }

        if (nem::abs(vector.z) < 0.999f) // TODO : fix magic precision number
        {
            b1 = nem::normalize(nem::cross(vector, base_vector_3<T>(0, 0, 1)));
        }
        else
        {
            b1 = nem::normalize(nem::cross(vector, base_vector_3<T>(1, 0, 0)));
        }

        b2 = nem::cross(vector, b1);

        return true;
    }
}