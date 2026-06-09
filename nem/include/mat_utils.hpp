#pragma once

#include "mat.hpp"
#include "utils.hpp"
#include "trig.hpp"
#include "quat.hpp"
#include "quat_utils.hpp"

namespace nem
{
    template<typename T, size_t R, size_t C, typename F>
    nem::mat<T, R, C> transform_items(nem::mat<T, R, C>& m, F&& func)
    {
        for (size_t r = 0; r < R; ++r)
        {
            for (size_t c = 0; c < C; ++c)
            {
                m.at(r, c) = func(r, c, m.at(r, c));
            }
        }
        return m;
    }

    template<typename T, size_t R, size_t C>
    constexpr nem::mat<T, C, R> transpose(const nem::mat<T, R, C>& m)
    {
        nem::mat<T, C, R> result;
        for (size_t r = 0; r < R; ++r)
        {
            for (size_t c = 0; c < C; ++c)
            {
                result.at(c, r) = m.at(r, c);
            }
        }
        return result;
    }

    template<typename T, size_t N>
    constexpr nem::mat<T, N, N> identity()
    {
        nem::mat<T, N, N> result((T)0.0);
        for (size_t i = 0; i < N; ++i)
        {
            result[i * N + i] = T{ 1 };
        }
        return result;
    }

    template<typename M>
    constexpr nem::mat<typename M::Type, M::Rows, M::Columns> identity()
    {
        constexpr size_t N = M::Rows;
        using T = typename M::Type;
        return nem::identity<T, N>();
    }

    template<typename T, size_t R1, size_t C1, size_t R2, size_t C2>
    constexpr nem::mat<T, R2, C2> upscale(const nem::mat<T, R1, C1>& m)
    {
        static_assert(R2 > R1 && "Error NEM: Matrix upscaling is only allowed for R2 > R1");
        static_assert(C2 > C1 && "Error NEM: Matrix upscaling is only allowed for C2 > C1");

        nem::mat<T, R2, C2> result;
        for (size_t r = 0; r < R1; ++r)
        {
            memcpy(result.row(r), m.row(r), C1 * sizeof(T));
        }
        return result;
    }

    template<typename T, size_t N>
    constexpr nem::mat<T, N + 1, N + 1> homogenous(const nem::mat<T, N, N>& m)
    {
        nem::mat<T, N + 1, N + 1> result = nem::identity<T, N + 1>();
        for (size_t r = 0; r < N; ++r)
        {
            memcpy(result.row(r), m.row(r), N * sizeof(T));
        }
        return result;
    }

    template<typename T>
    constexpr T determinant(const nem::mat<T, 2, 2>& m)
    {
        return m[0] * m[3] - m[1] * m[2];
    }

    template<std::floating_point T>
    constexpr nem::mat<T, 2, 2> rotate(T radians)
    {
        nem::sincos<T> a = nem::get_sincos(radians);
        return nem::mat<T, 2, 2>( {{ a.cos, -a.sin } , { a.sin, a.cos }} );
    }

    template<std::floating_point T>
    constexpr nem::mat<T, 3, 3> rotate_x(nem::sincos<T> a)
    {
        return nem::mat<T, 3, 3>( {{ 1, 0, 0 } , { 0, a.cos, -a.sin }, { 0, a.sin, a.cos }} );
    }

    template<std::floating_point T>
    constexpr nem::mat<T, 3, 3> rotate_y(nem::sincos<T> a)
    {
        return nem::mat<T, 3, 3>( {{ a.cos, 0, a.sin } , { 0, 1, 0 }, { -a.sin, 0, a.cos }} );
    }

    template<std::floating_point T>
    constexpr nem::mat<T, 3, 3> rotate_z(nem::sincos<T> a)
    {
        return nem::mat<T, 3, 3>( {{ a.cos, -a.sin, 0 } , { a.sin, a.cos, 0 }, { 0, 0, 1 }} );
    }

    template<std::floating_point T>
    constexpr nem::mat<T, 3, 3> rotate(T yaw_z, T pitch_y, T roll_x)
    {
        return  nem::rotate(nem::sincos(yaw_z  )) * 
                nem::rotate(nem::sincos(pitch_y)) * 
                nem::rotate(nem::sincos(roll_x ));
    }

    template<std::floating_point T>
    constexpr nem::mat<T, 3, 3> translate_2D(const nem::vec<T, 2>& value)
    {
        return nem::mat<T, 3, 3>({{1, 0, value[0]}, {0, 1, value[1]}, {0, 0, 1}});
    }

    template<std::floating_point T>
    constexpr nem::mat<T, 4, 4> translate_3D(const nem::vec<T, 3>& value)
    {
        return nem::mat<T, 4, 4>({{1, 0, 0, value[0]}, {0, 1, 0, value[1]}, {0, 0, 1, value[2]}, {0, 0, 0, 1}});
    }

    template<std::floating_point T, size_t N>
    constexpr nem::mat<T, N, N> scale(const nem::vec<T, N>& value)
    {
        nem::mat<T, N, N> result((T)0.0);
        for (size_t i = 0; i < N; ++i)
        {
            result.data[i * N + i] = value[i];
        }
        return result;
    }

    template <std::floating_point T>
    constexpr nem::mat<T, 4, 4> transform(const nem::vec<T, 3>& translation, const nem::quat_t<T>& rotation,
                                          const nem::vec<T, 3> scaler)
    {
        return nem::translate_3D(translation) *
               nem::homogenous(nem::norm_quaterion_to_rotation_matrix(nem::normalize(rotation))) *
               nem::homogenous<T, 3>(nem::scale(scaler));
    }
}
