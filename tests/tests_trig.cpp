#include <cmath>

#include "tests_common.hpp"
#include "trig.hpp"

// ===========================================================================
// sin
// ===========================================================================

TEST(Sin, AccuracyAgainstStd_Zero)
{
    const float nem_result = nem::sin(0.0f);
    const float std_result = std::sinf(0.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Sin, AccuracyAgainstStd_Positive)
{
    const float nem_result = nem::sin(2.f);
    const float std_result = std::sinf(2.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Sin, AccuracyAgainstStd_LargePositive)
{
    const float nem_result = nem::sin(10e6f);
    const float std_result = std::sinf(10e6f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Sin, AccuracyAgainstStd_LargeNegative)
{
    const float nem_result = nem::sin(-10e6f);
    const float std_result = std::sinf(-10e6f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Sin, Repetition)
{
    const float nem_result1 = nem::sin(1.0f);
    const float nem_result2 = nem::sin(1.0f + nem::TWO_PI<float>());

    ASSERT_NEAR(nem_result1, nem_result2, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Sin, RangeAccuracyAgainstStd)
{
    range_accuracy_test(-nem::TWO_PI<float>(), nem::TWO_PI<float>(), 1000, nem::sin, std::sinf, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Sin, SparseRangeAccuracyAgainstStd)
{
    range_accuracy_test(100 * -nem::TWO_PI<float>(), 100 * nem::TWO_PI<float>(), 1000, nem::sin, std::sinf, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Sin, ExtremeSparseRangeAccuracyAgainstStd)
{
    range_accuracy_test(10e7 * -nem::TWO_PI<float>(), 10e7 * nem::TWO_PI<float>(), 1000, nem::sin, std::sinf, nem::DEFAULT_TRIG_EPSILON);
}

// ===========================================================================
// cos
// ===========================================================================

TEST(Cos, AccuracyAgainstStd_Zero)
{
    const float nem_result = nem::cos(0.0f);
    const float std_result = std::cosf(0.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Cos, AccuracyAgainstStd_Positive)
{
    const float nem_result = nem::cos(2.0f);
    const float std_result = std::cosf(2.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Cos, AccuracyAgainstStd_LargePositive)
{
    const float nem_result = nem::cos(10e6f);
    const float std_result = std::cosf(10e6f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Cos, AccuracyAgainstStd_LargeNegative)
{
    const float nem_result = nem::cos(-10e6f);
    const float std_result = std::cosf(-10e6f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Cos, Repetition)
{
    const float nem_result1 = nem::cos(1.0f);
    const float nem_result2 = nem::cos(1.0f + nem::TWO_PI<float>());

    ASSERT_NEAR(nem_result1, nem_result2, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Cos, RangeAccuracyAgainstStd)
{
    range_accuracy_test(-nem::TWO_PI<float>(), nem::TWO_PI<float>(), 1000, nem::cos, std::cosf, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Cos, SparseRangeAccuracyAgainstStd)
{
    range_accuracy_test(100 * -nem::TWO_PI<float>(),  100 * nem::TWO_PI<float>(), 1000, nem::cos, std::cosf, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Cos, ExtremeSparseRangeAccuracyAgainstStd)
{
    range_accuracy_test(10e7 * -nem::TWO_PI<float>(),  10e7 * nem::TWO_PI<float>(), 1000, nem::cos, std::cosf, nem::DEFAULT_TRIG_EPSILON);
}

// ===========================================================================
// chain - sin + cos
// ===========================================================================

TEST(SinAndCos, ShiftSinToCos)
{
    const float sinv = nem::sin(1.0f);
    const float cosv = nem::cos(1.0f - nem::HALF_PI<float>());

    ASSERT_NEAR(sinv, cosv, nem::DEFAULT_TRIG_EPSILON);
}

TEST(SinAndCos, Identity1)
{
    const float x1 = 1.0f;
    const float sinv = nem::sin(x1);
    const float cosv = nem::cos(x1);

    const float result = nem::sqr(sinv) + nem::sqr(cosv);

    ASSERT_NEAR(result, 1.0f, nem::DEFAULT_TRIG_EPSILON);
}

TEST(SinAndCos, IdentityLarge)
{
    const float x1 = 4234.2f;
    const float sinv = nem::sin(x1);
    const float cosv = nem::cos(x1);

    const float result = nem::sqr(sinv) + nem::sqr(cosv);

    ASSERT_NEAR(result, 1.0f, nem::DEFAULT_TRIG_EPSILON);
}