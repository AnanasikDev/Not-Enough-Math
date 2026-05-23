#include "tests_common.hpp"

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
// pingpong
// ===========================================================================

TEST(PingPong, FloatPositiveWithinRange)
{
    const float result = nem::pingpong(3.0f, 5.0f);

    ASSERT_NEAR(result, 3.0f, kEps);
}

TEST(PingPong, FloatPositiveWithin2XRange)
{
    const float result = nem::pingpong(6.0f, 5.0f);

    ASSERT_NEAR(result, 4.0f, kEps);
}

TEST(PingPong, FloatPositiveWithin3XRange)
{
    const float result = nem::pingpong(10.5f, 5.0f);

    ASSERT_NEAR(result, 0.5f, kEps);
}

TEST(PingPong, FloatNegativeBelowRange)
{
    const float result = nem::pingpong(-3.0f, 5.0f);

    ASSERT_NEAR(result, 3.0f, kEps);
}

TEST(PingPong, FloatNegativeBelow2XRange)
{
    const float result = nem::pingpong(-5.0f, 5.0f);

    ASSERT_NEAR(result, 5.0f, kEps);
}

TEST(PingPong, FloatPositiveWithinMinMax)
{
    const float result = nem::pingpong(4.0f, 3.0f, 5.0f);

    ASSERT_NEAR(result, 4.0f, kEps);
}

TEST(PingPong, FloatPositiveAboveMinMax)
{
    const float result = nem::pingpong(5.5f, 3.0f, 5.0f);

    ASSERT_NEAR(result, 4.5f, kEps);
}

TEST(PingPong, FloatNegativeWithinMinMax)
{
    const float result = nem::pingpong(-1.0f, -1.5f, -0.5f);

    ASSERT_NEAR(result, -1.f, kEps);
}

TEST(PingPong, FloatNegativeBelowMinMax)
{
    const float result = nem::pingpong(-1.2f, -1.0f, -0.5f);

    ASSERT_NEAR(result, -0.8f, kEps);
}

TEST(PingPong, FloatNegativeBelow2MinMax)
{
    const float result = nem::pingpong(-2.0f, -1.0f, -0.5f);

    ASSERT_NEAR(result, -1.f, kEps);
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