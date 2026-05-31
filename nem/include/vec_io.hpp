#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include "vec.hpp"

namespace nem
{
    static constexpr const char* VECTOR_SEPARATOR = ", ";
    static constexpr const char* VECTOR_L_BRACE = "(";
    static constexpr const char* VECTOR_R_BRACE = ")";

    template<typename vec_derived_t, typename T, size_t N>
    std::ostream& operator<<(std::ostream& os, const base_vector_t<vec_derived_t, T, N>& vec)
    {
        os << VECTOR_L_BRACE;
        for (size_t i = 0; i < N; ++i)
        {
            os << vec[i] << (i < N - 1 ? VECTOR_SEPARATOR : "");
        }
        os << VECTOR_R_BRACE;
        return os;
    }

    template<typename vec_derived_t, typename T, size_t N>
    std::istream& operator>>(std::istream& is, base_vector_t<vec_derived_t, T, N>& vec)
    {
        for (size_t i = 0; i < N; ++i)
        {
            is >> vec[i];
        }
        return is;
    }

    template<typename vec_derived_t, typename T, size_t N>
    std::string tostr(const base_vector_t<vec_derived_t, T, N>& vec)
    {
        std::stringstream ss;
        ss << VECTOR_L_BRACE;
        for (size_t i = 0; i < N; ++i)
        {
            ss << vec[i] << (i < N - 1 ? VECTOR_SEPARATOR : "");
        }
        ss << VECTOR_R_BRACE;
        return ss.str();
    }
}
