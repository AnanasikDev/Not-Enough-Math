#include "tests_common.hpp"
#include <cmath>

// Log2 approximation

TEST(Log2, FloatOne)
{
    const float x = 1.0f;

    const float result = nem::log2(x);
    const float std_expected = std::log2f(x);
    const float expected = 0.0f;

    ASSERT_NEAR(result, std_expected, nem::rel_error<float>(x));
    ASSERT_NEAR(result, expected, nem::rel_error<float>(x));
}

TEST(Log2, FloatSmallPositive)
{
    const float x = 5.0f;

    const float result = nem::log2(x);
    const float std_expected = std::log2f(x);

    ASSERT_NEAR(result, std_expected, nem::rel_error<float>(x));
}

TEST(Log2, FloatBigPositive)
{
    const float x = 30.0f;

    const float result = nem::log2(x);
    const float std_expected = std::log2f(x);

    ASSERT_NEAR(result, std_expected, nem::rel_error<float>(x));
}

TEST(Log2, FloatLargePositive)
{
    const float x = 300.0f;

    const float result = nem::log2(x);
    const float std_expected = std::log2f(x);

    ASSERT_NEAR(result, std_expected, nem::rel_error<float>(x));
}

TEST(Log2, FloatVeryLargePositive)
{
    const float x = 10000.0f;

    const float result = nem::log2(x);
    const float std_expected = std::log2f(x);

    ASSERT_NEAR(result, std_expected, nem::rel_error<float>(x));
}

// Very fast log2 approximation

TEST(FastLog2, FloatVerySmall)
{
    const float x = 0.125f;

    const float result = nem::log2(x);
    const float std_expected = std::log2f(x);
    const float expected = -3.0f;

    ASSERT_NEAR(result, std_expected, nem::rel_error(expected));
    ASSERT_NEAR(result, expected, nem::rel_error(expected));
}

TEST(FastLog2, FloatSmall)
{
    const float x = 0.5f;

    const float result = nem::log2(x);
    const float std_expected = std::log2f(x);
    const float expected = -1.0f;

    ASSERT_NEAR(result, std_expected, nem::rel_error(expected));
    ASSERT_NEAR(result, expected, nem::rel_error(expected));
}

TEST(FastLog2, FloatOne)
{
    const float x = 1.0f;

    const float result = nem::log2(x);
    const float std_expected = std::log2f(x);
    const float expected = 0.0f;

    ASSERT_NEAR(result, std_expected, nem::abs_error<float>());
    ASSERT_NEAR(result, expected, nem::abs_error<float>());
}

TEST(FastLog2, FloatSmallPositive)
{
    const float x = 5.0f;

    const float result = nem::log2(x);
    const float std_expected = std::log2f(x);

    ASSERT_NEAR(result, std_expected, nem::rel_error<float>(x));
}

TEST(FastLog2, FloatBigPositive)
{
    const float x = 30.0f;

    const float result = nem::log2(x);
    const float std_expected = std::log2f(x);

    ASSERT_NEAR(result, std_expected, nem::rel_error<float>(x));
}

TEST(FastLog2, FloatLargePositive)
{
    const float x = 300.0f;

    const float result = nem::log2(x);
    const float std_expected = std::log2f(x);

    ASSERT_NEAR(result, std_expected, nem::rel_error<float>(x));
}

TEST(FastLog2, FloatVeryLargePositive)
{
    const float x = 10000.0f;

    const float result = nem::log2(x);
    const float std_expected = std::log2f(x);

    ASSERT_NEAR(result, std_expected, nem::rel_error<float>(x));
}

// ===========================================================================
// pow
// ===========================================================================

TEST(ScalarPow, PositiveFloat)
{
    const float value = 6;

    const float result = nem::pow(value, 2.0f);
    const float expected = 36.0f;

    ASSERT_NEAR(result, expected, nem::rel_error(expected));
}

TEST(ScalarPow, ZeroFloat)
{
    const float value = 0;

    const float result = nem::pow(value, 4.0f);
    const float expected = 0.0f;

    ASSERT_NEAR(result, expected, nem::abs_error<float>());
}

TEST(ScalarPow, BothSignsFloatEvenPower)
{
    const float value1 = -3;
    const float value2 = 3;

    const float result1 = nem::pow(value1, 2.0f);
    const float result2 = nem::pow(value2, 2.0f);

    const float expected1 = 9.0f;
    const float expected2 = 9.0f;

    ASSERT_NEAR(result1, expected1, nem::rel_error(expected1));
    ASSERT_NEAR(result2, expected2, nem::rel_error(expected2));
}

TEST(ScalarPow, BothSignsFloatOddPower)
{
    const float value1 = -3;
    const float value2 = 3;

    const float result1 = nem::pow(value1, 3.0f);
    const float result2 = nem::pow(value2, 3.0f);

    const float expected1 = -27.0f;
    const float expected2 =  27.0f;

    ASSERT_NEAR(result1, expected1, nem::rel_error(expected1));
    ASSERT_NEAR(result2, expected2, nem::rel_error(expected2));
}

TEST(ScalarPow, ZeroPowerFloat)
{
    const float value1 = 8;
    const float value2 = -2;

    const float result1 = nem::pow(value1, 0.0f);
    const float result2 = nem::pow(value2, 0.0f);
    const float expected = 1.0f;

    ASSERT_NEAR(result1, expected, nem::rel_error(expected));
    ASSERT_NEAR(result2, expected, nem::rel_error(expected));
}

TEST(ScalarPow, ZeroBaseFloat)
{
    const float value = 0.0f;

    const float result = nem::pow(value, 5.0f);

    ASSERT_NEAR(result, value, nem::abs_error<float>());
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
    const double expected = 2.0;

    ASSERT_NEAR(result, expected, dEps);
}

TEST(ScalarSqrtFloat, IrrationalResultMatchesStd)
{
    double value = 2.0;

    double result = nem::sqrt(value);
    const double expected = std::sqrt(2.0);

    ASSERT_NEAR(result, expected, dEps);
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
    double expected = 0.0;

    ASSERT_NEAR(result, expected, dEps);
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
    const float expected = 2.0f;
    const float result = nem::log(2.0f, 4.0f);

    ASSERT_NEAR(result, expected, nem::rel_error(expected));
}

TEST(ScalarLog, FloatPositiveBase10)
{
    const float expected = 4.0f;
    const float result = nem::log(10.0f, 10000.0f);

    ASSERT_NEAR(result, expected, nem::rel_error(expected));
}

TEST(ScalarLog, FloatBaseEqualsInput)
{
    const float expected = 1.0f;
    const float result = nem::log(7.0f, 7.0f);

    ASSERT_NEAR(result, expected, nem::rel_error(expected));
}

TEST(ScalarLog, FloatInputNear0Valid)
{
    const float base = 3.0f;
    const float power = 0.01f;
    const float input = nem::pow(base, power);
    const float result = nem::log(base, input);
    const float expected = power;

    ASSERT_NEAR(result, expected, nem::rel_error(expected));
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
    const float expected = power;

    ASSERT_NEAR(result, expected, nem::rel_error(expected));
}

TEST(ScalarLog, FloatLnPowChain)
{
    const float base = nem::E<float>;
    const float power = nem::PI<float>;
    const float input = nem::pow(base, power);
    const float result = nem::ln(input);
    const float expected = power;

    ASSERT_NEAR(result, expected, nem::rel_error(expected));
}

TEST(ScalarLog, FloatLnSameAsLogE)
{
    const float base = nem::E<float>;
    const float input = 12312.05f;
    const float a = nem::ln(input);
    const float b = nem::log(base, input);
    const float expected = b;

    ASSERT_NEAR(a, expected, nem::rel_error(expected));
}
