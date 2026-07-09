#pragma once

#include "config.hpp"
#include "utils.hpp"
#include "power.hpp"
#include <concepts>
#include "intrinsics.hpp"

#define NEM_FAST_TRIG
#ifndef NEM_FAST_TRIG
	#include <cmath>
#endif

namespace nem
{
	template <nem::scalar_type T>
	struct sincos
	{
		T sin;
		T cos;
	};

	static constexpr int DEFAULT_TRIG_PRECISION = 1;
    static constexpr float DEFAULT_TRIG_EPSILON = 0.01f;

    /// Converts degrees to radians. Used to make units explicit.
	template <nem::scalar_type T>
	constexpr T degrees(T degrees) noexcept
	{
		return nem::DEG_TO_RAD<T> * degrees;
	}

	/// Converts radians to radians (passes the argument unchanged). Used to make units explicit.
	template <nem::scalar_type T>
	constexpr T radians(T radians) noexcept
	{
		return radians;
	}

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

	/// Computes sin and cos together in a single range reduction pass, instead of paying for it
	/// twice (once per nem::sin/nem::cos call). Both quadrant-1 polynomials still have to be
	/// evaluated once each (they're different polynomials), but the division + rounding + multiply-subtract
	/// range reduction and the sign/abs extraction only happen once.
	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr nem::sincos<T> get_sincos(T radians)
	{
		const T s = nem::sign(radians);
		const T absx = radians * s;
		const int k = static_cast<int>(absx / nem::HALF_PI<T> + (T)0.5);
		const T r = absx - static_cast<T>(k) * nem::HALF_PI<T>;

		const T sin_q1 = ft_sin_q1<T, P>(r);
		const T cos_q1 = ft_cos_q1<T, P>(r);

		T sin_r, cos_r;
		switch (k % 4)
		{
			case 0: sin_r =  sin_q1; cos_r =  cos_q1; break;
			case 1: sin_r =  cos_q1; cos_r = -sin_q1; break;
			case 2: sin_r = -sin_q1; cos_r = -cos_q1; break;
			case 3: sin_r = -cos_q1; cos_r =  sin_q1; break;
			default: NEM_UNREACHABLE();
		}

		return nem::sincos<T> { s * sin_r, cos_r };
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

	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	nem::sincos<T> get_sincos(T radians)
	{
		return nem::sincos<T> { nem::sin(radians), nem::cos(radians) };
	}

#endif

	/// -------------------------------------------
	/// Tangent, cotangent, secant, cosecant
	/// -------------------------------------------

	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr T tan(T x)
	{
		const nem::sincos<T> sc = nem::get_sincos<T, P>(x);
		if (nem::is_zero(sc.cos))
		{
			return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero, "Tangent is undefined here (cosine is zero)");
		}
		return sc.sin / sc.cos;
	}

	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr T ctg(T x)
	{
		const nem::sincos<T> sc = nem::get_sincos<T, P>(x);
		if (nem::is_zero(sc.sin))
		{
			return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero, "Cotangent is undefined here (sine is zero)");
		}
		return sc.cos / sc.sin;
	}

	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr T sec(T x)
	{
		const T c = nem::cos<T, P>(x);
		if (nem::is_zero(c))
		{
			return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero, "Secant is undefined here (cosine is zero)");
		}
		return (T)1.0 / c;
	}

	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr T csc(T x)
	{
		const T s = nem::sin<T, P>(x);
		if (nem::is_zero(s))
		{
			return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero, "Cosecant is undefined here (sine is zero)");
		}
		return (T)1.0 / s;
	}

	/// -------------------------------------------
	/// Inverse trigonometric functions
	/// -------------------------------------------

	/// Core polynomial approximation of atan(x), valid on [-1, 1]. nem::atan reduces any other
	/// argument into this range first via atan(x) = sign(x) * HALF_PI - atan(1 / x).
	/// Minimax coefficients fitted for P = 1, 2, 3 (max error roughly 5e-3, 6e-4, 8e-5).
	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr T ft_atan_q1(T x)
	{
		const T x2 = x * x;
		if constexpr (P == 1)
		{
			// minimax (Remez) fit
			return x * (0.97239411 - 0.19194795 * x2);
		}
		else if constexpr (P == 2)
		{
			// minimax (Remez) fit
			return x * (0.99535796 + x2 * (-0.28869025 + 0.07933904 * x2));
		}
		else if constexpr (P >= 3)
		{
			// minimax (Remez) fit
			return x * (0.99921385 + x2 * (-0.32117487 + x2 * (0.14626402 - 0.0389862 * x2)));
		}
	}

	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr T atan(T x)
	{
		const T s = nem::sign(x);
		const T absx = s * x;
		if (absx <= (T)1.0)
		{
			return s * ft_atan_q1<T, P>(absx);
		}
		return s * (nem::HALF_PI<T> - ft_atan_q1<T, P>((T)1.0 / absx));
	}

	/// Two-argument arctangent: the angle of the point (x, y), in (-PI, PI], resolved using the
	/// sign of both arguments instead of just their ratio.
	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr T atan2(T y, T x)
	{
		if (nem::is_zero(x))
		{
			if (nem::is_zero(y))
			{
				return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero, "atan2 is undefined at the origin");
			}
			return nem::sign(y) * nem::HALF_PI<T>;
		}

		const T base = nem::atan<T, P>(y / x);
		return (x > (T)0.0) ? base : base + nem::sign(y) * nem::PI<T>;
	}

	/// Minimax polynomial approximation of acos, valid on [-1, 1], with a max error of roughly 6.7e-5.
	/// A widely used public-domain approximation (see e.g. "Efficient approximations for the arc cosine
	/// function", Lee, 2008, and countless graphics-programming write-ups building on it).
	template <std::floating_point T>
	constexpr T acos(T x)
	{
		const T negate = T(x < 0);
		const T ax = nem::abs(x);

		T ret = (T)-0.0187293;
		ret = ret * ax + (T)0.0742610;
		ret = ret * ax - (T)0.2121144;
		ret = ret * ax + (T)1.5707288;
		ret = ret * nem::sqrt((T)1.0 - ax);
		ret = ret - (T)2.0 * negate * ret;
		return negate * nem::PI<T> + ret;
	}

	template <std::floating_point T>
	constexpr T asin(T x)
	{
		return nem::HALF_PI<T> - nem::acos(x);
	}

	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr T actg(T x)
	{
		return nem::HALF_PI<T> - nem::atan<T, P>(x);
	}

	/// Two-argument arc-cotangent: the angle whose cotangent is x / y, equivalent to nem::atan2
	/// with the arguments given in x/y order instead of y/x.
	template <std::floating_point T, int P = DEFAULT_TRIG_PRECISION>
	constexpr T actg2(T x, T y)
	{
		return nem::atan2<T, P>(x, y);
	}
}