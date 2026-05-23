#pragma once

#include <concepts>
#include <type_traits>
#include <cassert>
#include <cmath>

#include "consts.hpp"
#include "err.hpp"
#include "config.hpp"

namespace nem
{
	template <nem::scalar_type T> constexpr T sign(T value) { return value >= 0 ? T{ 1 } : T{ -1 }; }
	template <typename T> constexpr T abs(T value) { return T{ value >= 0 ? value : -value }; }

	/// <summary>
	/// Is a nearly 0? Given an Epsilon > 0, within each all numbers are considered indistinguisable from 0, |a| < eps
	/// </summary>
	template <nem::scalar_type T> constexpr bool is_zero(T a, T eps = Eps<T>()) { return nem::abs(a) <= eps; }
	
	template <nem::scalar_type T> constexpr bool is_zero_or_neg(T a, T eps = Eps<T>()) { return a <= eps; }

	/// <summary>
	/// Are a and b nearly equal? Given an Epsilon > 0, within each all numbers are considered indistinguisable from 0, |a - b| < eps
	/// </summary>
	template <nem::scalar_type T> constexpr bool equal(T a, T b, T eps = Eps<T>()) { return nem::is_zero(a - b, eps); }

	// powers
	template <typename T> constexpr T pow2(T value) { return T{ value * value }; }
	template <typename T> constexpr T pow3(T value) { return T{ value * value * value }; }
	template <typename T> constexpr T pow4(T value) { return T{ nem::pow2(nem::pow2(value)) }; }
	template <typename T> constexpr T sqr (T value) { return T{ value * value }; }
	template <typename T> constexpr T cube(T value) { return T{ value * value * value }; }

	template <typename T> NEM_INLINE T pow(T base, T power) { return ::pow(base, power); }

	/// <summary>
	/// Natural logarithm. Input value is constrained to value > 0
	/// </summary>
	template <std::floating_point T> T ln(T value)
	{
		if (nem::is_zero_or_neg(value))
		{
			return nem::error::invalid_result<T>();
		}
		return ::log(value);
	}

	/// <summary>
	/// Natural logarithm. Input value is constrained to value > 0
	/// </summary>
	template <std::integral T> T ln(T value)
	{
		return (T)(ln<double>(static_cast<double>(value)));
	}

	template <std::floating_point T> T log(T base, T value)
	{
		if (nem::is_zero_or_neg(base) || nem::equal(base, (T)1.0))
		{
			return nem::error::invalid_result<T>();
		}
		if (nem::is_zero_or_neg(value))
		{
			return nem::error::invalid_result<T>();
		}
		return nem::ln(value) / nem::ln(base);
	}

	template <std::integral T> T log(T base, T value)
	{
		return (T)(log<double>(static_cast<double>(base), static_cast<double>(value)));
	}

	template <typename T>
	NEM_INLINE T sqrt(T value)
	{
		if (value < nem::Eps<T>()) value = T{ 0 };
		return static_cast<T>(std::sqrt(static_cast<double>(value)));
	}

	template <typename T, int Precision = 20>
	constexpr T csqrt(T value)
	{
		constexpr T ZERO = (T)0.0;
		if (value <= ZERO) return ZERO;
		T result = value;
		for (int i = 0; i < Precision; ++i) result = 0.5 * (result + value / result);
		return result;
	}

	template <std::integral T, int Precision = 20>
	constexpr T csqrt(T value)
	{
		constexpr T ZERO = (T)0;
		if (value <= ZERO) return ZERO;
		nem::real result = value;
		for (int i = 0; i < Precision; ++i) result = (nem::real)0.5 * (result + static_cast<nem::real>(value) / result);
		return static_cast<T>(result);
	}

	// limits

	template <nem::scalar_type T> constexpr T truncate(T value)
	{
		return (T)(long long int)value;
	}

	/// <summary>
	/// Floors always towards -infinity
	/// </summary>
	template <nem::scalar_type T> constexpr T floor(T value)
	{	
		const T trunc = nem::truncate(value);
		return trunc - (trunc > value); // subtract 1 if truncation made the number bigger, which can happen only when the value is negative AND not-whole. If it is whole, then truncation never changes the number. If the number is positive and not-whole,
		// | sign(value) | is whole? | sign(trunc - value) |
		// |      +      |	  yes    |           0         | -->  2.0 ->  2.0
		// |      +      |	   no    |          -1         | -->  2.3 ->  2.0
		// |      -      |	  yes    |           0         | --> -2.0 -> -2.0
		// |      -      |	   no    |          +1         | --> -2.3 -> -3.0
	}

	/// <summary>
	/// Ceils always towards +infinity
	/// </summary>
	template <nem::scalar_type T> constexpr T ceil(T value)
	{
		const T floored = nem::floor(value);
		return floored + (floored < value);
		// | sign(value) | is whole? | sign(trunc - value) |
		// |      +      |	  yes    |           0         | -->  2.0 ->  2.0
		// |      +      |	   no    |          -1         | -->  2.3 ->  3.0
		// |      -      |	  yes    |           0         | --> -2.0 -> -2.0
		// |      -      |	   no    |          +1         | --> -2.3 -> -2.0
	}

	/// <summary>
	/// Calculates euclidean modulo of a % b = r, where r belongs to [0, b). Unline standard C++ modulo operator, can never yield negative numbers and is mathematically correct.
	/// </summary>
	template <nem::scalar_type T> constexpr T mod(T a, T b)
	{
		if (nem::is_zero(a))
		{
			return nem::error::invalid_result<T>(nem::error::Type::ZeroModulo);
		}
		if (nem::is_zero(b))
		{
			return nem::error::invalid_result<T>(nem::error::Type::DivisionByZero);
		}
		const T v = a - nem::floor(a / b) * b;
		return v < 0 ? v + nem::abs(b) : v;
	}

	/// <summary>
	/// Unwinds number to 0 when goes past length. Lengh is excluded: when value == lengthExcl, value becomes 0.
	/// </summary>
	template <nem::scalar_type T> constexpr T repeat(T value, T lengthExcl)
	{
		return nem::mod(value, lengthExcl);
	}

	/// <summary>
	/// Unwinds number to minimum when goes past maximum. Max value is excluded: when value == maxExcl, value becomes minIncl.
	/// </summary>
	template <nem::scalar_type T> constexpr T repeat(T value, T minIncl, T maxExcl)
	{
		return minIncl + nem::mod(value - minIncl, maxExcl - minIncl);
	}

	template <nem::scalar_type T> constexpr T pingpong(T value, T length)
	{
		const T t = nem::repeat(value, length * (T)2.0);
		return length - nem::abs(t - length);
	}

	template <nem::scalar_type T> constexpr T pingpong(T value, T minIncl, T maxExcl)
	{
		return minIncl + nem::pingpong(value - minIncl, maxExcl - minIncl);
	}

	template <std::totally_ordered T> constexpr T clamp(T value, T minIncl, T maxIncl)
	{ 
		if (value > maxIncl) return maxIncl;
		else if (value < minIncl) return minIncl;
		return value;
	}
	template <std::totally_ordered T> constexpr T clamp01(T value) { return nem::clamp(value, 0.0F, 1.0F); }

	// interpolation

	template <typename T> constexpr T smoothstep(T edge0, T edge1, T x)
	{
		x = nem::clamp((x - edge0) / (edge1 - edge0), (T)0.0, (T)1.0);
		return x * x * ((T)3.0 - (T)2.0 * x);
	}
	template <typename T> constexpr T lerp(T a, T b, T t) { return b * t + a * ((T)1.0 - t); }
}