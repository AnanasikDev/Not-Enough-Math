#pragma once

#include "utils.hpp"
#include "err.hpp"

#include <type_traits>
#include <cstddef>
#include <limits>

#define TEST_VEC_TRAITS(VecType, Scalar) \
    static_assert(sizeof(VecType) == sizeof(Scalar) * VecType::Comps, \
        #VecType " size mismatch! Possible unexpected padding."); \
    static_assert(std::is_standard_layout_v<VecType>, \
        #VecType " is not Standard Layout. This breaks C-compatibility/offsetof."); \
    \
    static_assert(std::is_trivially_copyable_v<VecType>, \
        #VecType " is not trivially copyable. This hurts pass-by-value performance."); \
    static_assert(std::is_trivially_destructible_v<VecType>, \
        #VecType " has a non-trivial destructor. This prevents it from being in a union."); \
    \
    static_assert(alignof(VecType) >= alignof(Scalar), \
        #VecType " alignment is weaker than its scalar component."); \
    \
    static_assert(std::is_default_constructible_v<VecType>, \
        #VecType " should be default constructible for array allocations."); \
    static_assert(std::is_trivially_copy_constructible_v<VecType>, \
        #VecType " copy constructor is not trivial."); \
    static_assert(std::is_trivially_move_constructible_v<VecType>, \
        #VecType " move constructor is not trivial (math types should be POD-like).");

#define TEST_VEC_CLASS(ClassName) \
    TEST_VEC_TRAITS(ClassName<double>, double); \
    TEST_VEC_TRAITS(ClassName<float>, float); \
    TEST_VEC_TRAITS(ClassName<unsigned long long int>, unsigned long long int); \
    TEST_VEC_TRAITS(ClassName<long long int>, long long int); \
    TEST_VEC_TRAITS(ClassName<long int>, long int); \
    TEST_VEC_TRAITS(ClassName<unsigned long int>, unsigned long int); \
    TEST_VEC_TRAITS(ClassName<short>, short); \
    TEST_VEC_TRAITS(ClassName<unsigned short>, unsigned short); \
    TEST_VEC_TRAITS(ClassName<char>, char); \
    TEST_VEC_TRAITS(ClassName<unsigned char>, unsigned char);

namespace nem
{
	template<typename vec_derived_t, typename T, size_t N>
	struct base_vector_t
	{
		using Type = T;
		static constexpr size_t Comps = N;

		static_assert(N > 0 && "Not Enough Math: Vector N must be greater than 0");

		constexpr vec_derived_t& _impl_rw() { return (vec_derived_t&)*this; }
        constexpr const vec_derived_t& _impl_r() const { return (const vec_derived_t&)*this; }
        
		constexpr T& operator[](size_t index) { return _impl_rw().data[index]; }
		constexpr const T& operator[](size_t index) const { return _impl_r().data[index]; }

		static constexpr vec_derived_t NaN() { return vec_derived_t(std::numeric_limits<T>::quiet_NaN()); }

		vec_derived_t& operator+=(const vec_derived_t& rhs)
		{
			for (size_t i = 0; i < N; ++i)
			{
				(*this)[i] += rhs[i];
			}
			return _impl_rw();
		}

		vec_derived_t& operator-=(const vec_derived_t& rhs)
		{
			for (size_t i = 0; i < N; ++i)
			{
				(*this)[i] -= rhs[i];
			}
			return _impl_rw();
		}

		vec_derived_t& operator*=(const vec_derived_t& rhs)
		{
			for (size_t i = 0; i < N; ++i)
			{
				(*this)[i] *= rhs[i];
			}
			return _impl_rw();
		}

		vec_derived_t& operator*=(T scalar)
		{
			for (size_t i = 0; i < N; ++i)
			{
				(*this)[i] *= scalar;
			}
			return _impl_rw();
		}

		vec_derived_t& operator/=(const vec_derived_t& rhs)
		{
			for (size_t i = 0; i < N; ++i)
			{
				(*this)[i] /= rhs[i];
			}
			return _impl_rw();
		}

		vec_derived_t& operator/=(T scalar)
		{
			if constexpr (std::is_floating_point_v<T>)
            {
                const T fac = (T)1.0 / scalar;
				for (size_t i = 0; i < N; ++i)
				{
					(*this)[i] *= fac;
				}
            }
            else
            {
				for (size_t i = 0; i < N; ++i)
				{
					(*this)[i] /= scalar;
				}
			}
			return _impl_rw();
		}

		friend vec_derived_t operator+(vec_derived_t lhs, const vec_derived_t& rhs)
		{
			lhs += rhs;
			return lhs;
		}

		friend vec_derived_t operator-(vec_derived_t lhs, const vec_derived_t& rhs)
		{
			lhs -= rhs;
			return lhs;
		}

		friend vec_derived_t operator*(vec_derived_t lhs, const vec_derived_t& rhs)
		{
			lhs *= rhs;
			return lhs;
		}

		friend vec_derived_t operator*(vec_derived_t vec, T scalar)
		{
			vec *= scalar;
			return vec;
		}

		friend vec_derived_t operator*(T scalar, vec_derived_t vec)
		{
			vec *= scalar;
			return vec;
		}

		friend vec_derived_t operator/(vec_derived_t lhs, const vec_derived_t& rhs)
		{
			lhs /= rhs;
			return lhs;
		}

		friend vec_derived_t operator/(vec_derived_t vec, T scalar)
		{
			vec /= scalar;
			return vec;
		}

		friend vec_derived_t operator/(T scalar, vec_derived_t vec)
		{
			vec /= scalar;
			return vec;
		}
	};

	template <typename T>
	struct base_vector_2 : public base_vector_t<base_vector_2<T>, T, 2>
	{
		static constexpr size_t N = 2;
		union
		{
			T data[N]{ (T)0 };
			struct { T x, y; };
			struct { T u, v; };
			struct { T s, t; };
			struct { T min, max; };
			struct { T width, height; };
		};

		constexpr base_vector_2() : x(T{}), y(T{}) {}
		constexpr base_vector_2(T _scalar) : x(_scalar), y(_scalar) {}
		constexpr base_vector_2(T _x, T _y) : x(_x), y(_y) {}
	};
	TEST_VEC_CLASS(base_vector_2)

	template <typename T>
	struct base_vector_3 : public base_vector_t<base_vector_3<T>, T, 3>
	{
		static constexpr size_t N = 3;
		union
		{
			T data[N]{ (T)0 };
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		constexpr base_vector_3() : x(T{}), y(T{}), z(T{}) {}
		constexpr base_vector_3(T _scalar) : x(_scalar), y(_scalar), z(_scalar) {}
		constexpr base_vector_3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	};
	TEST_VEC_CLASS(base_vector_3)

	template <typename T>
	struct base_vector_4 : public base_vector_t<base_vector_4<T>, T, 4>
	{
		static constexpr size_t N = 4;
		union
		{
			T data[N]{ (T)0 };
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			struct { T min1, min2, max1, max2; };
		};

		constexpr base_vector_4() : x(T{}), y(T{}), z(T{}), w(T{}) {}
		constexpr base_vector_4(T _scalar) : x(_scalar), y(_scalar), z(_scalar), w(_scalar) {}
		constexpr base_vector_4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
	};
	TEST_VEC_CLASS(base_vector_4)

	template <typename T, size_t N>
	struct base_vector : public base_vector_t<base_vector<T, N>, T, N>
	{
		T data[N]{ (T)0 };

		constexpr base_vector() : data{} {}
		constexpr base_vector(T _scalar) : data{}
		{
			for (size_t i = 0; i < N; ++i)
			{
				data[i] = _scalar;
			}
		}
	};

	using int2 = base_vector_2<int>;
	using int3 = base_vector_3<int>;
	using int4 = base_vector_4<int>;
	using float2 = base_vector_2<float>;
	using float3 = base_vector_3<float>;
	using float4 = base_vector_4<float>;

	namespace color
	{
		static constexpr float ALPHA_TRANSPARENT = 0.f;
		static constexpr float ALPHA_OPAQUE = 1.f;

		static NEM_INLINE float4 rgb(float r, float g, float b) { return float4(r, g, b, 1.f); }
		static NEM_INLINE float4 rgba(float r, float g, float b, float a) { return float4(r, g, b, a); }
		static NEM_INLINE float4 opaque(float3 rgb) { return float4(rgb.r, rgb.g, rgb.b, ALPHA_OPAQUE); }
		static NEM_INLINE float4 opaque(float4 rgba) { return float4(rgba.r, rgba.g, rgba.b, ALPHA_OPAQUE); }
		static NEM_INLINE float4 transparent(float3 rgb) { return float4(rgb.r, rgb.g, rgb.b, ALPHA_TRANSPARENT); }
		static NEM_INLINE float4 transparent(float4 rgba) { return float4(rgba.r, rgba.g, rgba.b, ALPHA_TRANSPARENT); }

		static NEM_INLINE float4 clear  = rgba(0.f, 0.f, 0.f, ALPHA_TRANSPARENT);
		static NEM_INLINE float4 white  = rgba(1.f, 1.f, 1.f, ALPHA_OPAQUE);
		static NEM_INLINE float4 black  = rgba(0.f, 0.f, 0.f, ALPHA_OPAQUE);
		static NEM_INLINE float4 red    = rgb(1.f, 0.f, 0.f);
		static NEM_INLINE float4 green  = rgb(0.f, 1.f, 0.f);
		static NEM_INLINE float4 blue   = rgb(0.f, 0.f, 1.f);
		static NEM_INLINE float4 cyan   = rgb(0.f, 1.f, 1.f);
		static NEM_INLINE float4 yellow = rgb(1.f, 1.f, 0.f);
	};
}

#ifdef TEST_VEC_CLASS
#undef TEST_VEC_CLASS
#endif

#ifdef TEST_VEC_TRAITS
#undef TEST_VEC_TRAITS
#endif
