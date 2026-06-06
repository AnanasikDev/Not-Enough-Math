#pragma once

#include <bit>
#include "config.hpp"
#include "utils.hpp"

namespace nem
{
	namespace fast
    {
    
    template <std::floating_point T = float>
    constexpr T log2(T x)
    {
        uint32_t bits = std::bit_cast<uint32_t>(x);
		return float(bits) * (1.0f / (1 << 23)) - 126.94269504f;
    }

    } // namespace fast

    namespace accurate
    {
    
    template <std::floating_point T = float>
    constexpr T log2(T x)
    {
        uint32_t bits = std::bit_cast<uint32_t>(x);
		
		int exp = int((bits >> 23) & 0xFF) - 127;

		bits = (bits & 0x007FFFFF) | 0x3F800000;
		float m = std::bit_cast<float>(bits);

		float y = m - 1.0f;
		float poly = y * (1.4426950f
				+ y * (-0.7213475f
				+ y *  0.4809f));

		return float(exp) + poly;
    }
    
	} // accurate namespace


    /// -------------------------------------------
    /// Logs
    /// -------------------------------------------

    template <std::floating_point T = float, nem::Precision Prec = nem::default_precision>
    constexpr T log2(T x)
    {
        if constexpr (std::is_same_v<T, float>)
        {
            if constexpr (Prec == nem::accurate::mode)
            {
				return nem::accurate::log2<T>(x);
            }
            else if constexpr (Prec == nem::fast::mode)
            {
                return nem::fast::log2<T>(x);
			}
        }
        else
        {
            // TODO: add implementation for double and long double
            return nem::log2<float, Prec>(static_cast<float>(x));
            // return nem::error::invalid_result<T>(nem::error::Kind::InvalidArgument, "Log2 doesn't support other floating-point types than float (yet)");
		}
    }

    template <std::floating_point T, nem::Precision Prec = nem::default_precision>
    constexpr T log(T base, T value)
	{
		if (nem::is_zero_or_neg(base) || nem::equal(base, (T)1.0))
		{
			return nem::error::invalid_result<T>();
		}
		if (nem::is_zero_or_neg(value))
		{
			return nem::error::invalid_result<T>();
        }
		return nem::log2<T, Prec>(value) / nem::log2<T, Prec>(base);
    }

    template <std::floating_point T, nem::Precision Prec = nem::default_precision>
    constexpr T ln(T value)
    {
		if (nem::is_zero_or_neg(value))
		{
			return nem::error::invalid_result<T>();
		}
		return nem::log2<T, Prec>(value) / nem::LOG2E<T>;
	}

    template <std::integral T, nem::Precision Prec = nem::default_precision>
    constexpr T log(T base, T value)
	{
		return (T)nem::round(log<double, Prec>(static_cast<double>(base), static_cast<double>(value)));
    }

    /// -------------------------------------------
	/// Exponentiation
	/// -------------------------------------------

    template <std::floating_point T, nem::Precision Prec = nem::default_precision>
	constexpr T exp2(T x)
    {
        if constexpr (std::is_same_v<T, float>)
        {
			int i = static_cast<int>(x);
			float frac = x - float(i);
	
			float p = 1.0f
				+ frac * (0.6931472f
				+ frac * (0.2402265f
				+ frac * (0.0555041f
				+ frac *  0.0096181f)));
	
			uint32_t bits  = std::bit_cast<uint32_t>(p);
			bits += uint32_t(i) << 23;
			return std::bit_cast<float>(bits);
        }
        else
        {
            // TODO: implement for double and long double
            return nem::exp2<float, Prec>(x);
		}
    }

    template <nem::scalar_type T, std::integral E>
    constexpr T pow(T base, E exp)
	{
		T result = exp2<T>(log2<T>(nem::abs(base)) * T(exp));
		return (exp % 2 != 0) ? -result : result;
	}

    template <std::floating_point T, nem::Precision Prec = nem::default_precision>
    constexpr T pow(T base, T exp, nem::unsafe_t)
	{
		return exp2<T, Prec>(log2<T, Prec>(base) * exp);
	}

    template <std::floating_point T, nem::Precision Prec = nem::default_precision>
    constexpr T pow(T base, T exp, nem::safe_t = nem::safe)
    {
        // TODO: likely/unlikely paths
        
		if (nem::is_zero(exp))
		{
			return (T)1.0;
        }
        
		if (nem::is_zero(base))
		{
			return (T)0.0;
        }

        // most common
        if (base > 0.0)
        {
            return nem::pow(base, exp, nem::unsafe);
        }

        // base < 0
		if (nem::is_whole(exp))
		{
			return nem::pow<T, long long>(base, (long long)(exp));
		}
		else
		{
			return nem::error::invalid_result<T>(nem::error::Kind::DivisionByZero, "When base < 0 exponent cannot be float");
		}
	}

	/// -------------------------------------------
	/// Roots
	/// -------------------------------------------

	template <typename T>
	NEM_INLINE T sqrt(T value)
	{
		if (nem::is_zero_or_neg(value))
		{
			 value = T{ 0 };
		}
		if constexpr (std::is_floating_point_v<T>)
		{
			return static_cast<T>(nem::intr::_nem_sqrt(value));
		}
		else if constexpr (std::is_integral_v<T>)
		{
			return static_cast<T>(nem::intr::_nem_sqrt(static_cast<double>(value)));
		}
	}

	template <std::floating_point T, int Precision = 20>
	constexpr T csqrt(T value)
	{
		if (nem::is_zero_or_neg(value))
		{
			return (T)0.0;
		}

		T result = value;
		for (int i = 0; i < Precision; ++i)
		{
			result = 0.5 * (result + value / result);
		}
		return result;
	}

	template <std::integral T, int Precision = 20>
	constexpr T csqrt(T value)
	{
		if (nem::is_zero_or_neg(value))
		{
			return (T)0.0;
		}

		nem::real result = value;
		for (int i = 0; i < Precision; ++i)
		{
			result = (nem::real)0.5 * (result + static_cast<nem::real>(value) / result);
		}
		return static_cast<T>(result);
    }

    /// binary search for the approximation of integer square root.
    /// original implementation from "Hacker's Delight, Ch. 11: Integer square root, simple binary search."
    inline int isqrt(unsigned x)
	{
		unsigned a, b, m; // Limits and midpoint.
		a = 1;
		b = (x >> 5) + 8; // See text.
		if (b > 65535) b = 65535;
		do {
			m = (a + b) >> 1;
			if (m*m > x) b = m - 1;
			else a = m + 1;
        } while (b >= a);
        
		return a - 1;
    }

    /// binary search for the approximation of integer cubic root.
    /// original implementation from "Hacker's Delight, Ch. 11: Integer Cube Root"
    inline int icbrt(unsigned x)
	{
		int s;
		unsigned y, b;
		y = 0;
        for (s = 30; s >= 0; s = s - 3)
		{
			y = 2*y;
			b = (3*y*(y + 1) + 1) << s;
            if (x >= b)
			{
				x = x - b;
				y = y + 1;
			}
		}
		return y;
	}
}