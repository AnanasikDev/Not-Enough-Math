#pragma once

#include <concepts>

namespace nem
{
	template <std::floating_point T> constexpr T PI() { return (T)3.141592653589793; }
	template <std::floating_point T> constexpr T HALF_PI() { return (T)1.570796326794896; }
	template <std::floating_point T> constexpr T QUARTER_PI() { return (T)0.785398163397; }
	template <std::floating_point T> constexpr T TWO_PI() { return (T)6.283185307179586; }
	template <std::floating_point T> constexpr T E() { return (T)2.718281828459045; }
	template <std::floating_point T> constexpr T PHI() { return (T)1.618033988749894; }
	template <std::floating_point T> constexpr T Deg2Rad() { return nem::TWO_PI<T>() / (T)360.0; }
	template <std::floating_point T> constexpr T Rad2Deg() { return (T)1.0 / nem::Deg2Rad<T>(); }
}