#pragma once

#include <cassert>

namespace nem
{
	template <typename T, size_t R, size_t C>
	struct mat_base
	{
		static constexpr size_t size{ R * C };

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

		T data[size] = { 0 };

		constexpr mat_base() = default;
		constexpr mat_base(T _scalar) : data{}
		{
			for (size_t i = 0; i < size; ++i)
			{
				data[i] = _scalar;
			}
		}

		constexpr mat_base(std::initializer_list<T> list) : data{}
		{
			assert(list.size() == size && "Matrix must be initialized with exactly R * C elements");

			size_t i = 0;
			for (const auto& val : list)
			{
				if (i < R * C) data[i++] = val;
			}
		}

		constexpr mat_base(std::initializer_list<std::initializer_list<T>> rows) : data{}
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

		T* operator[](size_t r) { return &data[r * C]; }

		constexpr size_t index(size_t row, size_t column) const { return row * C + column; }

		constexpr T at(size_t index) const { return data[index]; }
		constexpr T at(size_t row, size_t column) const { return data[index(row, column)]; }

		constexpr const T& at_r(size_t index) const { return data[index]; }
		constexpr const T& at_r(size_t row, size_t column) const { return data[index(row, column)]; }

		constexpr T& at_rw(size_t index) { return data[index]; }
		constexpr T& at_rw(size_t row, size_t column) { return data[index(row, column)]; }
		
		static mat_base add(const mat_base& lhs, const mat_base& rhs)
		{
			mat_base result = lhs;
			for (size_t i = 0; i < size; ++i)
			{
				result.at_rw(i) = lhs.at(i) + rhs.at(i);
			}
			return result;
		}

		static mat_base sub(const mat_base& lhs, const mat_base& rhs)
		{
			mat_base result = lhs;
			for (size_t i = 0; i < size; ++i)
			{
				result.at_rw(i) = lhs.at(i) - rhs.at(i);
			}
			return result;
		}

		template <size_t R1, size_t C1>
		static mat_base<T, R, C1> mul(const mat_base<T, R, C>& lhs, const mat_base<T, R1, C1>& rhs)
		{
			constexpr size_t N = C;
			static_assert((C == R1) && "Matrix multiplication is only defined for matrices with C0 == R1");
			mat_base<T, R, C1> result;
			for (size_t r = 0; r < R; ++r)
			{
				for (size_t c = 0; c < C1; ++c)
				{
					for (size_t n = 0; n < N; ++n)
					{
						result.at_rw(r, c) += lhs.at_r(r, n) * rhs.at_r(n, c);
					}
				}
			}
			return result;
		}
	};

	template <typename T, size_t R, size_t C>
	struct mat : public mat_base<T, R, C>
	{
		using mat_base<T, R, C>::mat_base;
	};

	template <typename T, size_t N>
	struct mat<T, N, N> : public mat_base<T, N, N>
	{
		using mat_base<T, N, N>::mat_base;

		constexpr mat(T _scalar)
		{
			for (size_t i = 0; i < mat::size; ++i)
			{
				this->data[i] = _scalar;
			}
		}
		constexpr mat()
		{
			for (size_t i = 0; i < N; ++i)
			{
				this->data[i * N + i] = (T)1;
			}
		}

		static constexpr mat identity()
		{
			mat result((T)0.0);
			for (size_t i = 0; i < N; ++i)
			{
				result.data[i * N + i] = (T)1;
			}
			return result;
		}

		constexpr void transpose_in_place()
		{
			for (size_t r = 0; r < N; ++r)
			{
				for (size_t c = 0; c < N; ++c)
				{
					this->at_rw(c, r) = this->at_r(r, c);
				}
			}
		}
	};

	using mat2 = mat<real, 2, 2>;
	using mat3 = mat<real, 3, 3>;
	using mat4 = mat<real, 4, 4>;
}
