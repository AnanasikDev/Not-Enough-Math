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
	/// -------------------------------------------
	/// Metadata
	/// -------------------------------------------

	template <std::floating_point T> constexpr T is_infinite(T value) noexcept { return !nem::intr::_nem_isfinite(value); }
	template <std::floating_point T> constexpr T is_nan(T value) noexcept { return !nem::intr::_nem_isfinite(value); }

	template <std::integral T> constexpr T is_infinite(T) noexcept { return false; }
	template <std::integral T> constexpr T is_nan(T) noexcept { return false; }


	/// -------------------------------------------
	/// Sign operations
	/// -------------------------------------------

	/// Copies the sign of {from} over to {to}. If the signs were the same, it doesn't change.
	template <std::floating_point T> constexpr T copysign(T to, T from) noexcept
	{
		//to = static_cast<T>(__builtin_copysign(static_cast<double>(to), static_cast<double>(from)));
		return nem::intr::_nem_copysign(to, from);
	}
	template <nem::scalar_type T> constexpr T sign(T value) noexcept { return nem::copysign<T>((T)1.0, value); }

	template <typename T> constexpr T abs(T value) noexcept { return T{ value >= 0 ? value : -value }; }
	template <std::floating_point T> constexpr T abs(T value) noexcept { return nem::intr::_nem_fabs(value); }

	/// -------------------------------------------
	/// Comparisons
	/// -------------------------------------------
	
	/// <summary>
	/// Is a nearly 0? Given an Epsilon > 0, within each all numbers are considered indistinguisable from 0, |a| < eps
	/// </summary>
	template <nem::scalar_type T> constexpr bool is_zero(T a) noexcept { return nem::abs(a) < eps<T>(); }
	template <std::integral T> constexpr bool is_zero(T a) noexcept { return a == 0; }
	
	template <nem::scalar_type T> constexpr bool is_zero_or_neg(T a) noexcept { return a <= eps<T>(); }

	/// <summary>
	/// Are a and b nearly equal? Given an Epsilon > 0, within each all numbers are considered indistinguisable from 0, |a - b| < eps
	/// </summary>
	template <nem::scalar_type T> constexpr bool equal(T a, T b) noexcept { return nem::is_zero(a - b); }

	template <nem::scalar_type T> constexpr T get_max(T a, T b) noexcept { return (a > b) ? a : b; }

	template <nem::scalar_type T> constexpr T get_min(T a, T b) noexcept { return (a < b) ? a : b; }

	template <nem::scalar_type T> constexpr T average(T a, T b) noexcept { return (a + b) / (T)2.0; }


	/// -------------------------------------------
	/// Powers
	/// -------------------------------------------

	template <typename T> constexpr T pow2(T value) noexcept { return T{ value * value }; }
	template <typename T> constexpr T pow3(T value) noexcept { return T{ value * value * value }; }
	template <typename T> constexpr T pow4(T value) noexcept { return T{ value * value * value * value }; }
	template <typename T> constexpr T sqr (T value) noexcept { return T{ value * value }; }
	template <typename T> constexpr T cube(T value) noexcept { return T{ value * value * value }; }
	
	/// --------------------------------------------------------------------------------------
	/// Float truncation, fractional part, modulo (remainder), rounding, flooring, ceiling
	/// --------------------------------------------------------------------------------------

	template <nem::scalar_type T> constexpr T truncate(T value) noexcept
	{
		return (T)(long long int)value;
	}

	/// <summary>
	/// Floors always towards -infinity
	/// </summary>
	template <nem::scalar_type T> constexpr T floor(T value) noexcept
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
	template <nem::scalar_type T> constexpr T ceil(T value) noexcept
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
	/// Calculates euclidean modulo of a % b = r, where r belongs to [0, b). Unline standard C++ modulo operator, works with any floating-point numbers and can never yield negative numbers.
	/// </summary>
	template <nem::scalar_type T> constexpr T mod(T a, T b)
	{
		if (nem::is_zero(b))
		{
			return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero);
		}
		const T absb = nem::abs(b);
		const T v = a - nem::floor(a / b) * b;
		const T r = v < 0 ? v + absb : v;
		return nem::equal(r, absb) ? (T)0.0 : r;
	}

	/// <summary>
	/// Returns the fractional part of the floating-point number, with respect to sign
	/// 3.5 -> 0.5
	/// 4.0 -> 0.0
	/// -2.1 -> -0.1
	/// </summary>
	template <std::floating_point T> constexpr T frac(T value) noexcept
	{
		return value - nem::truncate(value);
	}
	
	/// Rounds the floating-point number to the closest integer. |0.5| will round up, meaning:
	/// 0.3 -> 0.0
	/// 0.5 -> 1.0
	/// -0.1 -> 0
	/// -0.6 -> -1.0
	/// -0.5 -> 0
	template <std::floating_point T> constexpr T round(T value) noexcept
	{
		const T floored = nem::floor(value);
		const T ceiled = floored + (floored < value); // ceil without extra floor
		const T neg_dist = value - floored;
		const T pos_dist = ceiled - value;
		const bool up = pos_dist < (neg_dist + nem::eps<T>()); // 0.5 -> up
		return ceiled * up + floored * !up; // branchless
	}

	/// -------------------------------------------
	/// Rounding, flooring and ceiling with step
	/// -------------------------------------------

	/// Floors the value to a uniform linear grid with step {step}. Same as normal floor, when step = 1. Step has to always be positive.
	/// (v = 0.9, s = 1.0) -> 0.0
	/// (v = 0.2, s = 1.0) -> 0.0
	/// (v = 0.4, s = 0.25) -> 0.25
	/// (v = 0.1, s = 0.25) -> 0.0
	/// (v = -0.1, s = 0.25) -> -0.25
	/// (v = 423.163123, s = 0.1) -> 423.1
	template <std::floating_point T> constexpr T floor(T value, T step)
	{
		if (nem::is_zero_or_neg(step))
		{
			return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero, "Flooring only supports positive step values");
		}
		return nem::floor(value / step) * step;
	}

	/// Floors the value to a uniform linear grid with step {step}. Same as normal floor, when step = 1. Step has to always be positive.
	/// (v = 5, s = 3) -> 3
	/// (v = -4, s = 3) -> -6
	template <std::integral T> constexpr T floor(T value, T step) noexcept
	{
		return (T)(nem::floor<nem::real>(static_cast<nem::real>(value), static_cast<nem::real>(step)));
	}

	/// Ceils the value to a uniform linear grid with step {step}. Same as normal ceil, when step = 1. Step has to always be positive.
	/// (v = 0.9, s = 1.0) -> 1.0
	/// (v = 0.2, s = 1.0) -> 1.0
	/// (v = 0.4, s = 0.25) -> 0.5
	/// (v = 0.1, s = 0.25) -> 0.5
	/// (v = -0.1, s = 0.25) -> 0.0
	/// (v = 423.163123, s = 0.1) -> 423.2
	template <std::floating_point T> constexpr T ceil(T value, T step)
	{
		if (nem::is_zero_or_neg(step))
		{
			return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero, "Ceiling only supports positive step values");
		}
		return nem::ceil(value / step) * step;
	}

	/// Ceils the value to a uniform linear grid with step {step}. Same as normal ceil, when step = 1. Step has to always be positive.
	/// (v = 5, s = 3) -> 3
	/// (v = -4, s = 3) -> -6
	template <std::integral T> constexpr T ceil(T value, T step)
	{
		return (T)(nem::ceil<nem::real>(static_cast<nem::real>(value), static_cast<nem::real>(step)));
	}

	/// Rounds the value to a uniform linear grid with step {step}. Same as normal round, when step = 1. Step has to always be positive.
	/// (v = 0.9, s = 1.0) -> 1.0
	/// (v = 0.2, s = 1.0) -> 0.0
	/// (v = 0.2, s = 0.25) -> 0.25
	/// (v = 0.1, s = 0.25) -> 0.0
	/// (v = -0.1, s = 0.25) -> 0.0
	/// (v = 423.163123, s = 0.1) -> 423.2
	template <std::floating_point T> constexpr T round(T value, T step)
	{
		if (nem::is_zero_or_neg(step))
		{
			return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero, "Rounding only supports positive step values");
		}
		return nem::round(value / step) * step;
	}

	/// Rounds the value to a uniform linear grid with step {step}. Same as normal round, when step = 1. Step has to always be positive.
	/// (v = 5, s = 3) -> 6
	/// (v = -4, s = 3) -> -3
	template <std::integral T> constexpr T round(T value, T step)
	{
		return (T)(nem::round<nem::real>(static_cast<nem::real>(value), static_cast<nem::real>(step)) + nem::eps<nem::real>());
	}
	
	/// -------------------------------------------
	/// Repeat, pingpong, clamp
	/// -------------------------------------------

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

	template <std::totally_ordered T> constexpr T clamp(T value, T minIncl, T maxIncl) noexcept
	{ 
		if (value > maxIncl) return maxIncl;
		else if (value < minIncl) return minIncl;
		return value;
	}
	template <std::totally_ordered T> constexpr T clamp01(T value) noexcept
	{
		return nem::clamp(value, (T)0.0, (T)1.0);
	}

	/// -------------------------------------------
	/// Interpolation
	/// -------------------------------------------

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

	/// -------------------------------------------
	/// Linear mapping
	/// -------------------------------------------

	template <nem::scalar_type T> constexpr T remap(T value, T fromMin, T fromMax, T toMin, T toMax)
	{
		const T fromLength = fromMax - fromMin;
		if (nem::is_zero(fromLength))
		{
			return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero, "Remapping from length is zero");
		}
		return toMin + (toMax - toMin) * ((value - fromMin) / fromLength);
    }

    /// -------------------------------------------
    /// Properties
    /// -------------------------------------------

    /// Is a floating point number whole (same as integer)
    template <std::floating_point T> constexpr T is_whole(T value)
    {
        return nem::is_zero(nem::frac(value));
    }
	
    /// Is an integer number whole. Always true, here for compatibility
    template <std::integral T> constexpr T is_whole(T value)
    {
        return true;
	}
}