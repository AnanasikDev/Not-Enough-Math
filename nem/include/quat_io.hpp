#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include "quat.hpp"

namespace nem
{
    static constexpr const char* QUAT_SEPARATOR = " + ";
    static constexpr const char* QUAT_L_BRACE = "(";
    static constexpr const char* QUAT_R_BRACE = ")";

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const quat<T>& q)
    {
        os << QUAT_L_BRACE;
        os << q.s << QUAT_SEPARATOR;
        os << q.x << "i" << QUAT_SEPARATOR;
        os << q.y << "j" << QUAT_SEPARATOR;
        os << q.z << "k";
        os << QUAT_R_BRACE;
        return os;
    }

    template<typename T>
    std::istream& operator>>(std::istream& is, nem::quat<T>& q)
    {
        is >> q.s;
        is >> q.x;
        is >> q.y;
        is >> q.z;
        return is;
    }

    template<typename T>
    std::string to_str(const quat<T>& q)
    {
        std::stringstream ss;
        ss << QUAT_L_BRACE;
        ss << q.s << QUAT_SEPARATOR;
        ss << q.x << "i" << QUAT_SEPARATOR;
        ss << q.y << "j" << QUAT_SEPARATOR;
        ss << q.z << "k";
        ss << QUAT_R_BRACE;
        return ss.str();
    }
}
