#pragma once

#include <sstream>

#include "mat.hpp"

namespace nem
{
	static constexpr const char* MATRIX_COLUMN_SEPARATOR = ", ";
	static constexpr const char* MATRIX_ROW_SEPARATOR = "\n";
	static constexpr const char* MATRIX_L_BRACE = "[";
	static constexpr const char* MATRIX_R_BRACE = "]";

	template<typename T, size_t R, size_t C>
	std::string tostr(const mat_base<T, R, C>& matrix)
	{
		std::stringstream ss;
		for (size_t r = 0; r < R; ++r)
		{
			ss << MATRIX_L_BRACE;
			for (size_t c = 0; c < C; ++c)
			{
				ss << matrix.at(r, c) << (c < C - 1 ? MATRIX_COLUMN_SEPARATOR : "");
			}
			ss << MATRIX_R_BRACE;
			ss << MATRIX_ROW_SEPARATOR;
		}
		return ss.str();
	}

	template<typename T, size_t R, size_t C>
    std::ostream& operator<<(std::ostream& os, const mat_base<T, R, C>& matrix)
    {
		for (size_t r = 0; r < R; ++r)
		{
			os << MATRIX_L_BRACE;
			for (size_t c = 0; c < C; ++c)
			{
				os << matrix.at(r, c) << (c < C - 1 ? MATRIX_COLUMN_SEPARATOR : "");
			}
			os << MATRIX_R_BRACE;
			os << MATRIX_ROW_SEPARATOR;
		}
		return os;
    }

	template<typename T, size_t R, size_t C>
    std::istream& operator>>(std::istream& is, mat_base<T, R, C>& matrix)
    {
		for (size_t r = 0; r < R; ++r)
		{
			for (size_t c = 0; c < C; ++c)
			{
				is >> matrix.at_rw(r, c);
			}
		}
		return is;
    }
}