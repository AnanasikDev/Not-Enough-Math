#include "tests_common.hpp"

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
    float value = 0.0f + nem::eps<float>();

    float result = nem::sign(value);

    ASSERT_NEAR(result, 1.0f, fEps);
}

TEST(Sign, NearZeroNeg)
{
    float value = 0.0f - nem::eps<float>();

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