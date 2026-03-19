#pragma once

#include "utils.hpp"
#include "vec.hpp"

namespace nem
{
#define VECTEMP template<typename Derived, typename T, size_t N>
#define VECTYPE BaseVector<Derived, T, N>
    
    VECTEMP inline bool is_nearly_zero(VECTYPE v)
    {
        for (size_t c = 0; c < N; ++c) if (!nem::is_nearly_zero(v.comp_r(c)) return false;
        return true;
    }

    VECTEMP inline T dot(VECTYPE a, VECTYPE b)
    {
        T result = (T)0.0;
        for (size_t c = 0; c < N; ++c) result += a.comp_r(c) * a.comp_r(c);
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

    VECTEMP inline T comp_sum(VECTYPE v)
    {
        T result = (T)0.0;
        for (size_t c = 0; c < N; ++c) result += v.comp_r(c);
        return result;
    }

    VECTEMP inline T comp_mul(VECTYPE v)
    {
        T result = (T)1.0;
        for (size_t c = 0; c < N; ++c) result *= v.comp_r(c);
        return result;
    }

    template<typename Derived, typename T, size_t N>
    inline float3 reflect(const float3& vector, const float3& normal) { return vector + (T)2.0 *  }
}