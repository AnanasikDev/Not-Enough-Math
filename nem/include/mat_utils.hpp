#pragma once

#include "mat.hpp"
#include "utils.hpp"
#include "trig.hpp"
#include "quat.hpp"
#include "quat_utils.hpp"

namespace nem
{
    template<typename T, size_t C, size_t R, typename F>
    constexpr nem::mat<T, C, R> transform_items(nem::mat<T, C, R> m, F&& func)
    {
        for (size_t c = 0; c < C; ++c)
        {
            for (size_t r = 0; r < R; ++r)
            {
                m[c][r] = func(r, c, m[c][r]);
            }
        }
        return m;
    }

    template<typename T, size_t C, size_t R>
    constexpr nem::mat<T, R, C> transpose(const nem::mat<T, C, R>& m)
    {
        nem::mat<T, R, C> result;
        for (size_t c = 0; c < C; ++c)
        {
            for (size_t r = 0; r < R; ++r)
            {
                result[r][c] = m[c][r];
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
            result[i][i] = T{ 1 };
        }
        return result;
    }

    template<typename M>
    constexpr nem::mat<typename M::ITEM_TYPE, M::COLUMNS, M::ROWS> identity()
    {
        static_assert(M::ROWS == M::COLUMNS && "Identity matrix must be square");
        return nem::identity<typename M::ITEM_TYPE, M::ROWS>();
    }

    template<typename T, size_t C1, size_t R1, size_t C2, size_t R2>
    constexpr nem::mat<T, C2, R2> upscale(const nem::mat<T, C1, R1>& m)
    {
        static_assert(R2 > R1 && "Error NEM: Matrix upscaling is only allowed for R2 > R1");
        static_assert(C2 > C1 && "Error NEM: Matrix upscaling is only allowed for C2 > C1");

        nem::mat<T, C2, R2> result;
        for (size_t c = 0; c < C1; ++c)
        {
            for (size_t r = 0; r < R1; ++r)
            {
                result[c][r] = m[c][r];
            }
        }
        return result;
    }

    template<typename T, size_t N>
    constexpr nem::mat<T, N + 1, N + 1> homogenous(const nem::mat<T, N, N>& m)
    {
        nem::mat<T, N + 1, N + 1> result = nem::identity<T, N + 1>();
        for (size_t c = 0; c < N; ++c)
        {
            for (size_t r = 0; r < N; ++r)
            {
                result[c][r] = m[c][r];
            }
        }
        return result;
    }

    template<typename T>
    constexpr T determinant(const nem::mat<T, 2, 2>& m)
    {
        return m[0][0] * m[1][1] - m[1][0] * m[0][1];
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
        return  nem::rotate_z(nem::get_sincos(yaw_z  )) *
                nem::rotate_y(nem::get_sincos(pitch_y)) *
                nem::rotate_x(nem::get_sincos(roll_x ));
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
            result[i][i] = value[i];
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
