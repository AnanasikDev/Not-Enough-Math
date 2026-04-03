#pragma once

namespace nem
{
    template<typename T, size_t R, size_t C, typename F>
    mat<T, R, C> operator|(mat<T, R, C>& m, F&& func)
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
}
