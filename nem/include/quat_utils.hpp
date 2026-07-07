#pragma once

#include "quat.hpp"
#include "vec.hpp"
#include "mat.hpp"
#include "utils.hpp"
#include "trig.hpp"
#include "power.hpp"

namespace nem
{
    template <typename T = nem::real>
    constexpr T sqr_length(const nem::quat_t<T>& q)
    {
        return nem::sqr(q.s) + nem::sqr(q.x) + nem::sqr(q.y) + nem::sqr(q.z);
    }

    template <typename T = nem::real>
    NEM_INLINE T length(const nem::quat_t<T>& q)
    {
        return nem::sqrt(nem::sqr_length(q));
    }

    template <typename T = nem::real>
    NEM_INLINE nem::quat_t<T> normalize(nem::quat_t<T> q)
    {
        const T l = nem::length(q);
        q /= l;
        return q;
    }

    template<typename T = nem::real>
    constexpr nem::quat_t<T> make_quat(const nem::vec<T, 4>& vec4)
    {
        return nem::quat_t<T> { vec4.x, vec4.y, vec4.z, vec4.w };
    }

    template<typename T = nem::real>
    constexpr nem::quat_t<T> make_quat(T scalar, T x, T y, T z)
    {
        return nem::quat_t<T> { scalar, x, y, z };
    }

    /// <summary>
    /// Conjugates the quaternion, yielding a quaternion with the same angle (scalar) but inverse axis (vector)
    /// </summary>
    template<typename T = nem::real>
    constexpr nem::quat_t<T> conjugate(const nem::quat_t<T>& q)
    {
        return nem::quat_t<T> { q.s, -q.x, -q.y, -q.z };
    }

    template<typename T = nem::real>
    constexpr nem::quat_t<T> inverse(const nem::quat_t<T>& q)
    {
        return nem::conjugate(q) / nem::sqr_length(q);
    }

    template<typename T = nem::real>
    nem::quat_t<T> from_axis_angle(const nem::vec<T, 3>& axis, T radians)
    {
        const nem::sincos a = nem::get_sincos(radians * T{0.5});
        return nem::make_quat<T>(
            axis.x * a.sin, 
            axis.y * a.sin, 
            axis.z * a.sin, 
            a.cos
        );
    }

    template <typename T = nem::real>
    nem::quat_t<T> from_euler(T pitch, T yaw, T roll)
    {
        nem::quat_t qx = nem::from_axis_angle({ 1,0,0 }, pitch);
        nem::quat_t qy = nem::from_axis_angle({ 0,1,0 }, yaw);
        nem::quat_t qz = nem::from_axis_angle({ 0,0,1 }, roll);
        return qy * qx * qz;
    }

    template <typename T = nem::real>
    constexpr nem::mat<T, 3, 3> norm_quaterion_to_rotation_matrix(const nem::quat_t<T>& q)
    {
        // implies that q is normalized, hence s^2 + x^2 + y^2 + z^2 = 1, hence different notation
        if (!nem::equal(nem::sqr_length(q), T{1}))
        {
            return nem::error::invalid_result<nem::mat<T, 3, 3>>(nem::error::Kind::InvalidArgument, "Quaternion has to be normalized");
        }

        // https://www.johndcook.com/blog/2025/05/07/quaternions-and-rotation-matrices/
        auto q0 = q.s, q1 = q.x, q2 = q.y, q3 = q.z;
        return nem::mat<T, 3, 3>({
            { 2 * (q0 * q0 + q1 * q1) - 1, 2 * (q1 * q2 - q0 * q3),     2 * (q1 * q3 + q0 * q2)     },
            { 2 * (q1 * q2 + q0 * q3),     2 * (q0 * q0 + q2 * q2) - 1, 2 * (q2 * q3 - q0 * q1)     },
            { 2 * (q1 * q3 - q0 * q2),     2 * (q2 * q3 + q0 * q1),     2 * (q0 * q0 + q3 * q3) - 1 }
        });
    }

    template <typename T>
    constexpr nem::vec<T, 3> extract_vector(const nem::quat_t<T>& q)
    {
        return nem::vec<T, 3>(q.x, q.y, q.z);
    }
}