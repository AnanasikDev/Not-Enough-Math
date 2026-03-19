#pragma once

#include <concepts>

namespace nem
{
	// limits
	template <std::totally_ordered T> static inline constexpr T clamp(const T value, const T minIncl, const T maxIncl) { if (value > maxIncl) return maxIncl; else if (value < minIncl) return minIncl; else return value; }
	template <std::totally_ordered T> static inline constexpr T clamp01(const T value) { return nem::clamp(value, 0.0F, 1.0F); }
	template <typename T> static inline constexpr T abs(const T value) { return (T)(value >= 0 ? value : -value); }

	// powers
	template <typename T> static inline constexpr T sqr(const T value) { return (T)(value * value); }
	template <typename T> static inline constexpr T cube(const T value) { return (T)(value * value * value); }
	template <typename T> static inline constexpr T pow2(const T value) { return (T)(nem::sqr(nem::sqr(value))); }
	template <typename T> static inline constexpr T pow3(const T value) { return (T)(nem::sqr(nem::sqr(value))); }
	template <typename T> static inline constexpr T pow4(const T value) { return (T)(nem::sqr(nem::sqr(value))); }

	template <typename T, int Precision = 20>
	static inline constexpr T sqrt(T value)
	{
		constexpr T ZERO = (T)0.0;
		if (value <= ZERO) return ZERO;
		T result = value;
		for (int i = 0; i < Precision; ++i) result = 0.5 * (result + value / result);
		return result;
	}

	template <int Precision = 20>
	static inline constexpr int sqrt(int value)
	{
		constexpr int ZERO = 0;
		if (value <= ZERO) return ZERO;
		double result = value;
		for (int i = 0; i < Precision; ++i) result = 0.5 * (result + static_cast<double>(value) / result);
		return static_cast<int>(result);
	}

	// interpolation

	template <typename T> static T smoothstep(T edge0, T edge1, T x)
	{
		x = nem::clamp((x - edge0) / (edge1 - edge0), (T)0.0, (T)1.0);
		return x * x * ((T)3.0 - (T)2.0 * x);
	}
	template <typename T> static inline constexpr T lerp(const T a, const T b, const T t) { return b * t + a * ((T)1.0 - t); }
	template <typename T> static inline constexpr T is_nearly_zero(const T a, const T eps = (T)1e-6) { return nem::abs(a - (T)0.0) < eps; }

	// consts

	template <typename T> static inline constexpr T PI() { return (T)3.141592653589793; }
	template <typename T> static inline constexpr T HALF_PI() { return (T)1.570796326794896; }
	template <typename T> static inline constexpr T TWO_PI() { return (T)6.283185307179586; }
	template <typename T> static inline constexpr T E() { return (T)2.718281828459045; }
	template <typename T> static inline constexpr T PHI() { return (T)1.618033988749894; }
};