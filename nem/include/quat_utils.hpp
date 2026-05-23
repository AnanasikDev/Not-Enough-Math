#pragma once

#include "quat.hpp"
#include "vec.hpp"
#include "mat.hpp"
#include "utils.hpp"

namespace nem
{
    template <typename T = nem::real>
    constexpr T sqrLength(const nem::quat<T>& q)
    {
        return nem::sqr(q.s) + nem::sqr(q.x) + nem::sqr(q.y) + nem::sqr(q.z);
    }

    template <typename T = nem::real>
    NEM_INLINE T length(const nem::quat<T>& q)
    {
        return nem::sqrt(nem::sqrLength(q));
    }

    template <typename T = nem::real>
    NEM_INLINE nem::quat<T> normalize(nem::quat<T> q)
    {
        const T l = nem::length(q);
        q /= l;
        return q;
    }

    template<typename Derived, typename T = nem::real>
    constexpr nem::quat<T> make_quat(const nem::BaseVectorT<Derived, T, 4>& vec4)
    {
        return nem::quat<T> { vec4.x, vec4.y, vec4.z, vec4.w };
    }

    template<typename T = nem::real>
    constexpr nem::quat<T> make_quat(T scalar, T x, T y, T z)
    {
        return nem::quat<T> { scalar, x, y, z };
    }

    /// <summary>
    /// Conjugates the quaternion, yielding a quaternion with the same angle (scalar) but inverse axis (vector)
    /// </summary>
    template<typename T = nem::real>
    constexpr nem::quat<T> conjugate(const nem::quat<T>& q)
    {
        return nem::quat<T> { q.s, -q.x, -q.y, -q.z };
    }

    template<typename T = nem::real>
    constexpr nem::quat<T> inverse(const nem::quat<T>& q)
    {
        return nem::conjugate(q) / nem::sqrLength(q);
    }

    template<typename Derived, typename T = nem::real>
    nem::quat<T> from_axis_angle(const nem::BaseVectorT<Derived, T, 3>& axis, T angle)
    {
        const T half = angle * T{ 0.5 };
        const T s = T{ std::sin(half) };
        return nem::make_quat<T>(
            axis.x * s, 
            axis.y * s, 
            axis.z * s, 
            T{ std::cos(half) }
        );
    }

    template <typename T = nem::real>
    nem::quat<T> from_euler(T pitch, T yaw, T roll)
    {
        nem::quat qx = nem::from_axis_angle({ 1,0,0 }, pitch);
        nem::quat qy = nem::from_axis_angle({ 0,1,0 }, yaw);
        nem::quat qz = nem::from_axis_angle({ 0,0,1 }, roll);
        return qy * qx * qz;
    }

    template <typename T = nem::real>
    constexpr nem::mat<T, 3, 3> norm_quaterion_to_rotation_matrix(const nem::quat<T>& q)
    {
        // implies that q is normalized, hence s^2 + x^2 + y^2 + z^2 = 1, hence different notation
        static_assert(nem::is_zero(nem::sqrLength(q), T{ 1 }));

        // https://www.johndcook.com/blog/2025/05/07/quaternions-and-rotation-matrices/
        nem::mat<T, 3, 3> result{ 0 };
        auto q0 = q.s, q1 = q.x, q2 = q.y, q3 = q.z;
        result[0] = 2 * (q0 * q0 + q1 * q1) - 1;
        result[1] = 2 * (q1 * q2 - q0 * q3);
        result[2] = 2 * (q1 * q3 + q0 * q2);

        result[3] = 2 * (q1 * q2 + q0 * q3);
        result[4] = 2 * (q0 * q0 + q2 * q2) - 1;
        result[5] = 2 * (q2 * q3 - q0 * q1);

        result[6] = 2 * (q1 * q3 - q0 * q2);
        result[7] = 2 * (q2 * q3 + q0 * q1);
        result[8] = 2 * (q0 * q0 + q3 * q3) - 1;

        return result;
    }
}