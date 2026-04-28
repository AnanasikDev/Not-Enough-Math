#include "common.h"

using namespace nem_tests;

// ===========================================================================
// clamp
// ===========================================================================

TEST_CASE("scalar::clamp::in-range value is unchanged", "[scalar][clamp]")
{
    int value = 5;

    int result = nem::clamp(value, 0, 10);

    REQUIRE(result == 5);
}

TEST_CASE("scalar::clamp::value below min becomes min", "[scalar][clamp]")
{
    int value = -1;

    int result = nem::clamp(value, 0, 10);

    REQUIRE(result == 0);
}

TEST_CASE("scalar::clamp::value above max becomes max", "[scalar][clamp]")
{
    int value = 11;

    int result = nem::clamp(value, 0, 10);

    REQUIRE(result == 10);
}

TEST_CASE("scalar::clamp::value at lower boundary is unchanged", "[scalar][clamp]")
{
    int value = 0;

    int result = nem::clamp(value, 0, 10);

    REQUIRE(result == 0);
}

TEST_CASE("scalar::clamp::value at upper boundary is unchanged", "[scalar][clamp]")
{
    int value = 10;

    int result = nem::clamp(value, 0, 10);

    REQUIRE(result == 10);
}

// ===========================================================================
// abs
// ===========================================================================

TEST_CASE("scalar::abs::negative integer becomes positive", "[scalar][abs]")
{
    int value = -7;

    int result = nem::abs(value);

    REQUIRE(result == 7);
}

TEST_CASE("scalar::abs::positive integer is unchanged", "[scalar][abs]")
{
    int value = 7;

    int result = nem::abs(value);

    REQUIRE(result == 7);
}

// ===========================================================================
// sqr
// ===========================================================================

TEST_CASE("scalar::sqr::positive integer", "[scalar][sqr]")
{
    int value = 5;

    int result = nem::sqr(value);

    REQUIRE(result == 25);
}

TEST_CASE("scalar::sqr::negative integer yields positive", "[scalar][sqr]")
{
    int value = -5;

    int result = nem::sqr(value);

    REQUIRE(result == 25);
}

// ===========================================================================
// cube
// ===========================================================================

TEST_CASE("scalar::cube::positive integer", "[scalar][cube]")
{
    int value = 3;

    int result = nem::cube(value);

    REQUIRE(result == 27);
}

TEST_CASE("scalar::cube::negative integer preserves sign", "[scalar][cube]")
{
    int value = -2;

    int result = nem::cube(value);

    REQUIRE(result == -8);
}

// ===========================================================================
// sqrt (floating point)
// ===========================================================================

TEST_CASE("scalar::sqrt_float::perfect square converges exactly", "[scalar][sqrt]")
{
    double value = 4.0;

    double result = nem::sqrt(value);

    REQUIRE_THAT(result, WithinAbs(2.0, kEpsD));
}

TEST_CASE("scalar::sqrt_float::irrational result matches std", "[scalar][sqrt]")
{
    double value = 2.0;

    double result = nem::sqrt(value);

    REQUIRE_THAT(result, WithinAbs(std::sqrt(2.0), kEpsD));
}

TEST_CASE("scalar::sqrt_float::zero returns zero", "[scalar][sqrt]")
{
    double value = 0.0;

    double result = nem::sqrt(value);

    REQUIRE_THAT(result, WithinAbs(0.0, kEpsD));
}

TEST_CASE("scalar::sqrt_float::negative input returns zero", "[scalar][sqrt]")
{
    double value = -1.0;

    double result = nem::sqrt(value);

    REQUIRE_THAT(result, WithinAbs(0.0, kEpsD));
}

// ===========================================================================
// sqrt (integer)
// ===========================================================================

TEST_CASE("scalar::sqrt_int::zero returns zero", "[scalar][sqrt]")
{
    int result = nem::sqrt(0);

    REQUIRE(result == 0);
}

TEST_CASE("scalar::sqrt_int::4 returns 2", "[scalar][sqrt]")
{
    int result = nem::sqrt(4);

    REQUIRE(result == 2);
}

TEST_CASE("scalar::sqrt_int::9 returns 3", "[scalar][sqrt]")
{
    int result = nem::sqrt(9);

    REQUIRE(result == 3);
}

TEST_CASE("scalar::sqrt_int::25 returns 5", "[scalar][sqrt]")
{
    int result = nem::sqrt(25);

    REQUIRE(result == 5);
}

// ===========================================================================
// lerp
// ===========================================================================

TEST_CASE("scalar::lerp::returns at 0", "[scalar][lerp]")
{
    double a = 0.0;
    double b = 10.0;
    double t = 0.0;

    double result = nem::lerp(a, b, t);

    REQUIRE_THAT(result, WithinAbs(a, kEpsD));
}

TEST_CASE("scalar::lerp::returns b at 1", "[scalar][lerp]")
{
    double a = 0.0;
    double b = 10.0;
    double t = 1.0;

    double result = nem::lerp(a, b, t);

    REQUIRE_THAT(result, WithinAbs(b, kEpsD));
}

TEST_CASE("scalar::lerp::at t0.5 returns midpoint", "[scalar][lerp]")
{
    double a = 0.0;
    double b = 10.0;
    double t = 0.5;

    double result = nem::lerp(a, b, t);

    REQUIRE_THAT(result, WithinAbs(5.0, kEpsD));
}

TEST_CASE("scalar::lerp::negative range midpoint is zero", "[scalar][lerp]")
{
    double a = -4.0;
    double b = 4.0;
    double t = 0.5;

    double result = nem::lerp(a, b, t);

    REQUIRE_THAT(result, WithinAbs(0.0, kEpsD));
}

// ===========================================================================
// smoothstep
// ===========================================================================

TEST_CASE("scalar::smoothstep::returns 0 at edge0", "[scalar][smoothstep]")
{
    double result = nem::smoothstep(0.0, 1.0, 0.0);

    REQUIRE_THAT(result, WithinAbs(0.0, kEpsD));
}

TEST_CASE("scalar::smoothstep::returns 1 at edge1", "[scalar][smoothstep]")
{
    double result = nem::smoothstep(0.0, 1.0, 1.0);

    REQUIRE_THAT(result, WithinAbs(1.0, kEpsD));
}

TEST_CASE("scalar::smoothstep::returns 0.5 at symmetric midpoint", "[scalar][smoothstep]")
{
    double result = nem::smoothstep(0.0, 1.0, 0.5);

    REQUIRE_THAT(result, WithinAbs(0.5, kEpsD));
}

TEST_CASE("scalar::smoothstep::clamps below edge0", "[scalar][smoothstep]")
{
    double result = nem::smoothstep(0.0, 1.0, -1.0);

    REQUIRE_THAT(result, WithinAbs(0.0, kEpsD));
}

TEST_CASE("scalar::smoothstep::clamps above edge1", "[scalar][smoothstep]")
{
    double result = nem::smoothstep(0.0, 1.0, 2.0);

    REQUIRE_THAT(result, WithinAbs(1.0, kEpsD));
}

// ===========================================================================
// is_nearly_zero
// ===========================================================================

TEST_CASE("scalar::is_nearly_zero::exact zero", "[scalar][is_nearly_zero]")
{
    bool result = nem::is_nearly_zero(0.0);

    REQUIRE(result);
}

TEST_CASE("scalar::is_nearly_zero::within default epsilon", "[scalar][is_nearly_zero]")
{
    bool result = nem::is_nearly_zero(1e-7);

    REQUIRE(result);
}

TEST_CASE("scalar::is_nearly_zero::negative within default epsilon", "[scalar][is_nearly_zero]")
{
    bool result = nem::is_nearly_zero(-1e-7);

    REQUIRE(result);
}

TEST_CASE("scalar::is_nearly_zero::outside default epsilon", "[scalar][is_nearly_zero]")
{
    bool result = nem::is_nearly_zero(0.01);

    REQUIRE_FALSE(result);
}

TEST_CASE("scalar::is_nearly_zero::within custom epsilon", "[scalar][is_nearly_zero]")
{
    bool result = nem::is_nearly_zero(0.05, 0.1);

    REQUIRE(result);
}

TEST_CASE("scalar::is_nearly_zero::outside custom epsilon", "[scalar][is_nearly_zero]")
{
    bool result = nem::is_nearly_zero(0.15, 0.1);

    REQUIRE_FALSE(result);
}