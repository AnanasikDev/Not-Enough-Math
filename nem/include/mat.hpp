#pragma once

#include <cassert>
#include "utils.hpp"
#include "vec.hpp"

namespace nem
{
	template <nem::scalar_type _T, size_t _C, size_t _R>
	struct mat
	{
		static constexpr size_t COLUMNS = _C;
		static constexpr size_t ROWS = _R;
        static constexpr size_t ITEM_COUNT = ROWS * COLUMNS;
        using ITEM_TYPE = _T;
        using COLUMN_TYPE = nem::vec<ITEM_TYPE, ROWS>;
        using ROW_TYPE = nem::vec<ITEM_TYPE, COLUMNS>;

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
        /// Storage is column-major: columns[c] is contiguous in memory, and columns[c][r]
        /// is the element at row r, column c. operator[] indexes a column first (GLM-style);
        /// at(row, col) indexes by mathematical (row, column) notation instead.

        union
        {
			ITEM_TYPE data[ITEM_COUNT] = { 0 };
            COLUMN_TYPE columns[COLUMNS];
		};

        constexpr COLUMN_TYPE& column(size_t index) { return columns[index]; }
        constexpr const COLUMN_TYPE& column(size_t index) const { return columns[index]; }

		constexpr COLUMN_TYPE& operator[](size_t col) { return columns[col]; }
		constexpr const COLUMN_TYPE& operator[](size_t col) const { return columns[col]; }

        constexpr ITEM_TYPE& at(size_t row, size_t col) { return columns[col][row]; }
        constexpr const ITEM_TYPE& at(size_t row, size_t col) const { return columns[col][row]; }

        constexpr ITEM_TYPE item(size_t i) const { return data[i]; }
        constexpr const ITEM_TYPE* item_ptr(size_t i) const { return &data[i]; }
        constexpr ITEM_TYPE* item_ptr(size_t i) { return &data[i]; }

		constexpr mat() : data{} {};
		constexpr mat(ITEM_TYPE scalar) : data{}
		{
			for (size_t i = 0; i < ITEM_COUNT; ++i)
			{
				data[i] = scalar;
			}
        }

        /// Takes ROWS lists of COLUMNS values each, matching how a matrix reads on paper,
        /// and scatters them into the column-major storage.
		constexpr mat(std::initializer_list<std::initializer_list<ITEM_TYPE>> rows) : data{}
		{
			// TODO: NEM_RUNTIME_ASSERT
			NEM_RUNTIME_ASSERT(rows.size() == ROWS, "Matrix row count mismatch!");

			size_t r = 0;
			for (const auto& row_list : rows)
			{
				NEM_RUNTIME_ASSERT(row_list.size() == COLUMNS, "Matrix column count mismatch!");

				size_t c = 0;
				for (const auto& val : row_list)
				{
					columns[c][r] = static_cast<ITEM_TYPE>(val);
					c++;
				}
				r++;
			}
		}

        template <size_t OTHER_COLUMNS>
		constexpr friend mat<ITEM_TYPE, OTHER_COLUMNS, ROWS> operator*(const mat& lhs, const mat<ITEM_TYPE, OTHER_COLUMNS, COLUMNS>& rhs)
		{
			mat<ITEM_TYPE, OTHER_COLUMNS, ROWS> result;
			for (size_t r = 0; r < ROWS; ++r)
			{
				for (size_t c = 0; c < OTHER_COLUMNS; ++c)
				{
					for (size_t n = 0; n < COLUMNS; ++n)
					{
						result[c][r] += lhs[n][r] * rhs[c][n];
					}
				}
			}
			return result;
        }

        static constexpr mat NaN() { return mat(std::numeric_limits<ITEM_TYPE>::quiet_NaN()); }

		constexpr mat& operator+=(const mat& other)
		{
			for (size_t c = 0; c < COLUMNS; ++c)
			{
				(*this)[c] += other[c];
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
			for (size_t i = 0; i < lhs.ITEM_COUNT; ++i)
			{
				if (!nem::equal(lhs.item(i), rhs.item(i)))
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

		constexpr friend nem::vec<ITEM_TYPE, ROWS> operator*(const mat& lhs, const nem::vec<ITEM_TYPE, COLUMNS>& rhs)
		{
			nem::vec<ITEM_TYPE, ROWS> result;
			for (size_t c = 0; c < COLUMNS; ++c)
			{
				for (size_t r = 0; r < ROWS; ++r)
				{
					result[r] += lhs[c][r] * rhs[c];
				}
			}
			return result;
		}
    };

	using mat2 = mat<real, 2, 2>;
	using mat3 = mat<real, 3, 3>;
	using mat4 = mat<real, 4, 4>;
}
