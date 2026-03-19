#pragma once

#include "utils.hpp"

namespace nem
{
	template<typename Derived, typename T, size_t N>
	struct BaseVector
	{
		constexpr Derived& ImplRW() { return (Derived&)*this; }
		constexpr const Derived& ImplR() const { return (const Derived&)*this; }

		Derived operator+(const Derived& other)
		{
			Derived result;
			for (size_t i = 0; i < N; i++)
			{
				result[i] = CompR(i) + other.CompR(i);
			}
			return result;
		}

		Derived operator-(const Derived& other)
		{
			Derived result;
			for (size_t i = 0; i < N; i++)
			{
				result[i] = CompR(i) - other.CompR(i);
			}
			return result;
		}

		Derived operator*(T scalar)
		{
			Derived result{};
			for (size_t i = 0; i < N; i++)
			{
				result[i] = CompR(i) * scalar;
			}
			return result;
		}

		Derived operator*(Derived other)
		{
			Derived result{};
			for (size_t i = 0; i < N; i++)
			{
				result[i] = CompR(i) * other.CompR(i);
			}
			return result;
		}

		Derived& operator*=(const Derived& other)
		{
			for (size_t i = 0; i < N; i++)
			{
				ImplRW()[i] *= other.CompR(i);
			}
			return ImplRW();
		}

		Derived operator/(T scalar)
		{
			Derived result{};
			for (size_t i = 0; i < N; i++)
			{
				result[i] = CompR(i) / scalar;
			}
			return result;
		}

		Derived operator/(Derived other)
		{
			Derived result{};
			for (size_t i = 0; i < N; i++)
			{
				result[i] = CompR(i) / other.CompR(i);
			}
			return result;
		}

		inline constexpr T& CompRW(size_t index)
		{
			return ImplRW().data[index];
		}

		inline constexpr const T& CompR(size_t index) const
		{
			return ImplR().data[index];
		}

		const T& operator[](size_t index) const
		{
			return CompR(index);
		}

		T& operator[](size_t index)
		{
			return CompRW(index);
		}

		Derived Lerped(const Derived& b, float t)
		{
			Derived result;
			for (size_t i = 0; i < N; i++)
			{
				result.CompRW(i) = (T)nem::lerp(CompR(i), b.CompR(i), (T)t);
			}
			return result;
		}

		static Derived Lerp(Derived a, const Derived& b, float t)
		{
			return a.Lerped(b, t);
		}

		T LengthSquared() const
		{
			T sum = T{};
			for (size_t i = 0; i < N; ++i)
				sum += CompR(i) * CompR(i);

			return sum;
		}

		T Length() const
		{
			return nem::sqrt(LengthSquared());
		}

		void Normalize()
		{
			T len = Length();
			if (len == T{}) return;

			for (size_t i = 0; i < N; ++i)
				CompRW(i) /= len;
		}
	};

	template <typename T>
	struct BaseVector2 : public BaseVector<BaseVector2<T>, T, 2>
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

		BaseVector2() : x(T{}), y(T{}) {}
		BaseVector2(T _x, T _y) : x(_x), y(_y) {}
		BaseVector2(T _scalar) : x(_scalar), y(_scalar) {}
	};

	template <typename T>
	struct BaseVector3 : public BaseVector<BaseVector3<T>, T, 3>
	{
		static constexpr size_t N = 3;
		union
		{
			T data[N]{ (T)0 };
			struct { T x, y, z; };
			struct { T r, g, b; };
		};

		BaseVector3() : x(T{}), y(T{}), z(T{}) {}
		BaseVector3(T _scalar) : x(_scalar), y(_scalar), z(_scalar) {}
		BaseVector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	};

	template <typename T>
	struct BaseVector4 : public BaseVector<BaseVector4<T>, T, 4>
	{
		static constexpr size_t N = 4;
		union
		{
			T data[N]{ (T)0 };
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			struct { T min1, min2, max1, max2; };
		};

		BaseVector4() : x(T{}), y(T{}), z(T{}), w(T{}) {}
		BaseVector4(T _scalar) : x(_scalar), y(_scalar), z(_scalar), w(_scalar) {}
		BaseVector4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
	};

	using int2 = BaseVector2<int>;
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

		static inline float4 clear = rgba(0.f, 0.f, 0.f, ALPHA_TRANSPARENT);
		static inline float4 white = rgba(1.f, 1.f, 1.f, ALPHA_OPAQUE);
		static inline float4 black = rgba(0.f, 0.f, 0.f, ALPHA_OPAQUE);
		static inline float4 red = rgb(1.f, 0.f, 0.f);
		static inline float4 green = rgb(0.f, 1.f, 0.f);
		static inline float4 blue = rgb(0.f, 0.f, 1.f);
		static inline float4 cyan = rgb(0.f, 1.f, 1.f);
		static inline float4 yellow = rgb(1.f, 1.f, 0.f);
	};
}
