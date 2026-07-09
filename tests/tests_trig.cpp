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
    const double nem_result = nem::sin(10e4f);
    const double std_result = std::sinf(10e4f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Sin, AccuracyAgainstStd_LargeNegative)
{
    const double nem_result = nem::sin(-10e4f);
    const double std_result = std::sinf(-10e4f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Sin, Repetition)
{
    const float nem_result1 = nem::sin(1.0f);
    const float nem_result2 = nem::sin(1.0f + nem::TWO_PI<float>);

    ASSERT_NEAR(nem_result1, nem_result2, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Sin, RangeAccuracyAgainstStd)
{
    range_accuracy_test(-nem::TWO_PI<double>, nem::TWO_PI<double>, 1000, nem::sin<double>, std::sin, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Sin, SparseRangeAccuracyAgainstStd)
{
    range_accuracy_test(100 * -nem::TWO_PI<double>, 100 * nem::TWO_PI<double>, 1000, nem::sin<double>, std::sin, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Sin, ExtremeSparseRangeAccuracyAgainstStd)
{
    range_accuracy_test(10e7 * -nem::TWO_PI<double>, 10e7 * nem::TWO_PI<double>, 1000, nem::sin<double>, std::sin, nem::DEFAULT_TRIG_EPSILON);
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
    const double nem_result = nem::cos(10e4f);
    const double std_result = std::cosf(10e4f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Cos, AccuracyAgainstStd_LargeNegative)
{
    const double nem_result = nem::cos(-10e4f);
    const double std_result = std::cosf(-10e4f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Cos, Repetition)
{
    const float nem_result1 = nem::cos(1.0f);
    const float nem_result2 = nem::cos(1.0f + nem::TWO_PI<float>);

    ASSERT_NEAR(nem_result1, nem_result2, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Cos, RangeAccuracyAgainstStd)
{
    range_accuracy_test(-nem::TWO_PI<double>, nem::TWO_PI<double>, 1000, nem::cos<double>, std::cos, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Cos, SparseRangeAccuracyAgainstStd)
{
    range_accuracy_test(100 * -nem::TWO_PI<double>,  100 * nem::TWO_PI<double>, 1000, nem::cos<double>, std::cos, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Cos, ExtremeSparseRangeAccuracyAgainstStd)
{
    range_accuracy_test(10e7 * -nem::TWO_PI<double>,  10e7 * nem::TWO_PI<double>, 1000, nem::cos<double>, std::cos, nem::DEFAULT_TRIG_EPSILON);
}

// ===========================================================================
// chain - sin + cos
// ===========================================================================

TEST(SinAndCos, ShiftSinToCos)
{
    const float sinv = nem::sin(1.0f);
    const float cosv = nem::cos(1.0f - nem::HALF_PI<float>);

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

TEST(GetSincos, MatchesSeparateSinAndCos)
{
    const float values[] = { 0.0f, 0.3f, 1.0f, 2.0f, -2.0f, 4234.2f, -10e4f };
    for (float x : values)
    {
        const nem::sincos<float> sc = nem::get_sincos(x);
        EXPECT_NEAR(sc.sin, nem::sin(x), nem::DEFAULT_TRIG_EPSILON);
        EXPECT_NEAR(sc.cos, nem::cos(x), nem::DEFAULT_TRIG_EPSILON);
    }
}

// ===========================================================================
// tan / ctg / sec / csc
// ===========================================================================

TEST(Tan, AccuracyAgainstStd)
{
    const float nem_result = nem::tan(0.5f);
    const float std_result = std::tan(0.5f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Tan, RangeAccuracyAgainstStd)
{
    range_accuracy_test(-1.2, 1.2, 1000, nem::tan<double>, std::tan, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Ctg, AccuracyAgainstStd)
{
    const float nem_result = nem::ctg(0.5f);
    const float std_result = 1.0f / std::tan(0.5f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Ctg, RangeAccuracyAgainstStd)
{
    range_accuracy_test(0.3, 2.8, 1000, nem::ctg<double>, [](double x) { return 1.0 / std::tan(x); }, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Sec, AccuracyAgainstStd)
{
    const float nem_result = nem::sec(0.5f);
    const float std_result = 1.0f / std::cos(0.5f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Csc, AccuracyAgainstStd)
{
    const float nem_result = nem::csc(0.5f);
    const float std_result = 1.0f / std::sin(0.5f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Tan, DivisionByZeroInvalid)
{
    const float result = nem::tan(nem::HALF_PI<float>);

    ASSERT_TRUE(IS_SAFE_INVALID(result));
}

TEST(Ctg, DivisionByZeroInvalid)
{
    const float result = nem::ctg(0.0f);

    ASSERT_TRUE(IS_SAFE_INVALID(result));
}

TEST(Sec, DivisionByZeroInvalid)
{
    const float result = nem::sec(nem::HALF_PI<float>);

    ASSERT_TRUE(IS_SAFE_INVALID(result));
}

TEST(Csc, DivisionByZeroInvalid)
{
    const float result = nem::csc(0.0f);

    ASSERT_TRUE(IS_SAFE_INVALID(result));
}

// ===========================================================================
// atan / atan2
// ===========================================================================

TEST(Atan, AccuracyAgainstStd_Zero)
{
    const float nem_result = nem::atan(0.0f);
    const float std_result = std::atan(0.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Atan, AccuracyAgainstStd_Positive)
{
    const float nem_result = nem::atan(0.6f);
    const float std_result = std::atan(0.6f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Atan, AccuracyAgainstStd_Negative)
{
    const float nem_result = nem::atan(-0.6f);
    const float std_result = std::atan(-0.6f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Atan, AccuracyAgainstStd_GreaterThanOne)
{
    const float nem_result = nem::atan(3.7f);
    const float std_result = std::atan(3.7f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Atan, AccuracyAgainstStd_LessThanNegativeOne)
{
    const float nem_result = nem::atan(-3.7f);
    const float std_result = std::atan(-3.7f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Atan, ApproachesHalfPiForLargeInput)
{
    const float nem_result = nem::atan(10e6f);

    ASSERT_NEAR(nem_result, nem::HALF_PI<float>, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Atan, RangeAccuracyAgainstStd)
{
    range_accuracy_test(-50.0, 50.0, 1000, nem::atan<double>, std::atan, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Atan2, AccuracyAgainstStd_FirstQuadrant)
{
    const float nem_result = nem::atan2(1.0f, 2.0f);
    const float std_result = std::atan2(1.0f, 2.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Atan2, AccuracyAgainstStd_SecondQuadrant)
{
    const float nem_result = nem::atan2(1.0f, -2.0f);
    const float std_result = std::atan2(1.0f, -2.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Atan2, AccuracyAgainstStd_ThirdQuadrant)
{
    const float nem_result = nem::atan2(-1.0f, -2.0f);
    const float std_result = std::atan2(-1.0f, -2.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Atan2, AccuracyAgainstStd_FourthQuadrant)
{
    const float nem_result = nem::atan2(-1.0f, 2.0f);
    const float std_result = std::atan2(-1.0f, 2.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Atan2, AccuracyAgainstStd_PositiveYAxis)
{
    const float nem_result = nem::atan2(1.0f, 0.0f);
    const float std_result = std::atan2(1.0f, 0.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Atan2, AccuracyAgainstStd_NegativeYAxis)
{
    const float nem_result = nem::atan2(-1.0f, 0.0f);
    const float std_result = std::atan2(-1.0f, 0.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Atan2, UndefinedAtOrigin)
{
    const float result = nem::atan2(0.0f, 0.0f);

    ASSERT_TRUE(IS_SAFE_INVALID(result));
}

TEST(Atan2, RangeAccuracyAgainstStd)
{
    for (double t = -nem::PI<double> + 0.05; t < nem::PI<double>; t += 0.05)
    {
        const double y = std::sin(t);
        const double x = std::cos(t);
        const double nem_result = nem::atan2(y, x);
        const double std_result = std::atan2(y, x);
        EXPECT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
    }
}

// ===========================================================================
// actg / actg2
// ===========================================================================

TEST(Actg, AccuracyAgainstStd_Zero)
{
    const float nem_result = nem::actg(0.0f);
    const float std_result = std::atan2(1.0f, 0.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Actg, AccuracyAgainstStd_Positive)
{
    const float nem_result = nem::actg(0.6f);
    const float std_result = std::atan2(1.0f, 0.6f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Actg, AccuracyAgainstStd_Negative)
{
    const float nem_result = nem::actg(-0.6f);
    const float std_result = std::atan2(1.0f, -0.6f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Actg, RangeAccuracyAgainstStd)
{
    for (double x = -50.0; x < 50.0; x += 0.5)
    {
        const double nem_result = nem::actg(x);
        const double std_result = std::atan2(1.0, x);
        EXPECT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
    }
}

TEST(AtanActg, Identity)
{
    const float x = 0.42f;
    const float result = nem::atan(x) + nem::actg(x);

    ASSERT_NEAR(result, nem::HALF_PI<float>, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Actg2, AccuracyAgainstStd_FirstQuadrant)
{
    const float nem_result = nem::actg2(1.0f, 2.0f);
    const float std_result = std::atan2(1.0f, 2.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Actg2, AccuracyAgainstStd_SecondQuadrant)
{
    const float nem_result = nem::actg2(-2.0f, 1.0f);
    const float std_result = std::atan2(-2.0f, 1.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Actg2, UndefinedAtOrigin)
{
    const float result = nem::actg2(0.0f, 0.0f);

    ASSERT_TRUE(IS_SAFE_INVALID(result));
}

// ===========================================================================
// asin / acos
// ===========================================================================

TEST(Acos, AccuracyAgainstStd_Zero)
{
    const float nem_result = nem::acos(0.0f);
    const float std_result = std::acos(0.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Acos, AccuracyAgainstStd_Bounds)
{
    ASSERT_NEAR(nem::acos(1.0f), std::acos(1.0f), nem::DEFAULT_TRIG_EPSILON);
    ASSERT_NEAR(nem::acos(-1.0f), std::acos(-1.0f), nem::DEFAULT_TRIG_EPSILON);
}

TEST(Acos, RangeAccuracyAgainstStd)
{
    range_accuracy_test(-1.0, 1.0, 1000, nem::acos<double>, std::acos, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Asin, AccuracyAgainstStd_Zero)
{
    const float nem_result = nem::asin(0.0f);
    const float std_result = std::asin(0.0f);

    ASSERT_NEAR(nem_result, std_result, nem::DEFAULT_TRIG_EPSILON);
}

TEST(Asin, AccuracyAgainstStd_Bounds)
{
    ASSERT_NEAR(nem::asin(1.0f), std::asin(1.0f), nem::DEFAULT_TRIG_EPSILON);
    ASSERT_NEAR(nem::asin(-1.0f), std::asin(-1.0f), nem::DEFAULT_TRIG_EPSILON);
}

TEST(Asin, RangeAccuracyAgainstStd)
{
    range_accuracy_test(-1.0, 1.0, 1000, nem::asin<double>, std::asin, nem::DEFAULT_TRIG_EPSILON);
}

TEST(AsinAcos, Identity)
{
    const float x = 0.42f;
    const float result = nem::asin(x) + nem::acos(x);

    ASSERT_NEAR(result, nem::HALF_PI<float>, nem::DEFAULT_TRIG_EPSILON);
}