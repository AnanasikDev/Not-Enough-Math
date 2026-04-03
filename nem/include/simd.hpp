#include <immintrin.h>
#include <string>
#include <sstream>
#include <array>

namespace nem
{
	struct alignas(32) float4_simd
	{
		__m128 data;

		using buffer_t = std::array<float, 4>;

		float4_simd() : data(_mm_setzero_ps()) {}
		float4_simd(float s1, float s2, float s3, float s4) : data(_mm_setr_ps(s1, s2, s3, s4)) {}
		float4_simd(float scalar) : data(_mm_set_ps1(scalar)) {}
		float4_simd(const float* const buffer) : data(_mm_loadu_ps(buffer)) {}
		float4_simd(__m128 intr) : data(intr) {}
		constexpr operator __m128() const { return data; }

		std::string Serialize() const
		{
			buffer_t buf = Store();
			std::stringstream ss;
			ss << "(";
			ss << buf[0]; ss << ", ";
			ss << buf[1]; ss << ", ";
			ss << buf[2]; ss << ", ";
			ss << buf[3];
			ss << ")";
			return ss.str();
		}

		static inline float4_simd HorizontalSum(const float4_simd& lh, const float4_simd& rh) { return float4_simd(_mm_hadd_ps(lh, rh)); }
		inline float Sum() { float4_simd hsum = HorizontalSum(data, data); return HorizontalSum(hsum, hsum)[0]; }

		static inline float4_simd Broadcast(float scalar) { return float4_simd(scalar); }
		static inline float4_simd Add(const float4_simd& lh, const float4_simd& rh) { return float4_simd(_mm_add_ps(lh, rh)); }
		static inline float4_simd Subtract(const float4_simd& lh, const float4_simd& rh) { return float4_simd(_mm_sub_ps(lh, rh)); }
		static inline float4_simd Multiply(const float4_simd& lh, const float4_simd& rh) { return float4_simd(_mm_mul_ps(lh, rh)); }
		static inline float4_simd Multiply(const float4_simd& lh, float rh) { return float4_simd(_mm_mul_ps(lh, float4_simd(rh))); }
		static inline float4_simd Divide(const float4_simd& lh, const float4_simd& rh) { return float4_simd(_mm_div_ps(lh, rh)); }
		static inline float4_simd Divide(const float4_simd& lh, float rh) { return float4_simd(_mm_div_ps(lh, float4_simd(rh))); }
		static inline float4_simd Square(const float4_simd& vec) { return Multiply(vec, vec); }
		static inline float4_simd MultiplyAndAdd(const float4_simd& av, const float4_simd& bv, const float4_simd& cv) { return float4_simd(_mm_fmadd_ps(av, bv, cv)); }
		static inline float4_simd Max(const float4_simd& lh, const float4_simd& rh) { return float4_simd(_mm_max_ps(lh, rh)); }

		inline std::array<float, 4> Store() const
		{
			alignas(32) std::array<float, 4> result{ 0 };
			_mm_store_ps(result.data(), data);
			return result;
		}

		inline void Store(float* const out) const
		{
			_mm_store_ps(out, data);
		}

		float operator[](size_t i) const
		{
			alignas(32) float tmp[4];
			Store(tmp);
			return tmp[i];
		}

		float4_simd& operator+=(const float4_simd& other)
		{
			*this = Add(*this, other);
			return *this;
		}

		float4_simd& operator-=(const float4_simd& other)
		{
			*this = Subtract(*this, other);
			return *this;
		}

		float4_simd& operator*=(const float4_simd& other)
		{
			*this = Multiply(*this, other);
			return *this;
		}

		float4_simd& operator*=(float scalar)
		{
			*this = Multiply(*this, scalar);
			return *this;
		}

		float4_simd& operator/=(const float4_simd& other)
		{
			*this = Divide(*this, other);
			return *this;
		}

		float4_simd& operator/=(float scalar)
		{
			*this = Divide(*this, scalar);
			return *this;
		}

		friend float4_simd operator+(float4_simd lh, const float4_simd& rh)
		{
			lh += rh;
			return lh;
		}

		friend float4_simd operator-(float4_simd lh, const float4_simd& rh)
		{
			lh -= rh;
			return lh;
		}

		friend float4_simd operator*(float4_simd lh, const float4_simd& rh)
		{
			lh *= rh;
			return lh;
		}

		friend float4_simd operator*(float4_simd lh, float scalar)
		{
			lh *= scalar;
			return lh;
		}

		friend float4_simd operator/(float4_simd lh, const float4_simd& rh)
		{
			lh /= rh;
			return lh;
		}

		friend float4_simd operator/(float4_simd lh, float scalar)
		{
			lh /= scalar;
			return lh;
		}
	};

	struct alignas(32) float8_simd
	{
		__m256 data;
		using buffer_t = std::array<float, 8>;

		float8_simd() : data(_mm256_setzero_ps()) {}
		float8_simd(float s1, float s2, float s3, float s4, float s5, float s6, float s7, float s8) : data(_mm256_setr_ps(s1, s2, s3, s4, s5, s6, s7, s8)) {}
		float8_simd(float scalar) : data(_mm256_set1_ps(scalar)) {}
		float8_simd(const float* const buffer) : data(_mm256_loadu_ps(buffer)) {}
		float8_simd(__m256 intr) : data(intr) {}
		constexpr operator __m256() const { return data; }

		std::string Serialize() const
		{
			std::stringstream ss;
			buffer_t buf = Store();
			ss << "(";
			ss << buf[0]; ss << ", ";
			ss << buf[1]; ss << ", ";
			ss << buf[2]; ss << ", ";
			ss << buf[3]; ss << ", ";
			ss << buf[4]; ss << ", ";
			ss << buf[5]; ss << ", ";
			ss << buf[6]; ss << ", ";
			ss << buf[7];
			ss << ")";
			return ss.str();
		}

		static inline float8_simd Broadcast(float scalar) { return float8_simd(scalar); }
		static inline float8_simd Add(const float8_simd& lh, const float8_simd& rh) { return float8_simd(_mm256_add_ps(lh, rh)); }
		static inline float8_simd Subtract(const float8_simd& lh, const float8_simd& rh) { return float8_simd(_mm256_sub_ps(lh, rh)); }
		static inline float8_simd Multiply(const float8_simd& lh, const float8_simd& rh) { return float8_simd(_mm256_mul_ps(lh, rh)); }
		static inline float8_simd Multiply(const float8_simd& lh, float rh) { return float8_simd(_mm256_mul_ps(lh, float8_simd(rh))); }
		static inline float8_simd Divide(const float8_simd& lh, const float8_simd& rh) { return float8_simd(_mm256_div_ps(lh, rh)); }
		static inline float8_simd Divide(const float8_simd& lh, float rh) { return float8_simd(_mm256_div_ps(lh, float8_simd(rh))); }
		static inline float8_simd Square(const float8_simd& vec) { return Multiply(vec, vec); }
		static inline float8_simd MultiplyAndAdd(const float8_simd& av, const float8_simd& bv, const float8_simd& cv) { return float8_simd(_mm256_fmadd_ps(av, bv, cv)); }
		static inline float8_simd Max(const float8_simd& lh, const float8_simd& rh) { return float8_simd(_mm256_max_ps(lh, rh)); }
		inline float4_simd TakeLower() const { return _mm256_castps256_ps128(data); }
		inline float4_simd TakeHigher() const { return _mm256_extractf128_ps(data, 1); }
		static inline float8_simd HorizontalSum(const float8_simd& lh, const float8_simd& rh) { return float8_simd(_mm256_hadd_ps(lh, rh)); }
		float Sum() const
		{
			float4_simd result = TakeLower() + TakeHigher();
			return result.Sum();
		}

		inline buffer_t Store() const
		{
			alignas(32) buffer_t result { 0 };
			_mm256_store_ps(result.data(), data);
			return result;
		}

		inline void Store(float* const out) const
		{
			_mm256_store_ps(out, data);
		}

		float operator[](size_t i) const
		{
			alignas(32) float tmp[8];
			Store(tmp);
			return tmp[i];
		}

		float8_simd& operator+=(const float8_simd& other)
		{
			*this = Add(*this, other);
			return *this;
		}

		float8_simd& operator-=(const float8_simd& other)
		{
			*this = Subtract(*this, other);
			return *this;
		}

		float8_simd& operator*=(const float8_simd& other)
		{
			*this = Multiply(*this, other);
			return *this;
		}

		float8_simd& operator*=(float scalar)
		{
			*this = Multiply(*this, scalar);
			return *this;
		}

		float8_simd& operator/=(const float8_simd& other)
		{
			*this = Divide(*this, other);
			return *this;
		}

		float8_simd& operator/=(float scalar)
		{
			*this = Divide(*this, scalar);
			return *this;
		}

		friend float8_simd operator+(float8_simd lh, const float8_simd& rh)
		{
			lh += rh;
			return lh;
		}

		friend float8_simd operator-(float8_simd lh, const float8_simd& rh)
		{
			lh -= rh;
			return lh;
		}

		friend float8_simd operator*(float8_simd lh, const float8_simd& rh)
		{
			lh *= rh;
			return lh;
		}

		friend float8_simd operator*(float8_simd lh, float scalar)
		{
			lh *= scalar;
			return lh;
		}

		friend float8_simd operator/(float8_simd lh, const float8_simd& rh)
		{
			lh /= rh;
			return lh;
		}

		friend float8_simd operator/(float8_simd lh, float scalar)
		{
			lh /= scalar;
			return lh;
		}
	};

}
