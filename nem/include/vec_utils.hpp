#pragma once

#include "utils.hpp"
#include "vec.hpp"
#include <cmath>

namespace nem
{
    template<typename Derived, typename T, size_t N>
    inline bool is_nearly_zero(const BaseVectorT<Derived, T, N>& v)
    {
        for (size_t c = 0; c < N; ++c)
        {
            if (!nem::is_nearly_zero(v.comp_r(c)))
            {
                return false;
            }
        }
        return true;
    }

    template<typename Derived, typename T, size_t N>
    inline bool is_nearly_zero(const BaseVectorT<Derived, T, N>&& v)
    {
        for (size_t c = 0; c < N; ++c)
        {
            if (!nem::is_nearly_zero(v.comp_r(c)))
            {
                return false;
            }
        }
        return true;
    }

    template<typename Derived, typename T, size_t N>
    inline T dot(const BaseVectorT<Derived, T, N>& a, const BaseVectorT<Derived, T, N>& b)
    {
        T result = (T)0.0;
        for (size_t c = 0; c < N; ++c)
        {
            result += a.comp_r(c) * b.comp_r(c);
        }
        return result;
    }

    template <typename T>
    inline BaseVector3<T> cross(const BaseVector3<T>& a, const BaseVector3<T>& b)
    {
        return BaseVector3<T>(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }

    template<typename Derived, typename T, size_t N>
    inline T horizontal_sum(const BaseVectorT<Derived, T, N>& v)
    {
        T result = (T)0.0;
        for (size_t c = 0; c < N; ++c)
        {
            result += v.comp_r(c);
        }
        return result;
    }

    template<typename Derived, typename T, size_t N>
    inline T horizontal_mul(const BaseVectorT<Derived, T, N>& v)
    {
        T result = (T)1.0;
        for (size_t c = 0; c < N; ++c)
        {
            result *= v.comp_r(c);
        }
        return result;
    }

    template<typename Derived, typename T, size_t N>
    inline Derived reflect(const BaseVectorT<Derived, T, N>& vector, const BaseVectorT<Derived, T, N>& normal)
    {
        return vector - (T)2.0 * nem::dot(vector, normal) * normal;
    }

    template<typename Derived, typename T, size_t N>
    static constexpr Derived lerp(const BaseVectorT<Derived, T, N>& a, const BaseVectorT<Derived, T, N>& b, float t)
    {
        Derived result;
        for (size_t i = 0; i < N; ++i)
        {
            result.comp_rw(i) = (T)nem::lerp(a.comp_r(i), b.comp_r(i), t);
        }
        return result;
    }

    template<typename Derived, typename T, size_t N>
    constexpr T sqrLength(const BaseVectorT<Derived, T, N>& vec)
    {
        T sum{};
        for (size_t i = 0; i < N; ++i)
        {
            sum += vec.comp_r(i) * vec.comp_r(i);
        }
        return sum;
    }

    template<typename Derived, typename T, size_t N>
    T length(const BaseVectorT<Derived, T, N>& vec)
    {
        return std::sqrtf(nem::sqrLength(vec));
    }

    template<typename Derived, typename T, size_t N>
    Derived normalize(const BaseVectorT<Derived, T, N>& vec)
    {
        Derived result;
        T len = nem::length(vec);

        if (nem::is_nearly_zero(len))
        {
            return nem::error::invalid_result<Derived>();
        }

        for (size_t i = 0; i < N; ++i)
        {
            result.comp_rw(i) = vec.comp_r(i) / len;
        }

        return result;
    }

    template<typename T>
    bool orthogonal_3d_basis(const BaseVector3<T>& vector, BaseVector3<T>& b1, BaseVector3<T>& b2)
    {
        if (nem::is_nearly_zero(vector))
        {
            nem::error::report_invalid(nem::error::Type::ZeroVector);
            return false;
        }

        if (nem::abs(vector.z) < 0.999f)
        {
            b1 = nem::normalize(nem::cross(vector, BaseVector3<T>(0, 0, 1)));
        }
        else
        {
            b1 = nem::normalize(nem::cross(vector, BaseVector3<T>(1, 0, 0)));
        }

        b2 = nem::cross(vector, b1);

        return true;
    }
}