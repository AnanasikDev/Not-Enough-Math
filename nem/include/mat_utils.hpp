#pragma once

#include "mat.hpp"

namespace nem
{
    template<typename T, size_t R, size_t C, typename F>
    mat<T, R, C> transform(mat<T, R, C>& m, F&& func)
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
    constexpr mat<T, C, R> transpose(const mat<T, R, C>& m)
    {
        mat<T, C, R> result;
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
    constexpr mat<T, N, N> identity()
    {
        mat<T, N, N> result((T)0.0);
        for (size_t i = 0; i < N; ++i)
        {
            result.data[i * N + i] = T{ 1 };
        }
        return result;
    }

    template<typename M>
    constexpr mat<typename M::Type, M::Rows, M::Columns> identity()
    {
        constexpr size_t N = M::Rows;
        using T = M::Type;
        return nem::identity<T, N>();
    }
}
