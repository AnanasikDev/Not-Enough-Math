#include "tests_common.hpp"

// ===========================================================================
// euclidean modulo
// ===========================================================================

TEST(Mod, PosDividendPosDivisor)
{
    float result = nem::mod(13, 5);

    ASSERT_NEAR(result, 3, fEps);
}

TEST(Mod, PosDividendNegDivisor)
{
    float result = nem::mod(13, -5);

    ASSERT_NEAR(result, 3.0f, fEps);
}

TEST(Mod, NegDividendPosDivisor)
{
    float result = nem::mod(-13, 5);

    ASSERT_NEAR(result, 2, fEps);
}

TEST(Mod, NegDividendNegDivisor)
{
    float result = nem::mod(-13, -5);

    ASSERT_NEAR(result, 2, fEps);
}

TEST(Mod, WholeDivision)
{
    float result = nem::mod(20, 4);

    ASSERT_NEAR(result, 0, fEps);
}

TEST(Mod, DividendZero)
{
    float result = nem::mod(0.0f, 4.0f);

    ASSERT_NEAR(result, 0.0f, fEps);
}

TEST(Mod, FloatOddRange)
{
    float result = nem::mod(3.0f, 1.2f);

    ASSERT_NEAR(result, 0.6f, fEps);
}

TEST(Mod, FloatOddRangeLargeDivisor)
{
    float result = nem::mod(1.123f, 2.0f);

    ASSERT_NEAR(result, 1.123f, fEps);
}

TEST(Mod, FloatNegativeWholeRangeZeroRemainder)
{
    float result = nem::mod(-4.0f, 2.0f);

    ASSERT_NEAR(result, 0.f, fEps);
}

TEST(Mod, FloatNegativeWholeRange)
{
    float result = nem::mod(-4.0f, 3.0f);

    ASSERT_NEAR(result, 2.f, fEps);
}

TEST(Mod, FloatNegativeOddRangeNoRemainder)
{
    float result = nem::mod(-3.5f, -0.7f);

    ASSERT_NEAR(result, 0.f, fEps);
}

TEST(Mod, FloatNegativeOddRange)
{
    float result = nem::mod(-10.f, 3.f);

    ASSERT_NEAR(result, 2.f, fEps);
}

// ===========================================================================
// floor
// ===========================================================================

TEST(Floor, FloatPositive)
{
    float result = nem::floor(4.8f);

    ASSERT_NEAR(result, 4.0f, fEps);
}

TEST(Floor, FloatPositiveWhole)
{
    float result = nem::floor(3.0f);

    ASSERT_NEAR(result, 3.0f, fEps);
}

TEST(Floor, FloatNegative)
{
    float result = nem::floor(-3.2f);

    ASSERT_NEAR(result, -4.0f, fEps);
}

TEST(Floor, FloatNegativeWhole)
{
    float result = nem::floor(-8.0f);

    ASSERT_NEAR(result, -8.0f, fEps);
}

TEST(Floor, FloatZero)
{
    float result = nem::floor(0.0f);

    ASSERT_NEAR(result, -0.0f, fEps);
}


// ===========================================================================
// ceil
// ===========================================================================

TEST(Ceil, FloatPositive)
{
    float result = nem::ceil(4.8f);

    ASSERT_NEAR(result, 5.0f, fEps);
}

TEST(Ceil, FloatPositiveWhole)
{
    float result = nem::ceil(3.0f);

    ASSERT_NEAR(result, 3.0f, fEps);
}

TEST(Ceil, FloatNegative)
{
    float result = nem::ceil(-3.2f);

    ASSERT_NEAR(result, -3.0f, fEps);
}

TEST(Ceil, FloatNegativeWhole)
{
    float result = nem::ceil(-8.0f);

    ASSERT_NEAR(result, -8.0f, fEps);
}

TEST(Ceil, FloatZero)
{
    float result = nem::ceil(0.0f);

    ASSERT_NEAR(result, -0.0f, fEps);
}

// ===========================================================================
// round
// ===========================================================================

TEST(Round, FloatPositiveDown)
{
    const float result = nem::round(4.1f);

    ASSERT_NEAR(result, 4.0f, fEps);
}

TEST(Round, FloatPositiveMidUp)
{
    const float result = nem::round(4.5f);

    ASSERT_NEAR(result, 5.0f, fEps);
}

TEST(Round, FloatPositiveMidDown)
{
    const float result = nem::round(4.5f - nem::Eps<float>());

    ASSERT_NEAR(result, 4.0f, fEps);
}

TEST(Round, FloatPositiveWhole)
{
    const float result = nem::round(100.0f);

    ASSERT_NEAR(result, 100.0f, fEps);
}

TEST(Round, FloatNegativeUp)
{
    const float result = nem::round(-4.1f);

    ASSERT_NEAR(result, -4.0f, fEps);
}

TEST(Round, FloatNegativeMidUp)
{
    const float result = nem::round(-4.5f);

    ASSERT_NEAR(result, -4.0f, fEps);
}

TEST(Round, FloatNegativeMidDown)
{
    const float result = nem::round(-4.5f - nem::Eps<float>());

    ASSERT_NEAR(result, -5.0f, fEps);
}

TEST(Round, FloatNegativeWhole)
{
    const float result = nem::round(-100.0f);

    ASSERT_NEAR(result, -100.0f, fEps);
}

TEST(Round, FloatZero)
{
    const float result = nem::round(0.0f);

    ASSERT_NEAR(result, 0.0f, fEps);
}

// ===========================================================================
// round with step
// ===========================================================================

TEST(RoundWithStep, FloatPositiveSecondDigitUp)
{
    const float result = nem::round(423.1634f, 0.1f);

    ASSERT_NEAR(result, 423.2f, fEps);
}

TEST(RoundWithStep, FloatPositiveSecondDigitDown)
{
    const float result = nem::round(423.1134f, 0.1f);

    ASSERT_NEAR(result, 423.1f, fEps);
}

TEST(RoundWithStep, FloatZero)
{
    const float result = nem::round(0.0f, 1.0f);

    ASSERT_NEAR(result, 0.0f, fEps);
}

TEST(RoundWithStep, FloatNegativePositiveStep)
{
    const float result = nem::round(-9.2f, 0.25f);

    ASSERT_NEAR(result, -9.25f, fEps);
}

TEST(RoundWithStep, FloatPositiveMid)
{
    const float result = nem::round(0.75f, 1.5f);

    ASSERT_NEAR(result, 1.5f, fEps);
}

TEST(RoundWithStep, FloatPositiveNearMidBelow)
{
    const float result = nem::round(0.75f - 0.001f, 1.5f);

    ASSERT_NEAR(result, 0, fEps);
}

TEST(RoundWithStep, FloatPositiveNearMidAbove)
{
    const float result = nem::round(0.75f + 0.001f, 1.5f);

    ASSERT_NEAR(result, 1.5f, fEps);
}

TEST(RoundWithStep, FloatPositiveOddToEvenPositiveStep)
{
    const float result = nem::round(123.0f, 2.0f);

    ASSERT_NEAR(result, 124.0f, fEps);
}

TEST(RoundWithStep, FloatNegativeOddToEvenPositiveStep)
{
    const float result = nem::round(-123.0f, 2.0f);

    ASSERT_NEAR(result, -122.0f, fEps);
}

TEST(RoundWithStep, IntPositive)
{
    const int result = nem::round(123, 10);

    ASSERT_EQ(result, 120);
}

TEST(RoundWithStep, IntNegative)
{
    const int result = nem::round(-123, 10);

    ASSERT_EQ(result, -120);
}

TEST(RoundWithStep, IntPositiveOddToEvenPositiveStep)
{
    const int result = nem::round(123, 2);

    ASSERT_EQ(result, 124);
}

TEST(RoundWithStep, IntNegativeOddToEvenPositiveStep)
{
    const int result = nem::round(-123, 2);

    ASSERT_EQ(result, -122);
}

// ===========================================================================
// floor with step
// ===========================================================================

TEST(FloorWithStep, FloatPositive)
{
    const float result = nem::floor(0.98f, 0.2f);

    ASSERT_NEAR(result, 0.8f, fEps);
}

TEST(FloorWithStep, FloatNegative)
{
    const float result = nem::floor(-0.98f, 0.2f);

    ASSERT_NEAR(result, -1.0f, fEps);
}

TEST(FloorWithStep, FloatLargeStep)
{
    const float result = nem::floor(19.4f, 8.0f);

    ASSERT_NEAR(result, 16.0f, fEps);
}

// ===========================================================================
// ceil with step
// ===========================================================================

TEST(CeilWithStep, FloatPositive)
{
    const float result = nem::ceil(0.98f, 0.2f);

    ASSERT_NEAR(result, 1.0f, fEps);
}

TEST(CeilWithStep, FloatNegative)
{
    const float result = nem::ceil(-0.98f, 0.2f);

    ASSERT_NEAR(result, -0.8f, fEps);
}

TEST(CeilWithStep, FloatLargeStep)
{
    const float result = nem::ceil(19.4f, 8.0f);

    ASSERT_NEAR(result, 24.0f, fEps);
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

    ASSERT_NEAR(result, 3.0f, fEps);
}

TEST(PingPong, FloatPositiveWithin2XRange)
{
    const float result = nem::pingpong(6.0f, 5.0f);

    ASSERT_NEAR(result, 4.0f, fEps);
}

TEST(PingPong, FloatPositiveWithin3XRange)
{
    const float result = nem::pingpong(10.5f, 5.0f);

    ASSERT_NEAR(result, 0.5f, fEps);
}

TEST(PingPong, FloatNegativeBelowRange)
{
    const float result = nem::pingpong(-3.0f, 5.0f);

    ASSERT_NEAR(result, 3.0f, fEps);
}

TEST(PingPong, FloatNegativeBelow2XRange)
{
    const float result = nem::pingpong(-5.0f, 5.0f);

    ASSERT_NEAR(result, 5.0f, fEps);
}

TEST(PingPong, FloatPositiveWithinMinMax)
{
    const float result = nem::pingpong(4.0f, 3.0f, 5.0f);

    ASSERT_NEAR(result, 4.0f, fEps);
}

TEST(PingPong, FloatPositiveAboveMinMax)
{
    const float result = nem::pingpong(5.5f, 3.0f, 5.0f);

    ASSERT_NEAR(result, 4.5f, fEps);
}

TEST(PingPong, FloatNegativeWithinMinMax)
{
    const float result = nem::pingpong(-1.0f, -1.5f, -0.5f);

    ASSERT_NEAR(result, -1.f, fEps);
}

TEST(PingPong, FloatNegativeBelowMinMax)
{
    const float result = nem::pingpong(-1.2f, -1.0f, -0.5f);

    ASSERT_NEAR(result, -0.8f, fEps);
}

TEST(PingPong, FloatNegativeBelow2MinMax)
{
    const float result = nem::pingpong(-2.0f, -1.0f, -0.5f);

    ASSERT_NEAR(result, -1.f, fEps);
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

    ASSERT_NEAR(result, a, dEps);
}

TEST(ScalarLerp, ReturnsBAtOne)
{
    double a = 0.0;
    double b = 10.0;
    double t = 1.0;

    double result = nem::lerp(a, b, t);

    ASSERT_NEAR(result, b, dEps);
}

TEST(ScalarLerp, AtHalfReturnsMidpoint)
{
    double a = 0.0;
    double b = 10.0;
    double t = 0.5;

    double result = nem::lerp(a, b, t);

    ASSERT_NEAR(result, 5.0, dEps);
}

TEST(ScalarLerp, NegativeRangeMidpointIsZero)
{
    double a = -4.0;
    double b = 4.0;
    double t = 0.5;

    double result = nem::lerp(a, b, t);

    ASSERT_NEAR(result, 0.0, dEps);
}

// ===========================================================================
// smoothstep
// ===========================================================================

TEST(ScalarSmoothstep, ReturnsZeroAtEdge0)
{
    double result = nem::smoothstep(0.0, 1.0, 0.0);

    ASSERT_NEAR(result, 0.0, dEps);
}

TEST(ScalarSmoothstep, ReturnsOneAtEdge1)
{
    double result = nem::smoothstep(0.0, 1.0, 1.0);

    ASSERT_NEAR(result, 1.0, dEps);
}

TEST(ScalarSmoothstep, ReturnsHalfAtSymmetricMidpoint)
{
    double result = nem::smoothstep(0.0, 1.0, 0.5);

    ASSERT_NEAR(result, 0.5, dEps);
}

TEST(ScalarSmoothstep, ClampsBelowEdge0)
{
    double result = nem::smoothstep(0.0, 1.0, -1.0);

    ASSERT_NEAR(result, 0.0, dEps);
}

TEST(ScalarSmoothstep, ClampsAboveEdge1)
{
    double result = nem::smoothstep(0.0, 1.0, 2.0);

    ASSERT_NEAR(result, 1.0, dEps);
}

// ===========================================================================
// remap
// ===========================================================================

TEST(Remap, FloatPositiveWithinRangeAmplify)
{
    const float result = nem::remap(0.5f, 0.0f, 1.0f, 10.0f, 100.0f);

    ASSERT_NEAR(result, 55.f, fEps);
}

TEST(Remap, FloatPositiveWithinRangeReduce)
{
    const float result = nem::remap(18.0f, 10.0f, 20.0f, 1.0f, 2.0f);

    ASSERT_NEAR(result, 1.8f, fEps);
}

TEST(Remap, FloatPositiveWithinRangeInvert)
{
    const float result = nem::remap(0.2f, 0.0f, 1.0f, 1.0f, 0.0f);

    ASSERT_NEAR(result, 0.8f, fEps);
}

TEST(Remap, FloatNegativeWithinRangeInvert)
{
    const float result = nem::remap(-3.3f, -4.0f, -3.0f, 9.0f, 10.0f);

    ASSERT_NEAR(result, 9.7f, fEps);
}


// ===========================================================================
// frac
// ===========================================================================

TEST(Frac, PositiveNearWhole)
{
    const float result = nem::frac(3.99f);

    ASSERT_NEAR(result, 0.99f, fEps);
}

TEST(Frac, PositiveNonWhole)
{
    const float result = nem::frac(3.2f);

    ASSERT_NEAR(result, 0.2f, fEps);
}

TEST(Frac, PositiveWhole)
{
    const float result = nem::frac(3.0f);

    ASSERT_NEAR(result, 0.0f, fEps);
}

TEST(Frac, NegativeNearWhole)
{
    const float result = nem::frac(-3.99f);

    ASSERT_NEAR(result, -0.99f, fEps);
}

TEST(Frac, NegativeNonWhole)
{
    const float result = nem::frac(-3.2f);

    ASSERT_NEAR(result, -0.2f, fEps);
}

TEST(Frac, NegativeWhole)
{
    const float result = nem::frac(-3.0f);

    ASSERT_NEAR(result, 0.0f, fEps);
}