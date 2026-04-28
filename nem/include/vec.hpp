#pragma once

#include "utils.hpp"
#include "err.hpp"

#include <type_traits>
#include <cstddef>

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
	template<typename Derived, typename T, size_t N>
	struct BaseVectorT
	{
		using Type = T;
		static constexpr size_t Comps = N;

		static_assert(N > 0 && "Not Enough Math: Vector N must be greater than 0");

		constexpr Derived& _impl_rw() { return (Derived&)*this; }
		constexpr const Derived& _impl_r() const { return (const Derived&)*this; }
		constexpr T& comp_rw(size_t index) { return _impl_rw().data[index]; }
		constexpr const T& comp_r(size_t index) const { return _impl_r().data[index]; }
		constexpr T& operator[](size_t index) { return comp_rw(index); }
		constexpr const T& operator[](size_t index) const { return comp_r(index); }

		Derived& operator+=(const Derived& rhs)
		{
			for (size_t i = 0; i < N; ++i)
			{
				(*this)[i] = this->comp_r(i) + rhs.comp_r(i);
			}
			return _impl_rw();
		}

		Derived& operator-=(const Derived& rhs)
		{
			for (size_t i = 0; i < N; ++i)
			{
				(*this)[i] = this->comp_r(i) - rhs.comp_r(i);
			}
			return _impl_rw();
		}

		Derived& operator*=(const Derived& rhs)
		{
			for (size_t i = 0; i < N; ++i)
			{
				(*this)[i] = this->comp_r(i) * rhs.comp_r(i);
			}
			return _impl_rw();
		}

		Derived& operator*=(T scalar)
		{
			for (size_t i = 0; i < N; ++i)
			{
				(*this)[i] = this->comp_r(i) * scalar;
			}
			return _impl_rw();
		}

		Derived& operator/=(const Derived& rhs)
		{
			for (size_t i = 0; i < N; ++i)
			{
				(*this)[i] = this->comp_r(i) / rhs.comp_r(i);
			}
			return _impl_rw();
		}

		Derived& operator/=(T scalar)
		{
			for (size_t i = 0; i < N; ++i)
			{
				(*this)[i] = this->comp_r(i) / scalar;
			}
			return _impl_rw();
		}

		friend Derived operator+(Derived lhs, const Derived& rhs)
		{
			lhs += rhs;
			return lhs;
		}

		friend Derived operator-(Derived lhs, const Derived& rhs)
		{
			lhs -= rhs;
			return lhs;
		}

		friend Derived operator*(Derived lhs, const Derived& rhs)
		{
			lhs *= rhs;
			return lhs;
		}

		friend Derived operator*(Derived vec, T scalar)
		{
			vec *= scalar;
			return vec;
		}

		friend Derived operator*(T scalar, Derived vec)
		{
			vec *= scalar;
			return vec;
		}

		friend Derived operator/(Derived lhs, const Derived& rhs)
		{
			lhs /= rhs;
			return lhs;
		}

		friend Derived operator/(Derived vec, T scalar)
		{
			vec /= scalar;
			return vec;
		}

		friend Derived operator/(T scalar, Derived vec)
		{
			vec /= scalar;
			return vec;
		}
	};

	template <typename T>
	struct BaseVector2 : public BaseVectorT<BaseVector2<T>, T, 2>
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

		constexpr BaseVector2() : x(T{}), y(T{}) {}
		constexpr BaseVector2(T _x, T _y) : x(_x), y(_y) {}
		constexpr BaseVector2(T _scalar) : x(_scalar), y(_scalar) {}
	};
	TEST_VEC_CLASS(BaseVector2)

	template <typename T>
	struct BaseVector3 : public BaseVectorT<BaseVector3<T>, T, 3>
	{
		static constexpr size_t N = 3;
		union
		{
			T data[N]{ (T)0 };
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		constexpr BaseVector3() : x(T{}), y(T{}), z(T{}) {}
		constexpr BaseVector3(T _scalar) : x(_scalar), y(_scalar), z(_scalar) {}
		constexpr BaseVector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	};
	TEST_VEC_CLASS(BaseVector3)

	template <typename T>
	struct BaseVector4 : public BaseVectorT<BaseVector4<T>, T, 4>
	{
		static constexpr size_t N = 4;
		union
		{
			T data[N]{ (T)0 };
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			struct { T min1, min2, max1, max2; };
		};

		constexpr BaseVector4() : x(T{}), y(T{}), z(T{}), w(T{}) {}
		constexpr BaseVector4(T _scalar) : x(_scalar), y(_scalar), z(_scalar), w(_scalar) {}
		constexpr BaseVector4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
	};
	TEST_VEC_CLASS(BaseVector4)

	template <typename T, size_t N>
	struct BaseVector : public BaseVectorT<BaseVector<T, N>, T, N>
	{
		T data[N]{ (T)0 };

		constexpr BaseVector() : data{} {}
		constexpr BaseVector(T _scalar) : data{}
		{
			for (size_t i = 0; i < N; ++i)
			{
				data[i] = _scalar;
			}
		}
	};

	using int2 = BaseVector2<int>;
	using int3 = BaseVector3<int>;
	using int4 = BaseVector4<int>;
	using float2 = BaseVector2<float>;
	using float3 = BaseVector3<float>;
	using float4 = BaseVector4<float>;

	namespace color
	{
		static constexpr float ALPHA_TRANSPARENT = 0.f;
		static constexpr float ALPHA_OPAQUE = 1.f;

		static inline float4 rgb(float r, float g, float b) { return float4(r, g, b, 1.f); }
		static inline float4 rgba(float r, float g, float b, float a) { return float4(r, g, b, a); }
		static inline float4 opaque(float3 rgb) { return float4(rgb.r, rgb.g, rgb.b, ALPHA_OPAQUE); }
		static inline float4 opaque(float4 rgba) { return float4(rgba.r, rgba.g, rgba.b, ALPHA_OPAQUE); }
		static inline float4 transparent(float3 rgb) { return float4(rgb.r, rgb.g, rgb.b, ALPHA_TRANSPARENT); }
		static inline float4 transparent(float4 rgba) { return float4(rgba.r, rgba.g, rgba.b, ALPHA_TRANSPARENT); }

		static inline float4 clear  = rgba(0.f, 0.f, 0.f, ALPHA_TRANSPARENT);
		static inline float4 white  = rgba(1.f, 1.f, 1.f, ALPHA_OPAQUE);
		static inline float4 black  = rgba(0.f, 0.f, 0.f, ALPHA_OPAQUE);
		static inline float4 red    = rgb(1.f, 0.f, 0.f);
		static inline float4 green  = rgb(0.f, 1.f, 0.f);
		static inline float4 blue   = rgb(0.f, 0.f, 1.f);
		static inline float4 cyan   = rgb(0.f, 1.f, 1.f);
		static inline float4 yellow = rgb(1.f, 1.f, 0.f);
	};
}

#ifdef TEST_VEC_CLASS
#undef TEST_VEC_CLASS
#endif

#ifdef TEST_VEC_TRAITS
#undef TEST_VEC_TRAITS
#endif
