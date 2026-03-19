#pragma once

namespace nem
{
	template <typename T> static inline constexpr T clamp(const T value, const T minIncl, const T maxIncl) { if (value > maxIncl) return maxIncl; else if (value < minIncl) return minIncl; else return value; }
	template <typename T> static inline constexpr T clamp01(const T value) { return nem::clamp(value, 0.0F, 1.0F); }
	template <typename T> static inline constexpr T abs(const T value) { return (T)(value >= 0 ? value : -value); }
	template <typename T> static inline constexpr T sqr(const T value) { return (T)(value * value); }
	template <typename T> static inline constexpr T cube(const T value) { return (T)(value * value * value); }
	template <typename T> static inline constexpr T pow4(const T value) { return (T)(nem::sqr(nem::sqr(value))); }
	static float smoothstep(float edge0, float edge1, float x)
	{
		x = nem::clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
		return x * x * (3 - 2 * x);
	}

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

	template <typename T> static inline constexpr T lerp(const T a, const T b, const T t) { return b * t + a * ((T)1.0 - t); }

	// consts

	template <typename T> static inline constexpr T PI() { return (T)3.141592653589793; }
	template <typename T> static inline constexpr T HALF_PI() { return (T)1.570796326794896; }
	template <typename T> static inline constexpr T TWO_PI() { return (T)6.283185307179586; }
	template <typename T> static inline constexpr T E() { return (T)2.718281828459045; }
	template <typename T> static inline constexpr T PHI() { return (T)1.618033988749894; }
};