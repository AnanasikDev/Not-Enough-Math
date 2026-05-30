#pragma once

#include <concepts>

namespace nem
{
	template <std::floating_point T> constexpr T SQRT2 =  		(T)1.414213562373095;
	template <std::floating_point T> constexpr T SQRT3 =  		(T)1.73205080756887;
	template <std::floating_point T> constexpr T SQRT5 =  		(T)2.236067977499789;
	template <std::floating_point T> constexpr T PI =  		  	(T)3.141592653589793;
	template <std::floating_point T> constexpr T HALF_PI =   	(T)nem::PI<T> * (T)0.5;
	template <std::floating_point T> constexpr T QUARTER_PI =  	(T)nem::PI<T> * (T)0.25;
	template <std::floating_point T> constexpr T TWO_PI =  		(T)nem::PI<T> * (T)2.0;
	template <std::floating_point T> constexpr T E =  			(T)2.718281828459045;
	template <std::floating_point T> constexpr T ESQR =  		   nem::E<T> * nem::E<T>;
	template <std::floating_point T> constexpr T PHI =  		(T)1.618033988749894;
	template <std::floating_point T> constexpr T DEG_TO_RAD =  	   nem::TWO_PI<T> / (T)360.0;
	template <std::floating_point T> constexpr T RAD_TO_DEG =  	(T)1.0 / nem::DEG_TO_RAD<T>;
}