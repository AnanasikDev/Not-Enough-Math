#pragma once

#include "config.hpp"
#include "utils.hpp"
#include <cmath>

#define NEM_FAST_TRIG

namespace nem
{

#if defined(NEM_FAST_TRIG)

	template <std::floating_point T, int P = 2>
	constexpr T ft_sin_q1(T x)
	{
		if constexpr (P <= 0)
			return x;
		const T xxx{ x * x * x };
		if constexpr (P == 1)
			return x - xxx / 6.0f;
		if constexpr (P == 2)
			return x - xxx / 6.0f + xxx * x * x / 120.0f;
		if constexpr (P == 3)
			return x - xxx / 6.0f + xxx * x * x / 120.0f - xxx * xxx * x / 5040.0f;
		if constexpr (P >= 4)
			return x - xxx / 6.0f + xxx * x * x / 120.0f - xxx * xxx * x / 5040.0f + xxx * xxx * xxx / 362880.0f;
	}

	template <std::floating_point T, int P = 2>
	constexpr T ft_cos_q1 (T x)
	{
		if constexpr (P <= 0)
			return 1;
		const T xxx{ x * x * x };
		if constexpr (P == 1)
			return 1 - x * x / 2.0f;
		if constexpr (P == 2)
			return 1 - x * x / 2.0f + xxx * x / 24.0f;
		if constexpr (P == 3)
			return 1 - x * x / 2.0f + xxx * x / 24.0f - xxx * xxx / 720.0f;
		if constexpr (P >= 4)
			return 1 - x * x / 2.0f + xxx * x / 24.0f - xxx * xxx / 720.0f + xxx * xxx * x * x / 40320.0f;
	}

	template <std::floating_point T, int P = 2>
	constexpr T sin(T x)
	{
		const T s = x >= 0 ? 1 : -1;
		const int k = static_cast<int>(x * s / nem::HALF_PI<T>());
		x = nem::mod(x, nem::HALF_PI<T>());
		switch (k % 4)
		{
			case 0: return      ft_sin_q1<T, P>(x);
			case 1: return s *  ft_cos_q1<T, P>(x);
			case 2: return     -ft_sin_q1<T, P>(x);
			case 3: return s * -ft_cos_q1<T, P>(x);
		};
		return (T)0;
	}

	template <std::floating_point T, int P = 2>
	constexpr T cos(T x)
	{
		const T s = x >= 0 ? 1 : -1;
		const int k = static_cast<int>(x * s / nem::HALF_PI<T>());
		x = nem::mod(x, nem::HALF_PI<T>());
		switch (k % 4)
		{
			case 0: return      ft_cos_q1<T, P>(x);
			case 1: return s * -ft_sin_q1<T, P>(x);
			case 2: return     -ft_cos_q1<T, P>(x);
			case 3: return s *  ft_sin_q1<T, P>(x);
		};
		return (T)0;
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