#pragma once

#include <concepts>

#include "config.hpp"

namespace nem
{
	// limits
	template <std::totally_ordered T> constexpr T clamp(T value, T minIncl, T maxIncl) { if (value > maxIncl) return maxIncl; else if (value < minIncl) return minIncl; else return value; }
	template <std::totally_ordered T> constexpr T clamp01(T value) { return nem::clamp(value, 0.0F, 1.0F); }
	template <typename T> constexpr T abs(T value) { return (T)(value >= 0 ? value : -value); }

	// powers
	template <typename T> constexpr T sqr(T value) { return (T)(value * value); }
	template <typename T> constexpr T cube(T value) { return (T)(value * value * value); }
	template <typename T> constexpr T pow2(T value) { return (T)(nem::sqr(nem::sqr(value))); }
	template <typename T> constexpr T pow3(T value) { return (T)(nem::sqr(nem::sqr(value))); }
	template <typename T> constexpr T pow4(T value) { return (T)(nem::sqr(nem::sqr(value))); }

	template <typename T, int Precision = 20>
	constexpr T sqrt(T value)
	{
		constexpr T ZERO = (T)0.0;
		if (value <= ZERO) return ZERO;
		T result = value;
		for (int i = 0; i < Precision; ++i) result = 0.5 * (result + value / result);
		return result;
	}

	template <std::integral T, int Precision = 20>
	constexpr T sqrt(T value)
	{
		constexpr T ZERO = (T)0;
		if (value <= ZERO) return ZERO;
		nem::real result = value;
		for (int i = 0; i < Precision; ++i) result = (nem::real)0.5 * (result + static_cast<nem::real>(value) / result);
		return static_cast<T>(result);
	}

	// interpolation

	template <typename T> T smoothstep(T edge0, T edge1, T x)
	{
		x = nem::clamp((x - edge0) / (edge1 - edge0), (T)0.0, (T)1.0);
		return x * x * ((T)3.0 - (T)2.0 * x);
	}
	template <typename T> constexpr T lerp(T a, T b, T t) { return b * t + a * ((T)1.0 - t); }
	template <typename T> constexpr T is_nearly_zero(T a, const T eps = (T)1e-6) { return nem::abs(a - (T)0.0) < eps; }

	// consts

	template <typename T> constexpr T PI() { return (T)3.141592653589793; }
	template <typename T> constexpr T HALF_PI() { return (T)1.570796326794896; }
	template <typename T> constexpr T TWO_PI() { return (T)6.283185307179586; }
	template <typename T> constexpr T E() { return (T)2.718281828459045; }
	template <typename T> constexpr T PHI() { return (T)1.618033988749894; }
};