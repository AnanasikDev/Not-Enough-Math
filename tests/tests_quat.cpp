#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#define GLM_FORCE_QUAT_DATA_WXYZ
#include <glm/gtx/quaternion.hpp>
#include "nem.hpp"
#include "quat.hpp"
#include "quat_utils.hpp"

static constexpr float kEps = 1e-4f;

static constexpr float FNAN = std::numeric_limits<float>::quiet_NaN();
static constexpr float FMAX = std::numeric_limits<float>::max();

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
// quat initialization
// ===========================================================================

TEST(QuatInit, DefaultSameAsGlm)
{
    nem::quatr q1;
    glm::quat  q2(0, 0, 0, 0);

    ASSERT_NEAR(q1.s, q2.w, kEps);
    ASSERT_NEAR(q1.x, q2.x, kEps);
    ASSERT_NEAR(q1.y, q2.y, kEps);
    ASSERT_NEAR(q1.z, q2.z, kEps);
}

TEST(QuatInit, ComponentsSameAsGlm)
{
    float s = 1, x = 2, y = 3, z = 4;
    nem::quatr q1 = nem::make_quat<float>(s, x, y, z);
    glm::quat  q2(s, x, y, z);

    ASSERT_NEAR(q1.s, q2.w, kEps);
    ASSERT_NEAR(q1.x, q2.x, kEps);
    ASSERT_NEAR(q1.y, q2.y, kEps);
    ASSERT_NEAR(q1.z, q2.z, kEps);
}

TEST(QuatInit, MemoryOrderSameAsGlm)
{
    float s = 1, x = 2, y = 3, z = 4;
    nem::quat<float> q1 = nem::make_quat<float>(s, x, y, z);
    glm::quat  q2(s, x, y, z);

    float* q1p = reinterpret_cast<float*>(&q1);
    float* q2p = reinterpret_cast<float*>(&q2);

    ASSERT_NEAR(q1p[0], q2p[0], kEps);
    ASSERT_NEAR(q1p[1], q2p[1], kEps);
    ASSERT_NEAR(q1p[2], q2p[2], kEps);
    ASSERT_NEAR(q1p[3], q2p[3], kEps);
}

TEST(QuatMul, Mul)
{
    float s1 = 1, x1 = 2, y1 = -3, z1 = 4;
    float s2 = 9, x2 = -7, y2 = 5, z2 = -11;

    nem::quatr q11 = nem::make_quat<float>(s1, x1, y1, z1);
    nem::quatr q12 = nem::make_quat<float>(s2, x2, y2, z2);
    nem::quatr q1m1 = q11 * q12;
    nem::quatr q1m2 = q12 * q11;

    ASSERT_NEAR(q1m1.s, 82,  kEps);
    ASSERT_NEAR(q1m1.x, 24,  kEps);
    ASSERT_NEAR(q1m1.y, -28, kEps);
    ASSERT_NEAR(q1m1.z, 14,  kEps);

    ASSERT_NEAR(q1m2.s, 82,  kEps);
    ASSERT_NEAR(q1m2.x, -2,  kEps);
    ASSERT_NEAR(q1m2.y, -16, kEps);
    ASSERT_NEAR(q1m2.z, 36,  kEps);
}

TEST(QuatMul, MulSameAsGlm)
{
    float s1 = 1, x1 = 2, y1 = 3, z1 = 4;
    float s2 = 0.5f, x2 = 7, y2 = 13, z2 = -5;

    nem::quatr q11 = nem::make_quat<float>(s1, x1, y1, z1);
    nem::quatr q12 = nem::make_quat<float>(s2, x2, y2, z2);
    nem::quatr q1m1 = q11 * q12;
    nem::quatr q1m2 = q12 * q11;

    glm::quat  q21(s1, x1, y1, z1);
    glm::quat  q22(s2, x2, y2, z2);
    glm::quat  q2m1 = q21 * q22;
    glm::quat  q2m2 = q22 * q21;

    ASSERT_NEAR(q1m1.s, q2m1.w, kEps);
    ASSERT_NEAR(q1m1.x, q2m1.x, kEps);
    ASSERT_NEAR(q1m1.y, q2m1.y, kEps);
    ASSERT_NEAR(q1m1.z, q2m1.z, kEps);

    ASSERT_NEAR(q1m2.s, q2m2.w, kEps);
    ASSERT_NEAR(q1m2.x, q2m2.x, kEps);
    ASSERT_NEAR(q1m2.y, q2m2.y, kEps);
    ASSERT_NEAR(q1m2.z, q2m2.z, kEps);
}