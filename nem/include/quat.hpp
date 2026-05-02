#pragma once

#include "config.hpp"

namespace nem
{
    template <typename T>
    struct quat
    {
        T s = 0,               // scalar
          x = 0, y = 0, z = 0; // vector

        constexpr quat& operator*=(const quat& other)
        {
            this->s = z * other.s + s * other.z + x * other.y - y * other.x;
            this->x = z * other.x - s * other.y + x * other.z + y * other.s;
            this->y = z * other.y + s * other.x - x * other.s + y * other.z;
            this->z = z * other.z - s * other.s - x * other.x - y * other.y;
            return *this;
        }

        constexpr friend quat operator*(quat lhs, const quat& rhs)
        {
            lhs *= rhs;
            return lhs;
        }
    };

    using quatr = quat<nem::real>;
}