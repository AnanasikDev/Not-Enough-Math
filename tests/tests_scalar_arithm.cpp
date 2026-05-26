#include "tests_common.hpp"

// ===========================================================================
// pow
// ===========================================================================

TEST(ScalarPow, PositiveFloat)
{
    const float value = 6;

    const float result = nem::pow(value, 2.0f);

    ASSERT_EQ(result, 36);
}

TEST(ScalarPow, ZeroFloat)
{
    const float value = 0;

    const float result = nem::pow(value, 4.0f);

    ASSERT_EQ(result, 0);
}

TEST(ScalarPow, BothSignsFloatEvenPower)
{
    const float value1 = -3;
    const float value2 = 3;

    const float result1 = nem::pow(value1, 2.0f);
    const float result2 = nem::pow(value2, 2.0f);

    ASSERT_EQ(result1, 9);
    ASSERT_EQ(result2, 9);
}

TEST(ScalarPow, BothSignsFloatOddPower)
{
    const float value1 = -3;
    const float value2 = 3;

    const float result1 = nem::pow(value1, 3.0f);
    const float result2 = nem::pow(value2, 3.0f);

    ASSERT_NEAR(result1, -27.0f, fEps);
    ASSERT_NEAR(result2,  27.0f, fEps);
}

TEST(ScalarPow, ZeroPowerFloat)
{
    const float value1 = 8;
    const float value2 = -2;

    const float result1 = nem::pow(value1, 0.0f);
    const float result2 = nem::pow(value2, 0.0f);

    ASSERT_NEAR(result1, 1.0f, fEps);
    ASSERT_NEAR(result2, 1.0f, fEps);
}

TEST(ScalarPow, ZeroBaseFloat)
{
    const float value = 0.0f;

    const float result = nem::pow(value, 5.0f);

    ASSERT_NEAR(result, value, fEps);
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

    ASSERT_NEAR(result, 2.0, dEps);
}

TEST(ScalarSqrtFloat, IrrationalResultMatchesStd)
{
    double value = 2.0;

    double result = nem::sqrt(value);

    ASSERT_NEAR(result, std::sqrt(2.0), dEps);
}

TEST(ScalarSqrtFloat, ZeroReturnsZero)
{
    double value = 0.0;

    double result = nem::sqrt(value);

    ASSERT_NEAR(result, 0.0, dEps);
}

TEST(ScalarSqrtFloat, NegativeInputReturnsZero)
{
    double value = -1.0;

    double result = nem::sqrt(value);

    ASSERT_NEAR(result, 0.0, dEps);
}

// ===========================================================================
// sqrt (integer)
// ===========================================================================

TEST(ScalarSqrt, IntZero)
{
    int result = nem::sqrt(0);

    ASSERT_EQ(result, 0);
}

TEST(ScalarSqrt, IntPositiveWhole)
{
    int result = nem::sqrt(81);

    ASSERT_EQ(result, 9);
}

TEST(ScalarSqrt, IntNegative)
{
    int result = nem::sqrt(-25);

    ASSERT_EQ(result, 0);
}

TEST(ScalarSqrt, IntPositiveNonSquare)
{
    int result = nem::sqrt(30);

    ASSERT_EQ(result, 5);
}

// ===========================================================================
// log
// ===========================================================================

TEST(ScalarLog, IntPositiveBase2)
{
    const int result = nem::log(2, 128);

    ASSERT_EQ(result, 7);
}

TEST(ScalarLog, IntPositiveBase10)
{
    const int result = nem::log(10, 10000);

    ASSERT_EQ(result, 4);
}

TEST(ScalarLog, FloatPositiveBase2)
{
    const float result = nem::log(2.0f, 4.0f);

    ASSERT_NEAR(result, 2.0f, fEps);
}

TEST(ScalarLog, FloatPositiveBase10)
{
    const float result = nem::log(10.0f, 10000.0f);

    ASSERT_NEAR(result, 4.0f, fEps);
}

TEST(ScalarLog, FloatBaseEqualsInput)
{
    const float result = nem::log(7.0f, 7.0f);

    ASSERT_NEAR(result, 1.0f, fEps);
}

TEST(ScalarLog, FloatInputNear0Valid)
{
    const float base = 3.0f;
    const float power = 0.001f;
    const float input = nem::pow(base, power);
    const float result = nem::log(base, input);

    ASSERT_NEAR(result, power, fEps);
}

TEST(ScalarLog, FloatInputIs0Invalid)
{
    const float result = nem::log(5.0f, 0.0f);

    ASSERT_TRUE(IS_SAFE_INVALID(result));
}

TEST(ScalarLog, FloatInputIsNegativeInvalid)
{
    const float result = nem::log(5.0f, -3.4f);

    ASSERT_TRUE(IS_SAFE_INVALID(result));
}

TEST(ScalarLog, FloatBaseIsNegativeInvalid)
{
    const float result = nem::log(-5.0f, -3.4f);

    ASSERT_TRUE(IS_SAFE_INVALID(result));
}

TEST(ScalarLog, FloatBaseIs0Invalid)
{
    const float result = nem::log(0.0f, 2.0f);

    ASSERT_TRUE(IS_SAFE_INVALID(result));
}

TEST(ScalarLog, FloatPowLogChain)
{
    const float base = 8.31f;
    const float power = 3.4f;
    const float input = nem::pow(base, power);
    const float result = nem::log(base, input);

    ASSERT_NEAR(result, power, fEps);
}

TEST(ScalarLog, FloatLnPowChain)
{
    const float base = nem::E<float>();
    const float power = nem::PI<float>();
    const float input = nem::pow(base, power);
    const float result = nem::ln(input);

    ASSERT_NEAR(result, power, fEps);
}

TEST(ScalarLog, FloatLnSameAsLogE)
{
    const float base = nem::E<float>();
    const float input = 12312.05f;
    const float a = nem::ln(input);
    const float b = nem::log(base, input);
    const bool result = nem::equal(a, b);
    ASSERT_TRUE(result);
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
// sign
// ===========================================================================

TEST(Sign, PositiveOne)
{
    float value = 1.0f;

    float result = nem::sign(value);

    ASSERT_NEAR(result, 1.0f, fEps);
}

TEST(Sign, NegativeOne)
{
    float value = -1.0f;

    float result = nem::sign(value);

    ASSERT_NEAR(result, -1.0f, fEps);
}

TEST(Sign, Zero)
{
    float value = 0.0f;

    float result = nem::sign(value);

    ASSERT_NEAR(result, 1.0f, fEps);
}

TEST(Sign, NearZeroPos)
{
    float value = 0.0f + nem::Eps<float>();

    float result = nem::sign(value);

    ASSERT_NEAR(result, 1.0f, fEps);
}

TEST(Sign, NearZeroNeg)
{
    float value = 0.0f - nem::Eps<float>();

    float result = nem::sign(value);

    ASSERT_NEAR(result, -1.0f, fEps);
}

TEST(Sign, PositiveLarge)
{
    float value = 4234.0f;

    float result = nem::sign(value);

    ASSERT_NEAR(result, 1.0f, fEps);
}

TEST(Sign, NegativeLarge)
{
    float value = -4234.0f;

    float result = nem::sign(value);

    ASSERT_NEAR(result, -1.0f, fEps);
}

// ===========================================================================
// copysign
// ===========================================================================

TEST(Copysign, PositiveToPositive)
{
    const float orig = 2.0f;
    float value = orig;
    float comp = 9.0f;

    value = nem::copysign(value, comp);

    ASSERT_NEAR(value, orig, fEps);
}

TEST(Copysign, PositiveToNegative)
{
    const float orig = 2.0f;
    float value = orig;
    float comp = -9.0f;

    value = nem::copysign(value, comp);

    ASSERT_NEAR(value, -orig, fEps);
}

TEST(Copysign, NegativeToNegative)
{
    const float orig = -2.0f;
    float value = orig;
    float comp = -9.0f;

    value = nem::copysign(value, comp);

    ASSERT_NEAR(value, orig, fEps);
}

TEST(Copysign, NegativeToPositive)
{
    const float orig = -2.0f;
    float value = orig;
    float comp = 9.0f;

    value = nem::copysign(value, comp);

    ASSERT_NEAR(value, -orig, fEps);
}