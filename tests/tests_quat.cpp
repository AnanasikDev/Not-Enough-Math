#include <limits>
#define GLM_FORCE_QUAT_DATA_WXYZ
#include <glm/gtx/quaternion.hpp>

#include "tests_common.hpp"

// ===========================================================================
// quat initialization
// ===========================================================================

TEST(QuatInit, DefaultSameAsGlm)
{
    nem::quat q1;
    glm::quat  q2(0, 0, 0, 0);

    ASSERT_NEAR(q1.s, q2.w, fEps);
    ASSERT_NEAR(q1.x, q2.x, fEps);
    ASSERT_NEAR(q1.y, q2.y, fEps);
    ASSERT_NEAR(q1.z, q2.z, fEps);
}

TEST(QuatInit, ComponentsSameAsGlm)
{
    float s = 1, x = 2, y = 3, z = 4;
    nem::quat q1 = nem::make_quat<float>(s, x, y, z);
    glm::quat  q2(s, x, y, z);

    ASSERT_NEAR(q1.s, q2.w, fEps);
    ASSERT_NEAR(q1.x, q2.x, fEps);
    ASSERT_NEAR(q1.y, q2.y, fEps);
    ASSERT_NEAR(q1.z, q2.z, fEps);
}

TEST(QuatInit, MemoryOrderSameAsGlm)
{
    float s = 1, x = 2, y = 3, z = 4;
    nem::quat_t<float> q1 = nem::make_quat<float>(s, x, y, z);
    glm::quat  q2(s, x, y, z);

    float* q1p = reinterpret_cast<float*>(&q1);
    float* q2p = reinterpret_cast<float*>(&q2);

    ASSERT_NEAR(q1p[0], q2p[0], fEps);
    ASSERT_NEAR(q1p[1], q2p[1], fEps);
    ASSERT_NEAR(q1p[2], q2p[2], fEps);
    ASSERT_NEAR(q1p[3], q2p[3], fEps);
}

TEST(QuatMul, Mul)
{
    float s1 = 1, x1 = 2, y1 = -3, z1 = 4;
    float s2 = 9, x2 = -7, y2 = 5, z2 = -11;

    nem::quat q11 = nem::make_quat<float>(s1, x1, y1, z1);
    nem::quat q12 = nem::make_quat<float>(s2, x2, y2, z2);
    nem::quat q1m1 = q11 * q12;
    nem::quat q1m2 = q12 * q11;

    ASSERT_NEAR(q1m1.s, 82,  fEps);
    ASSERT_NEAR(q1m1.x, 24,  fEps);
    ASSERT_NEAR(q1m1.y, -28, fEps);
    ASSERT_NEAR(q1m1.z, 14,  fEps);

    ASSERT_NEAR(q1m2.s, 82,  fEps);
    ASSERT_NEAR(q1m2.x, -2,  fEps);
    ASSERT_NEAR(q1m2.y, -16, fEps);
    ASSERT_NEAR(q1m2.z, 36,  fEps);
}

TEST(QuatMul, MulSameAsGlm)
{
    float s1 = 1, x1 = 2, y1 = 3, z1 = 4;
    float s2 = 0.5f, x2 = 7, y2 = 13, z2 = -5;

    nem::quat q11 = nem::make_quat<float>(s1, x1, y1, z1);
    nem::quat q12 = nem::make_quat<float>(s2, x2, y2, z2);
    nem::quat q1m1 = q11 * q12;
    nem::quat q1m2 = q12 * q11;

    glm::quat  q21(s1, x1, y1, z1);
    glm::quat  q22(s2, x2, y2, z2);
    glm::quat  q2m1 = q21 * q22;
    glm::quat  q2m2 = q22 * q21;

    ASSERT_NEAR(q1m1.s, q2m1.w, fEps);
    ASSERT_NEAR(q1m1.x, q2m1.x, fEps);
    ASSERT_NEAR(q1m1.y, q2m1.y, fEps);
    ASSERT_NEAR(q1m1.z, q2m1.z, fEps);

    ASSERT_NEAR(q1m2.s, q2m2.w, fEps);
    ASSERT_NEAR(q1m2.x, q2m2.x, fEps);
    ASSERT_NEAR(q1m2.y, q2m2.y, fEps);
    ASSERT_NEAR(q1m2.z, q2m2.z, fEps);
}

TEST(QuatExractVector, Simple)
{
    nem::quat q = nem::make_quat(1.0f, 2.0f, 3.0f, 4.0f);
    nem::float3 v = nem::extract_vector(q);

    ASSERT_NEAR(v.x, 2, fEps);
    ASSERT_NEAR(v.y, 3, fEps);
    ASSERT_NEAR(v.z, 4, fEps);
}

TEST(QuatLength, SameAsGlm)
{
    const float s = 1, x = 2, y = 3, z = 4;
    nem::quat_t<float> q1 = nem::make_quat<float>(s, x, y, z);
    glm::quat q2(s, x, y, z);

    float l1 = nem::length(q1);
    float l2 = glm::length(q2);

    ASSERT_NEAR(l1, l2, fEps);
}

TEST(QuatNormalize, SameAsGlm)
{
    const float s = 1, x = 2, y = 3, z = 4;
    nem::quat_t<float> q1 = nem::make_quat<float>(s, x, y, z);
    glm::quat q2(s, x, y, z);

    auto q1n = nem::normalize(q1);
    auto q2n = glm::normalize(q2);

    ASSERT_NEAR(q1n.s, q2n.w, fEps);
    ASSERT_NEAR(q1n.x, q2n.x, fEps);
    ASSERT_NEAR(q1n.y, q2n.y, fEps);
    ASSERT_NEAR(q1n.z, q2n.z, fEps);
}

TEST(QuatMulByVector, SameAsGlm)
{
    const nem::float3 v1(3.0f, -1.0f, 7.0f); 
    const glm::vec3   v2(3.0f, -1.0f, 7.0f); 
    const float s = 1, x = 2, y = 3, z = 4;
    nem::quat_t<float> q1 = nem::make_quat<float>(s, x, y, z);
    glm::quat q2(s, x, y, z);

    nem::float3 v1r = q1 * v1;
    glm::vec3 v2r = q2 * v2;

    ASSERT_NEAR(v1r[0], v2r[0], fEps);
    ASSERT_NEAR(v1r[1], v2r[1], fEps);
    ASSERT_NEAR(v1r[2], v2r[2], fEps);
}