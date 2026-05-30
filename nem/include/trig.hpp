#pragma once

#include "config.hpp"
#include "utils.hpp"
#include <concepts>
#include "intrinsics.hpp"

#define NEM_FAST_TRIG
#ifndef NEM_FAST_TRIG
	#include <cmath>
#endif

namespace nem
{

	static constexpr int DEFAULT_TRIG_PRECISION = 1;
	static constexpr float DEFAULT_TRIG_EPSILON = 0.01f;

#if defined(NEM_FAST_TRIG)

	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr T ft_sin_q1(T x)
	{
		const T x2 = x * x;
		if constexpr (P == 1)
		{
			return x * (-0.162 * x2 + 1.0); // my custom approximation
		}
		else if constexpr (P == 2)
		{
			// minimax https://publik-void.github.io/sin-cos-approximations
			return x * (0.999891821255810892885564707156941565 + x2 * (-0.165960116540878989063185380996540407 + 0.00760290334336935120704015646842617915 * x2));
		}
		else if constexpr (P >= 3)
		{
			// minimax https://publik-void.github.io/sin-cos-approximations
			return x * (0.999996615908002773079325846913220383 + x2 * (-0.16664828381895056829366054140948866 + x2 * (0.00830632522715989396465411782615901079 - x2 * 0.00018363653976946785297280224158683484)));
		}
	}

	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr T ft_cos_q1 (T x)
	{
		const T x2 = x * x;
		if constexpr (P == 1)
		{
			return -0.475 * x2 + 1.0; // my custom approximation
		}
		else if constexpr (P == 2)
		{
			// minimax https://publik-void.github.io/sin-cos-approximations
			return 0.997372645040477990699027658698347186 + x2 * (-0.490966242354240750313919970830772248 + 0.0351569652103601536791893003031729288 * x2);
		}
		else if constexpr (P >= 3)
		{
			// minimax https://publik-void.github.io/sin-cos-approximations
			return 0.999970210689953068626323587055728078 + x2 * (-0.499782706704688809140466617726333455 + x2 * (0.0413661149638482252569383872576459943 - x2 * 0.0012412397582398600702129604944720102));
		}
	}

	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr T sin(T x)
	{
		const T s = nem::sign(x);
		const T absx = x * s;
		const int k = static_cast<int>(absx / nem::HALF_PI<T> + (T)0.5);
		const T r = absx - static_cast<T>(k) * nem::HALF_PI<T>;
		switch (k % 4)
		{
			case 0: return s *  ft_sin_q1<T, P>(r);
			case 1: return s *  ft_cos_q1<T, P>(r);
			case 2: return s * -ft_sin_q1<T, P>(r);
			case 3: return s * -ft_cos_q1<T, P>(r);
		};
		NEM_UNREACHABLE();
	}

	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr T cos(T x)
	{
		const T absx = nem::abs(x);
		const int k = static_cast<int>(absx / nem::HALF_PI<T> + (T)0.5);
		const T r = absx - static_cast<T>(k) * nem::HALF_PI<T>;
		switch (k % 4)
		{
			case 0: return  ft_cos_q1<T, P>(r);
			case 1: return -ft_sin_q1<T, P>(r);
			case 2: return -ft_cos_q1<T, P>(r);
			case 3: return  ft_sin_q1<T, P>(r);
		};
		NEM_UNREACHABLE();
	}

#else

    template <std::floating_point T> T sin(T x)
    {
        return ::sinf(x);
    }

	template <std::floating_point T> T cos(T x)
	{
		return ::cosf(x);
	}
#endif
}