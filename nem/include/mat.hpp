#pragma once

#include <cassert>
#include "utils.hpp"
#include "vec.hpp"

namespace nem
{
	template <typename T, size_t R, size_t C>
	struct mat
	{
		static constexpr size_t Size{ R * C };
		static constexpr size_t Rows = R;
		static constexpr size_t Columns = C;
        using Type = T;

		///
		///            C
		///    ----------------
		///   | m00 m01 m02 m03   Row 0
		///   | m10 m11 m12 m13   Row 1
		/// R | m20 m21 m22 m23   Row 2
		///   | m30 m31 m32 m33   Row 3
		///   | m40 m41 m42 m43   Row 4
		/// 
		///	    Cl0 Cl1 Cl2 Cl3
		///

		T data[Size] = { 0 };

		constexpr mat() : data{} {};
		constexpr mat(T _scalar) : data{}
		{
			for (size_t i = 0; i < Size; ++i)
			{
				data[i] = _scalar;
			}
		}

		constexpr mat(std::initializer_list<T> list) : data{}
        {
            if (list.size() == 0)
            {
                return;
            }
            
			assert(list.size() == Size && "Matrix must be initialized with exactly R * C elements");

			size_t i = 0;
			for (const auto& val : list)
			{
				if (i < R * C) data[i++] = val;
			}
		}

		constexpr mat(std::initializer_list<std::initializer_list<T>> rows) : data{}
		{
			assert(rows.size() == R && "Matrix row count mismatch!");

			size_t r = 0;
			for (const auto& row_list : rows)
			{
				assert(row_list.size() == C && "Matrix column count mismatch!");

				size_t c = 0;
				for (const auto& val : row_list)
				{
					data[r * C + c] = static_cast<T>(val);
					c++;
				}
				r++;
			}
		}
		
		T& operator[](size_t element) { return data[element]; }
		const T& operator[](size_t element) const { return data[element]; }

		constexpr size_t index(size_t row, size_t column) const { return row * C + column; }

		constexpr T& at(size_t row, size_t column) { return data[index(row, column)]; }
        constexpr const T& at(size_t row, size_t column) const { return data[index(row, column)]; }

        constexpr T* row(size_t index) { return &data[this->index(index, 0)]; }
        constexpr const T* row(size_t index) const { return &data[this->index(index, 0)]; }

		//static constexpr mat NaN() { mat(std::numeric_limits<T>::quiet_NaN()); }

		template <size_t R1, size_t C1>
		constexpr friend mat<T, R, C1> operator*(const mat<T, R, C>& lhs, const mat<T, R1, C1>& rhs)
		{
			static_assert((C == R1) && "Matrix multiplication is only defined for matrices with C0 == R1");
			constexpr size_t N = C;
			mat<T, R, C1> result;
			for (size_t r = 0; r < R; ++r)
			{
				for (size_t c = 0; c < C1; ++c)
				{
					for (size_t n = 0; n < N; ++n)
					{
						result.at(r, c) += lhs.at(r, n) * rhs.at(n, c);
					}
				}
			}
			return result;
        }

		constexpr mat& operator+=(const mat& other)
		{
			for (size_t i = 0; i < Size; ++i)
			{
				(*this)[i] += other[i];
			}
			return *this;
		}

		constexpr friend mat operator+(mat lhs, const mat& rhs)
		{
			lhs += rhs;
			return lhs;
		}

		constexpr friend bool operator==(const mat& lhs, const mat& rhs)
		{
			for (size_t i = 0; i < lhs.Size; ++i)
			{
				if (!nem::is_zero(lhs.data[i] - rhs.data[i]))
				{
					return false;
				}
			}
			return true;
		}

		constexpr friend bool operator!=(const mat& lhs, const mat& rhs)
		{
			return !(lhs == rhs);
		}
	};

	using mat2 = mat<real, 2, 2>;
	using mat3 = mat<real, 3, 3>;
	using mat4 = mat<real, 4, 4>;
}

template <typename Derived, typename T, size_t N>
constexpr Derived operator*(const nem::mat<T, N, N>& lhs, const nem::base_vector_t<Derived, T, N>& rhs)
{
	Derived result;
	for (size_t r = 0; r < N; ++r)
	{
		for (size_t n = 0; n < N; ++n)
		{
			result[r] += lhs.at(r, n) * rhs[n];
		}
	}
	return result;
}