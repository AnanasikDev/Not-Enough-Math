#pragma once

#include <concepts>
#include "config.hpp"
#include "utils.hpp"
#include "trig.hpp"

// from my older project
// https://github.com/AnanasikDev/AEngine/blob/main/AEngine/Core/Mathf.cpp

namespace nem
{
	namespace ease
	{
		template <std::floating_point T> constexpr T in_out_back(T v)
		{
			constexpr T c1 = (T)1.70158;
			constexpr T c2 = c1 * (T)1.525;
			v *= 2;

			return v < (T)0.5
				? (nem::sqr(v) * ((c2 + 1) * v - c2)) / 2
				: (nem::sqr(v - 2) * ((c2 + 1) * (v - 2) + c2) + 2) / 2;
		}

		template <std::floating_point T> constexpr T in_back(T v)
		{
			constexpr T c1 = (T)1.70158;
			constexpr T c2 = c1 + 1;

			return c2 * nem::cube(v) - c1 * nem::sqr(v);
		}

		template <std::floating_point T> constexpr T out_back(T v)
		{
			constexpr T c1 = (T)1.70158;
			constexpr T c2 = c1 + 1;

			return 1 + c2 * nem::cube(v - 1) + c1 * nem::sqr(v - 1);
		}

		template <std::floating_point T> constexpr T in_sine(T v)
		{
			return 1 - nem::cos(v * nem::PI<T>() * (T)0.5);
		}

		template <std::floating_point T> constexpr T out_sine(T v)
		{
			return nem::sin(v * nem::PI<T>() * (T)0.5);
		}

		template <std::floating_point T> constexpr T in_out_sine(T v)
		{
			return -(nem::cos(nem::PI<T>() * v) - 1) * (T)0.5;
		}

		template <std::floating_point T> constexpr T in_bounce(T v)
		{
			constexpr T n1 = (T)7.5625;
			constexpr T d1 = (T)(1.0 / 2.75);

			if (v < d1)
			{
				return n1 * v * v;
			}
			else if (v < 2 * d1)
			{
				return n1 * (v -= (T)1.5f * d1) * v + (T)0.75;
			}
			else if (v < (T)2.5 * d1)
			{
				return n1 * (v -= (T)2.25f * d1) * v + (T)0.9375;
			}
			else
			{
				return n1 * (v -= (T)2.625f * d1) * v + (T)0.984375;
			}
		}

		template <std::floating_point T> constexpr T out_bounce(T v)
		{
			constexpr T n1 = (T)7.5625;
			constexpr T d1 = (T)(1.0 / 2.75);

			if (v < 1 * d1)
			{
				return n1 * v * v;
			}
			else if (v < 2 * d1)
			{
				return n1 * (v -= (T)1.5 * d1) * v + (T)0.75;
			}
			else if (v < 2.5f * d1)
			{
				return n1 * (v -= (T)2.25 * d1) * v + (T)0.9375;
			}
			else
			{
				return n1 * (v -= (T)2.625 * d1) * v + (T)0.984375;
			}
		}

		template <std::floating_point T> constexpr T in_out_bounce(T v)
		{
			return v < 0.5
				? (1 - out_bounce(1 - 2 * v)) * (T)0.5
				: (1 + out_bounce(2 * v - 1)) * (T)0.5;
		}

		NEM_INLINE template <std::floating_point T> T in_elastic(T v)
		{
			constexpr T c4 = (2 * nem::PI<T>()) / (T)3.0;

			return v == 0
				? 0
				: (v == 1
				? 1
				: -nem::pow((T)2, (T)10 * v - (T)10) * nem::sin((v * (T)10 - (T)10.75) * c4));
		}

		NEM_INLINE template <std::floating_point T> T out_elastic(T v)
		{
			constexpr T c4 = (2 * nem::PI<T>()) / (T)3.0;

			return v == 0
				? 0
				: (v == 1
				? 1
				: nem::pow((T)2, (T)-10 * v) * nem::sin((v * (T)10 - (T)0.75) * c4) + (T)1);
		}

		NEM_INLINE template <std::floating_point T> T in_out_elastic(T v)
		{
			constexpr T c5 = (2 * nem::PI<T>()) / (T)4.5;

			return v == 0
				? 0
				: (v == 1
				? 1
				: (v < 0.5
				   ? -(nem::pow((T)2.0, (T)20 * v - (T)10) * nem::sin(((T)20 * v - (T)11.125) * c5)) * (T)0.5
				   : (nem::pow((T)2.0, (T)-20 * v + (T)10) * nem::sin(((T)20 * v - (T)11.125) * c5)) * (T)0.5 + (T)1));
		}

		template <std::floating_point T> constexpr T in_cubic(T v)
		{
			return v * v * v;
		}

		template <std::floating_point T> constexpr T out_cubic(T v)
		{
			return 1 - nem::cube(1 - v);
		}

		template <std::floating_point T> constexpr T in_out_cubic(T v)
		{
			return v < 0.5f ? 4 * v * v * v : 1 - nem::cube(-2 * v + 2) * (T)0.5;
		}
	}
}