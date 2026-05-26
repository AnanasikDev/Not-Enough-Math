#include "tests_common.hpp"

#include <limits>

using nem::float2;
using nem::float3;
using nem::float4;

// ===========================================================================
// sqrLength
// ===========================================================================

TEST(VectorSqrLength, ZeroVectorYieldsZero)
{
    float3 input;

    float result = nem::sqrLength(input);

    ASSERT_NEAR(result, 0.f, fEps);
}

TEST(VectorSqrLength, NegativeComponentsSquarePositive)
{
    float3 input(-3.f, -4.f, 0.f);

    float result = nem::sqrLength(input);

    ASSERT_NEAR(result, 25.f, fEps);
}

TEST(VectorSqrLength, SingleAxisX)
{
    float3 input(7.f, 0.f, 0.f);

    float result = nem::sqrLength(input);

    ASSERT_NEAR(result, 49.f, fEps);
}

TEST(VectorSqrLength, SingleAxisZNegative)
{
    float3 input(0.f, 0.f, -5.f);

    float result = nem::sqrLength(input);

    ASSERT_NEAR(result, 25.f, fEps);
}

TEST(VectorSqrLength, GeneralThreeComponent)
{
    float3 input(1.f, 2.f, 1.f);

    float result = nem::sqrLength(input);

    ASSERT_NEAR(result, 6.f, fEps);
}

TEST(VectorSqrLength, MixedSignThreeComponent)
{
    float3 input(-1.f, 2.f, -1.f);

    float result = nem::sqrLength(input);

    ASSERT_NEAR(result, 6.f, fEps);
}

// ===========================================================================
// length
// ===========================================================================

TEST(VectorLength, PythagoreanQuadruple3_4_12_13)
{
    float3 input(3.f, 4.f, 12.f);

    float result = nem::length(input);

    ASSERT_NEAR(result, 13.f, fEps);
}

TEST(VectorLength, Float2Triangle3_4_5)
{
    float2 input(3.f, 4.f);

    float result = nem::length(input);

    ASSERT_NEAR(result, 5.f, fEps);
}

TEST(VectorLength, Float4SingleWComponent)
{
    float4 input(0.f, 0.f, 0.f, 1.f);

    float result = nem::length(input);

    ASSERT_NEAR(result, 1.f, fEps);
}

// ===========================================================================
// normalize
// ===========================================================================

TEST(VectorNormalize, ZeroVectorYieldsInvalidResult)
{
    float3 input;

    float3 result = nem::normalize(input);
    std::cout << "Vector is : " << result << "\n";

    ASSERT_TRUE(IS_SAFE_INVALID(result));
}

TEST(VectorNormalize, BelowEpsilonThresholdYieldsInvalidResult)
{
    float3 input(1e-7f, 0.f, 0.f);

    float3 result = nem::normalize(input);
    std::cout << "Vector is : " << result << "\n";

    ASSERT_TRUE(IS_SAFE_INVALID(result));
}

TEST(VectorNormalize, AboveEpsilonThresholdYieldsUnitVector)
{
    float3 input(1e-3f, 0.f, 0.f);

    float3 result = nem::normalize(input);

    ASSERT_NEAR(result.x, 1.f, fEps);
    ASSERT_NEAR(result.y, 0.f, fEps);
    ASSERT_NEAR(result.z, 0.f, fEps);
}

TEST(VectorNormalize, UnitVectorIsIdempotent)
{
    float3 input(1.f, 0.f, 0.f);

    float3 result = nem::normalize(input);

    ASSERT_NEAR(result.x, 1.f, fEps);
}

TEST(VectorNormalize, DoubleNormalizeIsStable)
{
    float3 input(3.f, 4.f, 5.f);

    float3 first = nem::normalize(input);
    float3 second = nem::normalize(first);

    ASSERT_NEAR(first.x, second.x, fEps);
    ASSERT_NEAR(first.y, second.y, fEps);
    ASSERT_NEAR(first.z, second.z, fEps);
}

TEST(VectorNormalize, PreservesNegativeDirection)
{
    float3 input(-5.f, 0.f, 0.f);

    float3 result = nem::normalize(input);

    ASSERT_NEAR(result.x, -1.f, fEps);
}

// ===========================================================================
// is_zero (vector)
// ===========================================================================

TEST(VectorIsNearlyZero, JustBelowThresholdPasses)
{
    float3 input(9.9e-7f, -9.9e-7f, 0.f);

    bool result = nem::is_zero(input);

    ASSERT_TRUE(result);
}

TEST(VectorIsNearlyZero, AtThresholdFailsStrictLessThan)
{
    float3 input(1e-6f, 0.f, 0.f);

    bool result = nem::is_zero(input);

    ASSERT_FALSE(result);
}

TEST(VectorIsNearlyZero, JustAboveThresholdFails)
{
    float3 input(1.1e-6f, 0.f, 0.f);

    bool result = nem::is_zero(input);

    ASSERT_FALSE(result);
}

TEST(VectorIsNearlyZero, NaNIsNotNearZero)
{
    float3 input(FNAN, 0.f, 0.f);

    bool result = nem::is_zero(input);

    ASSERT_FALSE(result);
}

TEST(VectorIsNearlyZero, NegativeZeroPasses)
{
    float3 input(-0.f, -0.f, -0.f);

    bool result = nem::is_zero(input);

    ASSERT_TRUE(result);
}

// ===========================================================================
// orthogonal_3d_basis
// ===========================================================================

TEST(VectorBasis, ZeroVectorRejected)
{
    float3 b1, b2;

    bool result = nem::orthogonal_3d_basis(float3(), b1, b2);

    ASSERT_FALSE(result);
}

TEST(VectorBasis, NearZeroVectorRejected)
{
    float3 input(1e-7f, 0.f, 0.f);
    float3 b1, b2;

    bool result = nem::orthogonal_3d_basis(input, b1, b2);

    ASSERT_FALSE(result);
}

TEST(VectorBasis, PositiveXAxis)
{
    float3 n(1.f, 0.f, 0.f);
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    ASSERT_TRUE(ok);
    require_valid_basis(n, b1, b2);
}

TEST(VectorBasis, NegativeXAxis)
{
    float3 n(-1.f, 0.f, 0.f);
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    ASSERT_TRUE(ok);
    require_valid_basis(n, b1, b2);
}

TEST(VectorBasis, PositiveYAxis)
{
    float3 n(0.f, 1.f, 0.f);
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    ASSERT_TRUE(ok);
    require_valid_basis(n, b1, b2);
}

TEST(VectorBasis, NegativeYAxis)
{
    float3 n(0.f, -1.f, 0.f);
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    ASSERT_TRUE(ok);
    require_valid_basis(n, b1, b2);
}

TEST(VectorBasis, PositiveZAxis)
{
    float3 n(0.f, 0.f, 1.f);
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    ASSERT_TRUE(ok);
    require_valid_basis(n, b1, b2);
}

TEST(VectorBasis, NegativeZAxis)
{
    float3 n(0.f, 0.f, -1.f);
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    ASSERT_TRUE(ok);
    require_valid_basis(n, b1, b2);
}

TEST(VectorBasis, ZComponentBelowBranchThreshold)
{
    float3 n = nem::normalize(float3(0.063f, 0.f, 0.998f));
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    ASSERT_TRUE(ok);
    require_valid_basis(n, b1, b2);
}

TEST(VectorBasis, ZComponentAboveBranchThreshold)
{
    float3 n = nem::normalize(float3(0.001f, 0.f, 0.9999f));
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    ASSERT_TRUE(ok);
    require_valid_basis(n, b1, b2);
}

TEST(VectorBasis, NegativeZAboveBranchThreshold)
{
    float3 n = nem::normalize(float3(0.001f, 0.f, -0.9999f));
    float3 b1, b2;

    bool ok = nem::orthogonal_3d_basis(n, b1, b2);

    ASSERT_TRUE(ok);
    require_valid_basis(n, b1, b2);
}

// ===========================================================================
// horizontal_sum
// ===========================================================================

TEST(VectorHorizontalSum, ZeroVectorYieldsZero)
{
    float3 input;

    float result = nem::horizontal_sum(input);

    ASSERT_NEAR(result, 0.f, fEps);
}

TEST(VectorHorizontalSum, Float4GeneralCase)
{
    float4 input(1.f, 2.f, 3.f, 4.f);

    float result = nem::horizontal_sum(input);

    ASSERT_NEAR(result, 10.f, fEps);
}

// ===========================================================================
// horizontal_mul
// ===========================================================================

TEST(VectorHorizontalMul, OneZeroComponentYieldsZero)
{
    float3 input(1.f, 2.f, 0.f);

    float result = nem::horizontal_mul(input);

    ASSERT_NEAR(result, 0.f, fEps);
}

TEST(VectorHorizontalMul, MiddleZeroComponentYieldsZero)
{
    float3 input(5.f, 0.f, 5.f);

    float result = nem::horizontal_mul(input);

    ASSERT_NEAR(result, 0.f, fEps);
}

TEST(VectorHorizontalMul, AllOnesYieldsOne)
{
    float4 input(1.f, 1.f, 1.f, 1.f);

    float result = nem::horizontal_mul(input);

    ASSERT_NEAR(result, 1.f, fEps);
}

// ===========================================================================
// dot
// ===========================================================================

TEST(VectorDot, SelfEqualsSqrLength)
{
    float3 v(-7.f, 11.f, -13.f);

    float result = nem::dot(v, v);

    ASSERT_NEAR(result, nem::sqrLength(v), fEps);
}

TEST(VectorDot, WithZeroVectorYieldsZero)
{
    float3 a(FMAX, FMAX, FMAX);
    float3 b;

    float result = nem::dot(a, b);

    ASSERT_NEAR(result, 0.f, fEps);
}

TEST(VectorDot, CommutativityHolds)
{
    float3 a(1.5f, -2.7f, 3.9f);
    float3 b(-4.1f, 5.3f, -6.5f);

    float ab = nem::dot(a, b);
    float ba = nem::dot(b, a);

    ASSERT_NEAR(ab, ba, fEps);
}

TEST(VectorDot, OrthogonalFloat2YieldsZero)
{
    float2 a(0.f, 1.f);
    float2 b(1.f, 0.f);

    float result = nem::dot(a, b);

    ASSERT_NEAR(result, 0.f, fEps);
}

TEST(VectorDot, AntiParallelFloat2YieldsNegativeOne)
{
    float2 a(0.f, 1.f);
    float2 b(0.f, -1.f);

    float result = nem::dot(a, b);

    ASSERT_NEAR(result, -1.f, fEps);
}

TEST(VectorDot, ParallelFloat2YieldsOne)
{
    float2 a(0.f, 1.f);
    float2 b(0.f, 1.f);

    float result = nem::dot(a, b);

    ASSERT_NEAR(result, 1.f, fEps);
}

// ===========================================================================
// cross
// ===========================================================================

TEST(VectorCross, WithZeroVectorYieldsZero)
{
    float3 a(1.f, 2.f, 3.f);
    float3 b;

    float3 result = nem::cross(a, b);

    ASSERT_NEAR(result.x, 0.f, fEps);
    ASSERT_NEAR(result.y, 0.f, fEps);
    ASSERT_NEAR(result.z, 0.f, fEps);
}

TEST(VectorCross, BothZeroYieldsZero)
{
    float3 a;
    float3 b;

    float3 result = nem::cross(a, b);

    ASSERT_NEAR(nem::length(result), 0.f, fEps);
}

TEST(VectorCross, NearlyParallelVectorsYieldNearZeroMagnitude)
{
    float3 a(1.f, 0.f, 0.f);
    float3 b(1.f, 1e-7f, 0.f);

    float3 result = nem::cross(a, b);

    ASSERT_LT(nem::length(result), 1e-6f);
}

TEST(VectorCross, ResultIsPerpendicularToBothInputs)
{
    float3 a(2.f, -3.f, 7.f);
    float3 b(-1.f, 4.f, 5.f);

    float3 result = nem::cross(a, b);

    ASSERT_NEAR(nem::dot(result, a), 0.f, fEps);
    ASSERT_NEAR(nem::dot(result, b), 0.f, fEps);
}

TEST(VectorCross, PerpendicularInputsHaveMagnitudeProduct)
{
    float3 a(3.f, 0.f, 0.f);
    float3 b(0.f, 5.f, 0.f);

    float3 result = nem::cross(a, b);
    float expected = nem::length(a) * nem::length(b);
    float actual = nem::length(result);

    ASSERT_NEAR(actual, expected, fEps);
}

// ===========================================================================
// compound assignment
// ===========================================================================

TEST(VectorCompoundAssign, PlusEqualsReturnsReferenceToSelf)
{
    float3 a(1.f, 2.f, 3.f);
    float3 b(10.f, 20.f, 30.f);

    float3& ref = (a += b);

    ASSERT_EQ(&ref, &a);
    ASSERT_NEAR(a.x, 11.f, fEps);
}

TEST(VectorCompoundAssign, MinusEqualsSelfYieldsZero)
{
    float3 a(FMAX, -FMAX, 42.f);

    a -= a;

    ASSERT_FLOAT_EQ(a.x, 0.f);
    ASSERT_FLOAT_EQ(a.y, 0.f);
    ASSERT_FLOAT_EQ(a.z, 0.f);
}

TEST(VectorCompoundAssign, DivEqualsSelfYieldsOnes)
{
    float3 a(7.f, -3.f, 0.5f);

    a /= a;

    ASSERT_NEAR(a.x, 1.f, fEps);
    ASSERT_NEAR(a.y, 1.f, fEps);
    ASSERT_NEAR(a.z, 1.f, fEps);
}

TEST(VectorCompoundAssign, MulEqualsReturnsReferenceToSelf)
{
    float3 a(1.f, 2.f, 3.f);
    float3 b(2.f);

    float3& ref = (a *= b);

    ASSERT_EQ(&ref, &a);
}

// ===========================================================================
// round-trip chains
// ===========================================================================

TEST(VectorChain, AddThenSubtractRecoversOriginal)
{
    float3 a(1.23456f, -7.89012f, 3.45678f);
    float3 b(9.87654f, 3.21098f, -6.54321f);

    float3 result = (a + b) - b;

    ASSERT_NEAR(result.x, a.x, fEps);
    ASSERT_NEAR(result.y, a.y, fEps);
    ASSERT_NEAR(result.z, a.z, fEps);
}

TEST(VectorChain, MultiplyThenDivideRecoversOriginal)
{
    float3 a(2.f, 3.f, 4.f);
    float3 b(5.f, 7.f, 11.f);

    float3 result = (a * b) / b;

    ASSERT_NEAR(result.x, a.x, fEps);
    ASSERT_NEAR(result.y, a.y, fEps);
    ASSERT_NEAR(result.z, a.z, fEps);
}

TEST(VectorChain, DotOfNormalizedWithItselfYieldsOne)
{
    float3 v(100.f, -200.f, 300.f);

    float3 n = nem::normalize(v);
    float result = nem::dot(n, n);

    ASSERT_NEAR(result, 1.f, fEps);
}

// ===========================================================================
// scalar broadcast
// ===========================================================================

TEST(VectorScalarBroadcast, MultiplicationScalesAllComponents)
{
    float3 v(2.f, 3.f, 4.f);

    float3 result = v * float3(5.f);

    ASSERT_NEAR(result.x, 10.f, fEps);
    ASSERT_NEAR(result.y, 15.f, fEps);
    ASSERT_NEAR(result.z, 20.f, fEps);
}

TEST(VectorScalarBroadcast, DivisionScalesAllComponents)
{
    float3 v(2.f, 3.f, 4.f);

    float3 result = v / float3(2.f);

    ASSERT_NEAR(result.x, 1.f, fEps);
    ASSERT_NEAR(result.y, 1.5f, fEps);
    ASSERT_NEAR(result.z, 2.f, fEps);
}
