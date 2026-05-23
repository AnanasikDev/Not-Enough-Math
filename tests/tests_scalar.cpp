#include <gtest/gtest.h>
#include "nem.hpp"

static constexpr float  kEps = 1e-4f;
static constexpr double kEpsD = 1e-9;

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

// ===========================================================================
// euclidean modulo
// ===========================================================================

TEST(Mod, PosDividendPosDivisor)
{
    float result = nem::mod(13, 5);

    ASSERT_EQ(result, 3);
}

TEST(Mod, PosDividendNegDivisor)
{
    float result = nem::mod(13, -5);

    ASSERT_EQ(result, 3);
}

TEST(Mod, NegDividendPosDivisor)
{
    float result = nem::mod(-13, 5);

    ASSERT_EQ(result, 2);
}

TEST(Mod, NegDividendNegDivisor)
{
    float result = nem::mod(-13, -5);

    ASSERT_EQ(result, 2);
}

TEST(Mod, WholeDivision)
{
    float result = nem::mod(20, 4);

    ASSERT_EQ(result, 0);
}

TEST(Mod, DividendZero)
{
    float result = nem::mod(0, 4);

    ASSERT_EQ(result, IS_SAFE_INVALID(result));
}

TEST(Mod, FloatOddRange)
{
    float result = nem::mod(3.0f, 1.2f);

    ASSERT_NEAR(result, 0.6f, kEps);
}

TEST(Mod, FloatOddRangeLargeDivisor)
{
    float result = nem::mod(1.123f, 2.0f);

    ASSERT_NEAR(result, 1.123f, kEps);
}

TEST(Mod, FloatNegativeWholeRangeZeroRemainder)
{
    float result = nem::mod(-4.0f, 2.0f);

    ASSERT_NEAR(result, 0.f, kEps);
}

TEST(Mod, FloatNegativeWholeRange)
{
    float result = nem::mod(-4.0f, 3.0f);

    ASSERT_NEAR(result, 2.f, kEps);
}

TEST(Mod, FloatNegativeOddRangeNoRemainder)
{
    float result = nem::mod(-3.5f, -0.7f);

    ASSERT_NEAR(result, 0.f, kEps);
}

TEST(Mod, FloatNegativeOddRange)
{
    float result = nem::mod(-10.f, 3.f);

    ASSERT_NEAR(result, 2.f, kEps);
}

// ===========================================================================
// floor
// ===========================================================================

TEST(Floor, FloatPositive)
{
    float result = nem::floor(4.8f);

    ASSERT_NEAR(result, 4.0f, kEps);
}

TEST(Floor, FloatPositiveWhole)
{
    float result = nem::floor(3.0f);

    ASSERT_NEAR(result, 3.0f, kEps);
}

TEST(Floor, FloatNegative)
{
    float result = nem::floor(-3.2f);

    ASSERT_NEAR(result, -4.0f, kEps);
}

TEST(Floor, FloatNegativeWhole)
{
    float result = nem::floor(-8.0f);

    ASSERT_NEAR(result, -8.0f, kEps);
}

TEST(Floor, FloatZero)
{
    float result = nem::floor(0.0f);

    ASSERT_NEAR(result, -0.0f, kEps);
}


// ===========================================================================
// ceil
// ===========================================================================

TEST(Ceil, FloatPositive)
{
    float result = nem::ceil(4.8f);

    ASSERT_NEAR(result, 5.0f, kEps);
}

TEST(Ceil, FloatPositiveWhole)
{
    float result = nem::ceil(3.0f);

    ASSERT_NEAR(result, 3.0f, kEps);
}

TEST(Ceil, FloatNegative)
{
    float result = nem::ceil(-3.2f);

    ASSERT_NEAR(result, -3.0f, kEps);
}

TEST(Ceil, FloatNegativeWhole)
{
    float result = nem::ceil(-8.0f);

    ASSERT_NEAR(result, -8.0f, kEps);
}

TEST(Ceil, FloatZero)
{
    float result = nem::ceil(0.0f);

    ASSERT_NEAR(result, -0.0f, kEps);
}

// ===========================================================================
// clamp
// ===========================================================================

TEST(ScalarClamp, InRangeValueIsUnchanged)
{
    int value = 5;

    int result = nem::clamp(value, 0, 10);

    ASSERT_EQ(result, 5);
}

TEST(ScalarClamp, ValueBelowMinBecomesMin)
{
    int value = -1;

    int result = nem::clamp(value, 0, 10);

    ASSERT_EQ(result, 0);
}

TEST(ScalarClamp, ValueAboveMaxBecomesMax)
{
    int value = 11;

    int result = nem::clamp(value, 0, 10);

    ASSERT_EQ(result, 10);
}

TEST(ScalarClamp, ValueAtLowerBoundaryIsUnchanged)
{
    int value = 0;

    int result = nem::clamp(value, 0, 10);

    ASSERT_EQ(result, 0);
}

TEST(ScalarClamp, ValueAtUpperBoundaryIsUnchanged)
{
    int value = 10;

    int result = nem::clamp(value, 0, 10);

    ASSERT_EQ(result, 10);
}

// ===========================================================================
// repeat
// ===========================================================================

TEST(ScalarRepeat, ValueAtUpperBoundaryIsUnchanged)
{
    int value = 10;

    int result = nem::repeat(value, 0, 10);

    ASSERT_EQ(result, 0);
}

TEST(ScalarRepeat, ValueAtLowerBoundaryIsUnchanged)
{
    int value = 2;

    int result = nem::repeat(value, 2, 10);

    ASSERT_EQ(result, 2);
}

TEST(ScalarRepeat, ValueBetweenBoundsIsUnchanged)
{
    int value = 6;

    int result = nem::repeat(value, 0, 10);

    ASSERT_EQ(result, 6);
}

TEST(ScalarRepeat, ValueBetween2XBoundsIsRepeated)
{
    int value = 11;

    int result = nem::repeat(value, 0, 10);

    ASSERT_EQ(result, 1);
}

TEST(ScalarRepeat, ValueBetweenMinusBoundsIsRepeated)
{
    int value = -6;

    int result = nem::repeat(value, 0, 10);

    ASSERT_EQ(result, 4);
}

TEST(ScalarRepeat, ValueBelowOddBoundsIsRepeated)
{
    int value = 3;

    int result = nem::repeat(value, 7, 13);

    ASSERT_EQ(result, 9);
}

TEST(ScalarRepeat, ValueAboveOddBoundsIsRepeated)
{
    int value = 16;

    int result = nem::repeat(value, 7, 13);

    ASSERT_EQ(result, 10);
}

// ===========================================================================
// abs
// ===========================================================================

TEST(ScalarAbs, NegativeIntegerBecomesPositive)
{
    int value = -7;

    int result = nem::abs(value);

    ASSERT_EQ(result, 7);
}

TEST(ScalarAbs, PositiveIntegerIsUnchanged)
{
    int value = 7;

    int result = nem::abs(value);

    ASSERT_EQ(result, 7);
}

// ===========================================================================
// sqr
// ===========================================================================

TEST(ScalarSqr, PositiveInteger)
{
    int value = 5;

    int result = nem::sqr(value);

    ASSERT_EQ(result, 25);
}

TEST(ScalarSqr, NegativeIntegerYieldsPositive)
{
    int value = -5;

    int result = nem::sqr(value);

    ASSERT_EQ(result, 25);
}

// ===========================================================================
// cube
// ===========================================================================

TEST(ScalarCube, PositiveInteger)
{
    int value = 3;

    int result = nem::cube(value);

    ASSERT_EQ(result, 27);
}

TEST(ScalarCube, NegativeIntegerPreservesSign)
{
    int value = -2;

    int result = nem::cube(value);

    ASSERT_EQ(result, -8);
}

// ===========================================================================
// sqrt (floating point)
// ===========================================================================

TEST(ScalarSqrtFloat, PerfectSquareConvergesExactly)
{
    double value = 4.0;

    double result = nem::sqrt(value);

    ASSERT_NEAR(result, 2.0, kEpsD);
}

TEST(ScalarSqrtFloat, IrrationalResultMatchesStd)
{
    double value = 2.0;

    double result = nem::sqrt(value);

    ASSERT_NEAR(result, std::sqrt(2.0), kEpsD);
}

TEST(ScalarSqrtFloat, ZeroReturnsZero)
{
    double value = 0.0;

    double result = nem::sqrt(value);

    ASSERT_NEAR(result, 0.0, kEpsD);
}

TEST(ScalarSqrtFloat, NegativeInputReturnsZero)
{
    double value = -1.0;

    double result = nem::sqrt(value);

    ASSERT_NEAR(result, 0.0, kEpsD);
}

// ===========================================================================
// sqrt (integer)
// ===========================================================================

TEST(ScalarSqrtInt, ZeroReturnsZero)
{
    int result = nem::sqrt(0);

    ASSERT_EQ(result, 0);
}

TEST(ScalarSqrtInt, FourReturnsTwo)
{
    int result = nem::sqrt(4);

    ASSERT_EQ(result, 2);
}

TEST(ScalarSqrtInt, NineReturnsThree)
{
    int result = nem::sqrt(9);

    ASSERT_EQ(result, 3);
}

TEST(ScalarSqrtInt, TwentyFiveReturnsFive)
{
    int result = nem::sqrt(25);

    ASSERT_EQ(result, 5);
}

// ===========================================================================
// lerp
// ===========================================================================

TEST(ScalarLerp, ReturnsAAtZero)
{
    double a = 0.0;
    double b = 10.0;
    double t = 0.0;

    double result = nem::lerp(a, b, t);

    ASSERT_NEAR(result, a, kEpsD);
}

TEST(ScalarLerp, ReturnsBAtOne)
{
    double a = 0.0;
    double b = 10.0;
    double t = 1.0;

    double result = nem::lerp(a, b, t);

    ASSERT_NEAR(result, b, kEpsD);
}

TEST(ScalarLerp, AtHalfReturnsMidpoint)
{
    double a = 0.0;
    double b = 10.0;
    double t = 0.5;

    double result = nem::lerp(a, b, t);

    ASSERT_NEAR(result, 5.0, kEpsD);
}

TEST(ScalarLerp, NegativeRangeMidpointIsZero)
{
    double a = -4.0;
    double b = 4.0;
    double t = 0.5;

    double result = nem::lerp(a, b, t);

    ASSERT_NEAR(result, 0.0, kEpsD);
}

// ===========================================================================
// smoothstep
// ===========================================================================

TEST(ScalarSmoothstep, ReturnsZeroAtEdge0)
{
    double result = nem::smoothstep(0.0, 1.0, 0.0);

    ASSERT_NEAR(result, 0.0, kEpsD);
}

TEST(ScalarSmoothstep, ReturnsOneAtEdge1)
{
    double result = nem::smoothstep(0.0, 1.0, 1.0);

    ASSERT_NEAR(result, 1.0, kEpsD);
}

TEST(ScalarSmoothstep, ReturnsHalfAtSymmetricMidpoint)
{
    double result = nem::smoothstep(0.0, 1.0, 0.5);

    ASSERT_NEAR(result, 0.5, kEpsD);
}

TEST(ScalarSmoothstep, ClampsBelowEdge0)
{
    double result = nem::smoothstep(0.0, 1.0, -1.0);

    ASSERT_NEAR(result, 0.0, kEpsD);
}

TEST(ScalarSmoothstep, ClampsAboveEdge1)
{
    double result = nem::smoothstep(0.0, 1.0, 2.0);

    ASSERT_NEAR(result, 1.0, kEpsD);
}

// ===========================================================================
// is_nearly_zero
// ===========================================================================

TEST(ScalarIsNearlyZero, ExactZero)
{
    bool result = nem::is_nearly_zero(0.0);

    ASSERT_TRUE(result);
}

TEST(ScalarIsNearlyZero, WithinDefaultEpsilon)
{
    bool result = nem::is_nearly_zero(1e-7);

    ASSERT_TRUE(result);
}

TEST(ScalarIsNearlyZero, NegativeWithinDefaultEpsilon)
{
    bool result = nem::is_nearly_zero(-1e-7);

    ASSERT_TRUE(result);
}

TEST(ScalarIsNearlyZero, OutsideDefaultEpsilon)
{
    bool result = nem::is_nearly_zero(0.01);

    ASSERT_FALSE(result);
}

TEST(ScalarIsNearlyZero, WithinCustomEpsilon)
{
    bool result = nem::is_nearly_zero(0.05, 0.1);

    ASSERT_TRUE(result);
}

TEST(ScalarIsNearlyZero, OutsideCustomEpsilon)
{
    bool result = nem::is_nearly_zero(0.15, 0.1);

    ASSERT_FALSE(result);
}
