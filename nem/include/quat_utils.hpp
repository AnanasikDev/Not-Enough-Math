#pragma once

#include "quat.hpp"
#include "vec.hpp"

namespace nem
{
    template<typename Derived, typename T = nem::real>
    constexpr quat<T> make_quat(const nem::BaseVectorT<Derived, T, 4>& vec4)
    {
        return quat<T> { vec4.x, vec4.y, vec4.z, vec4.w };
    }

    template<typename T = nem::real>
    constexpr quat<T> make_quat(T scalar, T x, T y, T z)
    {
        return quat<T> { scalar, x, y, z };
    }

    template<typename Derived, typename T = nem::real>
    quat<T> from_axis_angle(const nem::BaseVectorT<Derived, T, 3>& axis, T angle)
    {
        T half = angle * T{ 0.5 };
        T s = T{ std::sin(half) };
        return quat(
            axis.x * s, 
            axis.y * s, 
            axis.z * s, 
            T{ std::cos(half) }
        );
    }

    template <typename T = nem::real>
    quat<T> from_euler(T pitch, T yaw, T roll)
    {
        quat qx = nem::from_axis_angle({ 1,0,0 }, pitch);
        quat qy = nem::from_axis_angle({ 0,1,0 }, yaw);
        quat qz = nem::from_axis_angle({ 0,0,1 }, roll);
        return qy * qx * qz;
    }
}