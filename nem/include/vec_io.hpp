#pragma once

#include <iostream>
#include <string>

#include "vec.hpp"

namespace nem
{
    static inline constexpr const char* SEPARATOR = ", ";
    static inline constexpr const char* VECTOR_L_BRACE = "(";
    static inline constexpr const char* VECTOR_R_BRACE = ")";

    template<typename Derived, typename T, size_t N>
    std::ostream& operator<<(std::ostream& os, const BaseVectorT<Derived, T, N>& vec)
    {
        os << VECTOR_L_BRACE;
        for (size_t i = 0; i < N; ++i)
        {
            os << vec[i] << (i < N - 1 ? SEPARATOR : "");
        }
        os << VECTOR_R_BRACE;
        return os;
    }

    template<typename Derived, typename T, size_t N>
    std::istream& operator>>(std::istream& is, BaseVectorT<Derived, T, N>& vec)
    {
        for (size_t i = 0; i < N; ++i)
        {
            is >> vec[i];
        }
        return is;
    }
}
