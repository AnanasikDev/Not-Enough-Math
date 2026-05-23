#pragma once

#include <concepts>
#include <type_traits>
#include <cassert>
#include <cmath>

#include "err.hpp"
#include "config.hpp"

namespace nem
{
	template <std::floating_point T>
	constexpr T Eps() { return (T)1e-6; }

	template <typename T>
	concept scalar_type = std::integral<T> || std::floating_point<T>;

	template <nem::scalar_type T> constexpr T sign(T value) { return value >= 0 ? T{ 1 } : T{ -1 }; }
	template <typename T> constexpr T abs(T value) { return T{ value >= 0 ? value : -value }; }
	template <nem::scalar_type T> constexpr bool is_nearly_zero(T a, T eps = (T)1e-6) { return nem::abs(a) <= eps; }

	// powers
	template <typename T> constexpr T pow2(T value) { return T{ value * value }; }
	template <typename T> constexpr T pow3(T value) { return T{ value * value * value }; }
	template <typename T> constexpr T pow4(T value) { return T{ nem::pow2(nem::pow2(value)) }; }
	template <typename T> constexpr T sqr (T value) { return T{ value * value }; }
	template <typename T> constexpr T cube(T value) { return T{ value * value * value }; }

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

	// misc
	
	template <nem::scalar_type T> constexpr T truncate(T value)
	{
		return (T)(long long int)value;
	}

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
		if (nem::is_nearly_zero(a))
		{
			return nem::error::invalid_result<T>(nem::error::Type::ZeroModulo);
		}
		if (nem::is_nearly_zero(b))
		{
			return nem::error::invalid_result<T>(nem::error::Type::DivisionByZero);
		}
		const float v = a - nem::floor(a / b) * b;
		return v < 0 ? v + nem::abs(b) : v;
	}

	template <nem::scalar_type T> constexpr T repeat(T value, T length)
	{
		return nem::mod(value, length);
	}

	template <nem::scalar_type T> constexpr T repeat(T value, T min, T max)
	{
		return min + nem::mod(value - min, max - min);
	}

	// limits

	template <std::totally_ordered T> constexpr T clamp(T value, T minIncl, T maxIncl)
	{ 
		if (value > maxIncl) 
			return maxIncl;
		else if (value < minIncl)
			return minIncl;
		else return value;
	}
	template <std::totally_ordered T> constexpr T clamp01(T value) { return nem::clamp(value, 0.0F, 1.0F); }

	// interpolation

	template <typename T> T smoothstep(T edge0, T edge1, T x)
	{
		x = nem::clamp((x - edge0) / (edge1 - edge0), (T)0.0, (T)1.0);
		return x * x * ((T)3.0 - (T)2.0 * x);
	}
	template <typename T> constexpr T lerp(T a, T b, T t) { return b * t + a * ((T)1.0 - t); }
	
	// consts

	template <typename T> constexpr T PI() { return (T)3.141592653589793; }
	template <typename T> constexpr T HALF_PI() { return (T)1.570796326794896; }
	template <typename T> constexpr T TWO_PI() { return (T)6.283185307179586; }
	template <typename T> constexpr T E() { return (T)2.718281828459045; }
	template <typename T> constexpr T PHI() { return (T)1.618033988749894; }
}