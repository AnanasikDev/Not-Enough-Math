#pragma once

#include "mat.hpp"

namespace nem
{
    template<typename T, size_t R, size_t C, typename F>
    nem::mat<T, R, C> transform(nem::mat<T, R, C>& m, F&& func)
    {
        for (size_t r = 0; r < R; ++r)
        {
            for (size_t c = 0; c < C; ++c)
            {
                m.at_rw(r, c) = func(r, c, m.at_r(r, c));
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
                result.at_rw(c, r) = m.at_r(r, c);
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
            result.data[i * N + i] = T{ 1 };
        }
        return result;
    }

    template<typename M>
    constexpr nem::mat<typename M::Type, M::Rows, M::Columns> identity()
    {
        constexpr size_t N = M::Rows;
        using T = M::Type;
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
            memcpy(result[r], m[r], C1 * sizeof(T));
        }
        return result;
    }
}
