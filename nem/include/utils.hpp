#pragma once

#include <concepts>
#include <type_traits>
#include <cassert>

#include "consts.hpp"
#include "err.hpp"
#include "config.hpp"

#include "intrinsics.hpp"

namespace nem
{
	template <nem::scalar_type T> constexpr T sign(T value) { return nem::_nem_copysign<T>((T)1.0, value); }

	template <typename T> constexpr T abs(T value) { return T{ value >= 0 ? value : -value }; }
	template <std::floating_point T> constexpr T abs(T value) { return nem::_nem_fabs(value); }

	/// <summary>
	/// Is a nearly 0? Given an Epsilon > 0, within each all numbers are considered indistinguisable from 0, |a| < eps
	/// </summary>
	template <nem::scalar_type T> constexpr bool is_zero(T a) { return nem::abs(a) < Eps<T>(); }
	template <std::integral T> constexpr bool is_zero(T a) { return a == 0; }
	
	template <nem::scalar_type T> constexpr bool is_zero_or_neg(T a) { return a <= Eps<T>(); }

	/// <summary>
	/// Are a and b nearly equal? Given an Epsilon > 0, within each all numbers are considered indistinguisable from 0, |a - b| < eps
	/// </summary>
	template <nem::scalar_type T> constexpr bool equal(T a, T b) { return nem::is_zero(a - b); }

	// powers
	template <typename T> constexpr T pow2(T value) { return T{ value * value }; }
	template <typename T> constexpr T pow3(T value) { return T{ value * value * value }; }
	template <typename T> constexpr T pow4(T value) { return T{ nem::pow2(nem::pow2(value)) }; }
	template <typename T> constexpr T sqr (T value) { return T{ value * value }; }
	template <typename T> constexpr T cube(T value) { return T{ value * value * value }; }

	template <nem::scalar_type T> NEM_INLINE T pow(T base, T power) { return ::pow(base, power); }

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
		if (nem::is_zero_or_neg(value))
		{
			 value = T{ 0 };
		}
		if constexpr (std::is_floating_point_v<T>)
		{
			return static_cast<T>(nem::_nem_sqrt(value));
		}
		else if constexpr (std::is_integral_v<T>)
		{
			return static_cast<T>(nem::_nem_sqrt(static_cast<double>(value)));
		}
	}

	template <std::floating_point T, int Precision = 20>
	constexpr T csqrt(T value)
	{
		if (nem::is_zero_or_neg(value))
		{
			return (T)0.0;
		}

		T result = value;
		for (int i = 0; i < Precision; ++i)
		{
			result = 0.5 * (result + value / result);
		}
		return result;
	}

	template <std::integral T, int Precision = 20>
	constexpr T csqrt(T value)
	{
		if (nem::is_zero_or_neg(value))
		{
			return (T)0.0;
		}

		nem::real result = value;
		for (int i = 0; i < Precision; ++i)
		{
			result = (nem::real)0.5 * (result + static_cast<nem::real>(value) / result);
		}
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
		if (nem::is_zero(b))
		{
			return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero);
		}
		const T v = a - nem::floor(a / b) * b;
		return v < 0 ? v + nem::abs(b) : v;
	}

	/// <summary>
	/// Returns the fractional part of the floating-point number, with respect to sign
	/// 3.5 -> 0.5
	/// 4.0 -> 0.0
	/// -2.1 -> -0.1
	/// </summary>
	template <std::floating_point T> constexpr T frac(T value)
	{
		return value - nem::truncate(value);
	}
	
	/// Rounds the floating-point number to the closest integer. |0.5| will round up, meaning:
	/// 0.3 -> 0.0
	/// 0.5 -> 1.0
	/// -0.1 -> 0
	/// -0.6 -> -1.0
	/// -0.5 -> 0
	template <std::floating_point T> constexpr T round(T value)
	{
		const T floored = nem::floor(value);
		const T ceiled = floored + (floored < value); // ceil without extra floor
		const T neg_dist = value - floored;
		const T pos_dist = ceiled - value;
		const bool up = pos_dist < neg_dist + nem::Eps<T>(); // 0.5 -> up
		return ceiled * up + floored * !up; // branchless
	}


	/// Copies the sign of {from} over to {to}. If the signs were the same, it doesn't change.
	template <std::floating_point T> constexpr T copysign(T to, T from)
	{
		//to = static_cast<T>(__builtin_copysign(static_cast<double>(to), static_cast<double>(from)));
		return nem::_nem_copysign(to, from);
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
		const T length = edge1 - edge0;
		if (nem::is_zero(length))
		{
			return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero, "Smoothstep edges are too closeby");
		}
		x = nem::clamp((x - edge0) / (edge1 - edge0), (T)0.0, (T)1.0);
		return x * x * ((T)3.0 - (T)2.0 * x);
	}
	template <typename T> constexpr T lerp(T a, T b, T t) { return b * t + a * ((T)1.0 - t); }

	template <nem::scalar_type T> constexpr T remap(T value, T fromMin, T fromMax, T toMin, T toMax)
	{
		const T fromLength = fromMax - fromMin;
		if (nem::is_zero(fromLength))
		{
			return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero, "Remapping from length is zero");
		}
		return toMin + (toMax - toMin) * ((value - fromMin) / fromLength);
	}
}