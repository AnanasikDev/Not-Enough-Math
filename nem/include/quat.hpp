#pragma once

#include "config.hpp"
#include "err.hpp"
#include "utils.hpp"
#include "vec.hpp"
#include "vec_utils.hpp"

namespace nem
{
    template <typename T> struct quat
    {
    T s = 0,                 // scalar
        x = 0, y = 0, z = 0; // vector

    // static constexpr quat NaN() { quat{ std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN(),
    // std::numeric_limits<T>::quiet_NaN(), std::numeric_limits<T>::quiet_NaN() }; }

    constexpr quat &operator*=(const quat &other)
    {
        quat &q = *this;
        const quat &p = other;
        /* from wikipedia
        a = a1a2 - b1b2 - c1c2 - d1d2
        b = a1b2 + b1a2 + c1d2 - d1c2
        c = a1c2 - b1d2 + c1a2 + d1b2
        d = a1d2 + b1c2 - c1b2 + d1a2

        s = s1s2 - x1x2 - y1y2 - z1z2
        x = s1x2 + x1s2 + y1z2 - z1y2
        y = s1y2 - x1z2 + y1s2 + z1x2
        z = s1z2 + x1y2 - y1x2 + z1s2

        s = q.s * p.s - q.x * p.x - q.y * p.y - q.z * p.z
        x = q.s * p.x + q.x * p.s + q.y * p.z - q.z * p.y
        y = q.s * p.y - q.x * p.z + q.y * p.s + q.z * p.x
        z = q.s * p.z + q.x * p.y - q.y * p.x + q.z * p.s
        */

        decltype(q.s) rs = q.s * p.s - q.x * p.x - q.y * p.y - q.z * p.z;
        decltype(q.x) rx = q.s * p.x + q.x * p.s + q.y * p.z - q.z * p.y;
        decltype(q.y) ry = q.s * p.y - q.x * p.z + q.y * p.s + q.z * p.x;
        decltype(q.z) rz = q.s * p.z + q.x * p.y - q.y * p.x + q.z * p.s;
        this->s = rs;
        this->x = rx;
        this->y = ry;
        this->z = rz;
        return *this;
    }

    constexpr friend quat operator*(quat lhs, const quat &rhs)
    {
        lhs *= rhs;
        return lhs;
    }

    constexpr quat &operator*=(T scalar)
    {
        this->s = s * scalar;
        this->x = x * scalar;
        this->y = y * scalar;
        this->z = z * scalar;
        return *this;
    }

    constexpr friend quat operator*(quat q, T scalar)
    {
        q *= scalar;
        return q;
    }

    constexpr quat &operator/=(T scalar)
    {
        // TODO: add 0 division protection with nem::err
        return (*this *= (T{1.0} / scalar));
    }

    constexpr friend quat operator/(quat q, T scalar)
    {
        q /= scalar;
        return q;
    }

    constexpr quat &operator+=(const quat &other)
    {
        this->s += other.s;
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
        return *this;
    }

    constexpr friend quat operator+(quat lhs, const quat &rhs)
    {
        lhs += rhs;
        return lhs;
    }

    constexpr friend quat operator-(quat q)
    {
        return quat{-q.s, -q.x, -q.y, -q.z};
    }

    constexpr friend nem::BaseVector3<T> operator*(const quat& q, const nem::BaseVector3<T>& v)
    {
        const nem::BaseVector3<T> w(q.x, q.y, q.z);
        const T a = q.s;
        return (v + (T)2.0 * a * nem::cross(w, v) + (T)2.0 * (nem::cross(w, nem::cross(w, v))));
    }
};

    using quatr = quat<nem::real>;

} // namespace nem