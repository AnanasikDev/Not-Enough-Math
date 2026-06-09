#pragma once

#include "utils.hpp"
#include "err.hpp"

#include <type_traits>
#include <cstddef>
#include <limits>

#define TEST_VEC_TRAITS(VecType) \
    static_assert(sizeof(VecType) == sizeof(VecType::item_type) * VecType::items_count, \
        #VecType " size mismatch! Possible unexpected padding."); \
    static_assert(std::is_standard_layout_v<VecType>, \
        #VecType " is not Standard Layout. This breaks C-compatibility/offsetof."); \
    \
    static_assert(std::is_trivially_copyable_v<VecType>, \
        #VecType " is not trivially copyable. This hurts pass-by-value performance."); \
    static_assert(std::is_trivially_destructible_v<VecType>, \
        #VecType " has a non-trivial destructor. This prevents it from being in a union."); \
    \
    static_assert(alignof(VecType) >= alignof(VecType::item_type), \
        #VecType " alignment is weaker than its scalar component."); \
    \
    static_assert(std::is_default_constructible_v<VecType>, \
        #VecType " should be default constructible for array allocations."); \
    static_assert(std::is_trivially_copy_constructible_v<VecType>, \
        #VecType " copy constructor is not trivial."); \
    static_assert(std::is_trivially_move_constructible_v<VecType>, \
        #VecType " move constructor is not trivial (math types should be POD-like).");

namespace nem
{
	template<typename _T, size_t _N>
	struct storage
    {
		using item_type = _T;
		static constexpr size_t items_count = _N; 
        
		item_type data[items_count];
    };

	template<typename _T>
	struct storage<_T, 2>
    {
		using item_type = _T;
		static constexpr size_t items_count = 2; 
        
        union
        {
			item_type data[items_count]{ item_type{ 0 } };
			struct { item_type x, y; };
			struct { item_type u, v; };
			struct { item_type s, t; };
			struct { item_type min, max; };
			struct { item_type width, height; };
		};
    };

    template<typename _T>
	struct storage<_T, 3>
    {
		using item_type = _T;
		static constexpr size_t items_count = 3; 	
        
        union
        {
			item_type data[items_count]{ item_type{ 0 } };
			struct { item_type x, y, z; };
			struct { item_type r, g, b; };
		};
    };

    template<typename _T>
	struct storage<_T, 4>
    {
		using item_type = _T;
		static constexpr size_t items_count = 4; 	
        
        union
        {
			item_type data[items_count]{ item_type{ 0 } };
			struct { item_type x, y, z, w; };
			struct { item_type r, g, b, a; };
			struct { item_type min1, min2, max1, max2; };
		};
    };

    template <typename _T, size_t _N>
    requires (_N > 1)
	struct vec : storage<_T, _N>
	{
		using item_type = _T;
		static constexpr size_t items_count = _N;

        vec() = default;
		vec(item_type scalar)
		{
			for (int i = 0; i < items_count; ++i)
			{
				this->data[i] = scalar;
			}
		}

		template <typename... Args>
		requires (sizeof...(Args) == items_count) && ((std::is_same_v<Args, item_type> || nem::is_subset_of_v<Args, item_type>) && ...)
		vec(Args... args)
		{
			int i = 0;
			((this->data[i++] = args), ...);
        }

        constexpr item_type& operator[](size_t index) { return this->data[index]; }
		constexpr const item_type& operator[](size_t index) const { return this->data[index]; }

        static constexpr vec NaN() { return vec(std::numeric_limits<item_type>::quiet_NaN()); }

		vec& operator+=(const vec& rhs)
		{
			for (size_t i = 0; i < items_count; ++i)
			{
				(*this)[i] += rhs[i];
			}
			return *this;
		}

		vec& operator-=(const vec& rhs)
		{
			for (size_t i = 0; i < items_count; ++i)
			{
				(*this)[i] -= rhs[i];
			}
			return *this;
		}

		vec& operator*=(const vec& rhs)
		{
			for (size_t i = 0; i < items_count; ++i)
			{
				(*this)[i] *= rhs[i];
			}
			return *this;
		}

		vec& operator*=(item_type scalar)
		{
			for (size_t i = 0; i < items_count; ++i)
			{
				(*this)[i] *= scalar;
			}
			return *this;
		}

		vec& operator/=(const vec& rhs)
		{
			for (size_t i = 0; i < items_count; ++i)
			{
				(*this)[i] /= rhs[i];
			}
			return *this;
		}

		vec& operator/=(item_type scalar)
		{
			if constexpr (std::is_floating_point_v<item_type>)
            {
                const item_type fac = (item_type)1.0 / scalar;
				for (size_t i = 0; i < items_count; ++i)
				{
					(*this)[i] *= fac;
				}
            }
            else
            {
				for (size_t i = 0; i < items_count; ++i)
				{
					(*this)[i] /= scalar;
				}
			}
			return *this;
		}

		friend vec operator+(vec lhs, const vec& rhs)
		{
			lhs += rhs;
			return lhs;
		}

		friend vec operator-(vec lhs, const vec& rhs)
		{
			lhs -= rhs;
			return lhs;
		}

		friend vec operator*(vec lhs, const vec& rhs)
		{
			lhs *= rhs;
			return lhs;
		}

		friend vec operator*(vec vec, item_type scalar)
		{
			vec *= scalar;
			return vec;
		}

		friend vec operator*(item_type scalar, vec vec)
		{
			vec *= scalar;
			return vec;
		}

		friend vec operator/(vec lhs, const vec& rhs)
		{
			lhs /= rhs;
			return lhs;
		}

		friend vec operator/(vec vec, item_type scalar)
		{
			vec /= scalar;
			return vec;
		}

		friend vec operator/(item_type scalar, vec vec)
		{
			for (size_t i = 0; i < items_count; ++i)
            {
                // TODO: zero division safety
				vec[i] = scalar / vec[i];
			}
			return vec;
        }

        // unary minus
        friend vec operator-(vec value)
        {
            for (size_t i = 0; i < items_count; ++i)
            {
				value[i] = -value[i];
			}
			return value;
        }

        // unary plus
        friend vec operator+(vec value)
        {
            for (size_t i = 0; i < items_count; ++i)
            {
				value[i] = +value[i];
			}
			return value;
		}
    };
    
	using int2    = nem::vec<int   , 2>;
	using int3    = nem::vec<int   , 3>;
	using int4    = nem::vec<int   , 4>;
	using float2  = nem::vec<float , 2>;
	using float3  = nem::vec<float , 3>;
    using float4  = nem::vec<float , 4>;
    using double2 = nem::vec<double, 2>;
	using double3 = nem::vec<double, 3>;
    using double4 = nem::vec<double, 4>;
    
	TEST_VEC_TRAITS(int2);
	TEST_VEC_TRAITS(int3);
	TEST_VEC_TRAITS(int4);
	TEST_VEC_TRAITS(float2);
	TEST_VEC_TRAITS(float3);
    TEST_VEC_TRAITS(float4);
    TEST_VEC_TRAITS(double2);
	TEST_VEC_TRAITS(double3);
	TEST_VEC_TRAITS(double4);

	namespace color
	{
		static constexpr float ALPHA_TRANSPARENT = 0.f;
		static constexpr float ALPHA_OPAQUE = 1.f;

		static NEM_INLINE float4 rgb(float r, float g, float b) { return float4(r, g, b, ALPHA_OPAQUE); }
		static NEM_INLINE float4 rgba(float r, float g, float b, float a) { return float4(r, g, b, a); }
		static NEM_INLINE float4 opaque(float3 rgb) { return float4(rgb.r, rgb.g, rgb.b, ALPHA_OPAQUE); }
		static NEM_INLINE float4 opaque(float4 rgba) { return float4(rgba.r, rgba.g, rgba.b, ALPHA_OPAQUE); }
		static NEM_INLINE float4 transparent(float3 rgb) { return float4(rgb.r, rgb.g, rgb.b, ALPHA_TRANSPARENT); }
		static NEM_INLINE float4 transparent(float4 rgba) { return float4(rgba.r, rgba.g, rgba.b, ALPHA_TRANSPARENT); }

		static NEM_INLINE float4 clear  = rgba(0.f, 0.f, 0.f, ALPHA_TRANSPARENT);
		static NEM_INLINE float4 white  = rgb(1.f, 1.f, 1.f);
		static NEM_INLINE float4 black  = rgb(0.f, 0.f, 0.f);
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
