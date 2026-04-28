#include "common.h"

#include <cmath>
#include <limits>

using namespace nem_tests;
using nem::float2;
using nem::float3;
using nem::float4;

// ===========================================================================
// Test helpers
// ===========================================================================

static constexpr float FNAN = std::numeric_limits<float>::quiet_NaN();
static constexpr float FMAX = std::numeric_limits<float>::max();

static bool IS_SAFE_INVALID(float scalar)
{
#ifdef NEM_ERR_USE_NAN
    return std::isnan(scalar);
#elif defined(NEM_ERR_SAFE_FALLBACK)
    return nem::is_nearly_zero(scalar);
#else
    return nem::is_nearly_zero(scalar);
#endif
}

template<typename Derived, typename T, size_t N>
static bool IS_SAFE_INVALID(const nem::BaseVectorT<Derived, T, N>& vec)
{
    static_assert(std::is_same_v<T, float>,
        "IS_SAFE_INVALID vector helper only supports floats");
    for (size_t i = 0; i < N; i++)
    {
        if (IS_SAFE_INVALID(vec[i])) return true;
    }
    return false;
}

static void require_valid_basis(float3 n, float3 b1, float3 b2)
{
    REQUIRE_THAT(nem::length(b1), WithinAbs(1.f, kEps));
    REQUIRE_THAT(nem::length(b2), WithinAbs(1.f, kEps));
    REQUIRE_THAT(nem::dot(n, b1), WithinAbs(0.f, kEps));
    REQUIRE_THAT(nem::dot(n, b2), WithinAbs(0.f, kEps));
    REQUIRE_THAT(nem::dot(b1, b2), WithinAbs(0.f, kEps));
}

// ===========================================================================
// sqrLength
// ===========================================================================

TEST_CASE("vector::sqrLength::zero vector yields zero", "[vec][sqrLength]")
{
    float3 input;

    float result = nem::sqrLength(input);

    REQUIRE_THAT(result, WithinAbs(0.f, kEps));
}

TEST_CASE("vector::sqrLength::negative components square positive", "[vec][sqrLength]")
{
    float3 input(-3.f, -4.f, 0.f);

    float result = nem::sqrLength(input);

    REQUIRE_THAT(result, WithinAbs(25.f, kEps));
}

TEST_CASE("vector::sqrLength::single axis x", "[vec][sqrLength]")
{
    float3 input(7.f, 0.f, 0.f);

    float result = nem::sqrLength(input);

    REQUIRE_THAT(result, WithinAbs(49.f, kEps));
}

TEST_CASE("vector::sqrLength::single axis z negative", "[vec][sqrLength]")
{
    float3 input(0.f, 0.f, -5.f);

    float result = nem::sqrLength(input);

    REQUIRE_THAT(result, WithinAbs(25.f, kEps));
}

TEST_CASE("vector::sqrLength::general three-component", "[vec][sqrLength]")
{
    float3 input(1.f, 2.f, 1.f);

    float result = nem::sqrLength(input);

    REQUIRE_THAT(result, WithinAbs(6.f, kEps));
}

TEST_CASE("vector::sqrLength::mixed sign three-component", "[vec][sqrLength]")
{
    float3 input(-1.f, 2.f, -1.f);

    float result = nem::sqrLength(input);

    REQUIRE_THAT(result, WithinAbs(6.f, kEps));
}

// ===========================================================================
// length
// ===========================================================================

TEST_CASE("vector::length::3-4-12-13 pythagorean quadruple", "[vec][length]")
{
    float3 input(3.f, 4.f, 12.f);

    float result = nem::length(input);

    REQUIRE_THAT(result, WithinAbs(13.f, kEps));
}

TEST_CASE("vector::length::float2 3-4-5 triangle", "[vec][length]")
{
    float2 input(3.f, 4.f);

    float result = nem::length(input);

    REQUIRE_THAT(result, WithinAbs(5.f, kEps));
}

TEST_CASE("vector::length::float4 single w component", "[vec][length]")
{
    float4 input(0.f, 0.f, 0.f, 1.f);

    float result = nem::length(input);

    REQUIRE_THAT(result, WithinAbs(1.f, kEps));
}


// ===========================================================================
// normalize
// ===========================================================================

TEST_CASE("vector::normalize::zero vector yields invalid result", "[vec][normalize]")
{
    float3 input;

    float3 result = nem::normalize(input);

    REQUIRE(IS_SAFE_INVALID(result));
}

TEST_CASE("vector::normalize::below epsilon threshold yields invalid result", "[vec][normalize]")
{
    float3 input(1e-7f, 0.f, 0.f);

    float3 result = nem::normalize(input);

    REQUIRE(IS_SAFE_INVALID(result));
}

TEST_CASE("vector::normalize::above epsilon threshold yields unit vector", "[vec][normalize]")
{
    float3 input(1e-3f, 0.f, 0.f);

    float3 result = nem::normalize(input);

    REQUIRE_THAT(result.x, WithinAbs(1.f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(0.f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(0.f, kEps));
}

TEST_CASE("vector::normalize::unit vector is idempotent", "[vec][normalize]")
{
    float3 input(1.f, 0.f, 0.f);

    float3 result = nem::normalize(input);

    REQUIRE_THAT(result.x, WithinAbs(1.f, kEps));
}

TEST_CASE("vector::normalize::double normalize is stable", "[vec][normalize]")
{
    float3 input(3.f, 4.f, 5.f);

    float3 first = nem::normalize(input);
    float3 second = nem::normalize(first);

    REQUIRE_THAT(first.x, WithinAbs(second.x, kEps));
    REQUIRE_THAT(first.y, WithinAbs(second.y, kEps));
    REQUIRE_THAT(first.z, WithinAbs(second.z, kEps));
}

TEST_CASE("vector::normalize::preserves negative direction", "[vec][normalize]")
{
    float3 input(-5.f, 0.f, 0.f);

    float3 result = nem::normalize(input);

    REQUIRE_THAT(result.x, WithinAbs(-1.f, kEps));
}

// ===========================================================================
// is_nearly_zero (vector)
// ===========================================================================

TEST_CASE("vector::is_nearly_zero::just below threshold passes", "[vec][is_nearly_zero]")
{
    float3 input(9.9e-7f, -9.9e-7f, 0.f);

    bool result = nem::is_nearly_zero(input);

    REQUIRE(result);
}

TEST_CASE("vector::is_nearly_zero::at threshold fails (strict less-than)", "[vec][is_nearly_zero]")
{
    float3 input(1e-6f, 0.f, 0.f);

    bool result = nem::is_nearly_zero(input);

    REQUIRE_FALSE(result);
}

TEST_CASE("vector::is_nearly_zero::just above threshold fails", "[vec][is_nearly_zero]")
{
    float3 input(1.1e-6f, 0.f, 0.f);

    bool result = nem::is_nearly_zero(input);

    REQUIRE_FALSE(result);
}

TEST_CASE("vector::is_nearly_zero::NaN is not near zero", "[vec][is_nearly_zero]")
{
    float3 input(FNAN, 0.f, 0.f);

    bool result = nem::is_nearly_zero(input);

    REQUIRE_FALSE(result);
}

TEST_CASE("vector::is_nearly_zero::negative zero passes", "[vec][is_nearly_zero]")
{
    float3 input(-0.f, -0.f, -0.f);

    bool result = nem::is_nearly_zero(input);

    REQUIRE(result);
}

// ===========================================================================
// orthogonal_3d_basis
// ===========================================================================

TEST_CASE("vector::orthogonal_3d_basis::zero vector rejected", "[vec][basis]")
{
    float3 b1, b2;

    bool result = nem::orthogonal_3d_basis(float3(), b1, b2);

    REQUIRE_FALSE(result);
}

TEST_CASE("vector::orthogonal_3d_basis::near-zero vector rejected", "[vec][basis]")
{
    float3 input(1e-7f, 0.f, 0.f);
    float3 b1, b2;

    bool result = nem::orthogonal_3d_basis(input, b1, b2);

    REQUIRE_FALSE(result);
}

TEST_CASE("vector::orthogonal_3d_basis::positive x axis", "[vec][basis]")
{
    float3 n(1.f, 0.f, 0.f);
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    REQUIRE(ok);
    require_valid_basis(n, b1, b2);
}

TEST_CASE("vector::orthogonal_3d_basis::negative x axis", "[vec][basis]")
{
    float3 n(-1.f, 0.f, 0.f);
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    REQUIRE(ok);
    require_valid_basis(n, b1, b2);
}

TEST_CASE("vector::orthogonal_3d_basis::positive y axis", "[vec][basis]")
{
    float3 n(0.f, 1.f, 0.f);
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    REQUIRE(ok);
    require_valid_basis(n, b1, b2);
}

TEST_CASE("vector::orthogonal_3d_basis::negative y axis", "[vec][basis]")
{
    float3 n(0.f, -1.f, 0.f);
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    REQUIRE(ok);
    require_valid_basis(n, b1, b2);
}

TEST_CASE("vector::orthogonal_3d_basis::positive z axis", "[vec][basis]")
{
    float3 n(0.f, 0.f, 1.f);
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    REQUIRE(ok);
    require_valid_basis(n, b1, b2);
}

TEST_CASE("vector::orthogonal_3d_basis::negative z axis", "[vec][basis]")
{
    float3 n(0.f, 0.f, -1.f);
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    REQUIRE(ok);
    require_valid_basis(n, b1, b2);
}

TEST_CASE("vector::orthogonal_3d_basis::z component below branch threshold", "[vec][basis]")
{
    float3 n = nem::normalize(float3(0.063f, 0.f, 0.998f));
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    REQUIRE(ok);
    require_valid_basis(n, b1, b2);
}

TEST_CASE("vector::orthogonal_3d_basis::z component above branch threshold", "[vec][basis]")
{
    float3 n = nem::normalize(float3(0.001f, 0.f, 0.9999f));
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    REQUIRE(ok);
    require_valid_basis(n, b1, b2);
}

TEST_CASE("vector::orthogonal_3d_basis::negative z above branch threshold", "[vec][basis]")
{
    float3 n = nem::normalize(float3(0.001f, 0.f, -0.9999f));
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    REQUIRE(ok);
    require_valid_basis(n, b1, b2);
}

// ===========================================================================
// horizontal_sum
// ===========================================================================

TEST_CASE("vector::horizontal_sum::zero vector yields zero", "[vec][horizontal_sum]")
{
    float3 input;

    float result = nem::horizontal_sum(input);

    REQUIRE_THAT(result, WithinAbs(0.f, kEps));
}

TEST_CASE("vector::horizontal_sum::float4 general case", "[vec][horizontal_sum]")
{
    float4 input(1.f, 2.f, 3.f, 4.f);

    float result = nem::horizontal_sum(input);

    REQUIRE_THAT(result, WithinAbs(10.f, kEps));
}

// ===========================================================================
// horizontal_mul
// ===========================================================================

TEST_CASE("vector::horizontal_mul::one zero component yields zero", "[vec][horizontal_mul]")
{
    float3 input(1.f, 2.f, 0.f);

    float result = nem::horizontal_mul(input);

    REQUIRE_THAT(result, WithinAbs(0.f, kEps));
}

TEST_CASE("vector::horizontal_mul::middle zero component yields zero", "[vec][horizontal_mul]")
{
    float3 input(5.f, 0.f, 5.f);

    float result = nem::horizontal_mul(input);

    REQUIRE_THAT(result, WithinAbs(0.f, kEps));
}

TEST_CASE("vector::horizontal_mul::all ones yields one", "[vec][horizontal_mul]")
{
    float4 input(1.f, 1.f, 1.f, 1.f);

    float result = nem::horizontal_mul(input);

    REQUIRE_THAT(result, WithinAbs(1.f, kEps));
}

// ===========================================================================
// dot
// ===========================================================================

TEST_CASE("vector::dot::self equals sqrLength", "[vec][dot]")
{
    float3 v(-7.f, 11.f, -13.f);

    float result = nem::dot(v, v);

    REQUIRE_THAT(result, WithinAbs(nem::sqrLength(v), kEps));
}

TEST_CASE("vector::dot::with zero vector yields zero", "[vec][dot]")
{
    float3 a(FMAX, FMAX, FMAX);
    float3 b;

    float result = nem::dot(a, b);

    REQUIRE_THAT(result, WithinAbs(0.f, kEps));
}

TEST_CASE("vector::dot::commutativity holds", "[vec][dot]")
{
    float3 a(1.5f, -2.7f, 3.9f);
    float3 b(-4.1f, 5.3f, -6.5f);

    float ab = nem::dot(a, b);
    float ba = nem::dot(b, a);

    REQUIRE_THAT(ab, WithinAbs(ba, kEps));
}

TEST_CASE("vector::dot::orthogonal float2 yields zero", "[vec][dot]")
{
    float2 a(0.f, 1.f);
    float2 b(1.f, 0.f);

    float result = nem::dot(a, b);

    REQUIRE_THAT(result, WithinAbs(0.f, kEps));
}

TEST_CASE("vector::dot::anti-parallel float2 yields negative one", "[vec][dot]")
{
    float2 a(0.f, 1.f);
    float2 b(0.f, -1.f);

    float result = nem::dot(a, b);

    REQUIRE_THAT(result, WithinAbs(-1.f, kEps));
}

TEST_CASE("vector::dot::parallel float2 yields one", "[vec][dot]")
{
    float2 a(0.f, 1.f);
    float2 b(0.f, 1.f);

    float result = nem::dot(a, b);

    REQUIRE_THAT(result, WithinAbs(1.f, kEps));
}

// ===========================================================================
// cross
// ===========================================================================

TEST_CASE("vector::cross::with zero vector yields zero", "[vec][cross]")
{
    float3 a(1.f, 2.f, 3.f);
    float3 b;

    float3 result = nem::cross(a, b);

    REQUIRE_THAT(result.x, WithinAbs(0.f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(0.f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(0.f, kEps));
}

TEST_CASE("vector::cross::both zero yields zero", "[vec][cross]")
{
    float3 a;
    float3 b;

    float3 result = nem::cross(a, b);

    REQUIRE_THAT(nem::length(result), WithinAbs(0.f, kEps));
}

TEST_CASE("vector::cross::nearly parallel vectors yield near-zero magnitude", "[vec][cross]")
{
    float3 a(1.f, 0.f, 0.f);
    float3 b(1.f, 1e-7f, 0.f);

    float3 result = nem::cross(a, b);

    REQUIRE(nem::length(result) < 1e-6f);
}

TEST_CASE("vector::cross::result is perpendicular to both inputs", "[vec][cross]")
{
    float3 a(2.f, -3.f, 7.f);
    float3 b(-1.f, 4.f, 5.f);

    float3 result = nem::cross(a, b);

    REQUIRE_THAT(nem::dot(result, a), WithinAbs(0.f, kEps));
    REQUIRE_THAT(nem::dot(result, b), WithinAbs(0.f, kEps));
}

TEST_CASE("vector::cross::perpendicular inputs have magnitude |a||b|", "[vec][cross]")
{
    float3 a(3.f, 0.f, 0.f);
    float3 b(0.f, 5.f, 0.f);

    float3 result = nem::cross(a, b);
    float expected = nem::length(a) * nem::length(b);
    float actual = nem::length(result);

    REQUIRE_THAT(actual, WithinAbs(expected, kEps));
}

// ===========================================================================
// compound assignment
// ===========================================================================

TEST_CASE("vector::compound_assign::operator += returns reference to self", "[vec][arithmetic]")
{
    float3 a(1.f, 2.f, 3.f);
    float3 b(10.f, 20.f, 30.f);

    float3& ref = (a += b);

    REQUIRE(&ref == &a);
    REQUIRE_THAT(a.x, WithinAbs(11.f, kEps));
}

TEST_CASE("vector::compound_assign::operator -= self yields zero", "[vec][arithmetic]")
{
    float3 a(FMAX, -FMAX, 42.f);

    a -= a;

    REQUIRE(a.x == 0.f);
    REQUIRE(a.y == 0.f);
    REQUIRE(a.z == 0.f);
}

TEST_CASE("vector::compound_assign::operator /= self yields ones", "[vec][arithmetic]")
{
    float3 a(7.f, -3.f, 0.5f);

    a /= a;

    REQUIRE_THAT(a.x, WithinAbs(1.f, kEps));
    REQUIRE_THAT(a.y, WithinAbs(1.f, kEps));
    REQUIRE_THAT(a.z, WithinAbs(1.f, kEps));
}

TEST_CASE("vector::compound_assign::operator *= returns reference to self", "[vec][arithmetic]")
{
    float3 a(1.f, 2.f, 3.f);
    float3 b(2.f);

    float3& ref = (a *= b);

    REQUIRE(&ref == &a);
}

// ===========================================================================
// round-trip chains
// ===========================================================================

TEST_CASE("vector::chain::add then subtract recovers original", "[vec][chain]")
{
    float3 a(1.23456f, -7.89012f, 3.45678f);
    float3 b(9.87654f, 3.21098f, -6.54321f);

    float3 result = (a + b) - b;

    REQUIRE_THAT(result.x, WithinAbs(a.x, kEps));
    REQUIRE_THAT(result.y, WithinAbs(a.y, kEps));
    REQUIRE_THAT(result.z, WithinAbs(a.z, kEps));
}

TEST_CASE("vector::chain::multiply then divide recovers original", "[vec][chain]")
{
    float3 a(2.f, 3.f, 4.f);
    float3 b(5.f, 7.f, 11.f);

    float3 result = (a * b) / b;

    REQUIRE_THAT(result.x, WithinAbs(a.x, kEps));
    REQUIRE_THAT(result.y, WithinAbs(a.y, kEps));
    REQUIRE_THAT(result.z, WithinAbs(a.z, kEps));
}

TEST_CASE("vector::chain::dot of normalized with itself yields one", "[vec][chain]")
{
    float3 v(100.f, -200.f, 300.f);

    float3 n = nem::normalize(v);
    float result = nem::dot(n, n);

    REQUIRE_THAT(result, WithinAbs(1.f, kEps));
}

// ===========================================================================
// scalar broadcast
// ===========================================================================

TEST_CASE("vector::scalar_broadcast::multiplication scales all components", "[vec][arithmetic]")
{
    float3 v(2.f, 3.f, 4.f);

    float3 result = v * float3(5.f);

    REQUIRE_THAT(result.x, WithinAbs(10.f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(15.f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(20.f, kEps));
}

TEST_CASE("vector::scalar_broadcast::division scales all components", "[vec][arithmetic]")
{
    float3 v(2.f, 3.f, 4.f);

    float3 result = v / float3(2.f);

    REQUIRE_THAT(result.x, WithinAbs(1.f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(1.5f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(2.f, kEps));
}