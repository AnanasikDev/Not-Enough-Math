#include "tests_common.hpp"

// ===========================================================================
// is_zero
// ===========================================================================

TEST(ScalarIsNearlyZero, ExactZero)
{
    bool result = nem::is_zero(0.0f);

    ASSERT_TRUE(result);
}

TEST(ScalarIsNearlyZero, WithinDefaultEpsilon)
{
    bool result = nem::is_zero(1e-7f);

    ASSERT_TRUE(result);
}

TEST(ScalarIsNearlyZero, NegativeWithinDefaultEpsilon)
{
    bool result = nem::is_zero(-1e-7f);

    ASSERT_TRUE(result);
}

TEST(ScalarIsNearlyZero, OutsideDefaultEpsilon)
{
    bool result = nem::is_zero(0.01f);

    ASSERT_FALSE(result);
}

// ===========================================================================
// equal
// ===========================================================================

TEST(ScalarAreNearlyEqual, ExactlyEqual)
{
    float a = 5.51f;
    float b = 5.51f;
    bool result = nem::equal(a, b);

    ASSERT_TRUE(result);
}

TEST(ScalarAreNearlyEqual, Different4Digit)
{
    float a = 5.5101f;
    float b = 5.5102f;
    bool result = nem::equal(a, b);

    ASSERT_FALSE(result);
}

// ===========================================================================
// is_zero_or_neg
// ===========================================================================

TEST(IsZeroOrNeg, FloatPositive)
{
    const float a = 5.51f;
    const bool result = nem::is_zero_or_neg(a);

    ASSERT_FALSE(result);
}

TEST(IsZeroOrNeg, FloatNegative)
{
    const float a = -5.51f;
    const bool result = nem::is_zero_or_neg(a);

    ASSERT_TRUE(result);
}

TEST(IsZeroOrNeg, FloatZero)
{
    const float a = 0.0f;
    const bool result = nem::is_zero_or_neg(a);

    ASSERT_TRUE(result);
}

TEST(IsZeroOrNeg, FloatPositiveBelowAbsEpsilon)
{
    const float a = nem::eps<float>() / 5.0f;
    const bool result = nem::is_zero_or_neg(a);

    ASSERT_TRUE(result);
}

TEST(IsZeroOrNeg, FloatNegativeBelowAbsEpsilon)
{
    const float a = -nem::eps<float>() / 5.0f;
    const bool result = nem::is_zero_or_neg(a);

    ASSERT_TRUE(result);
}