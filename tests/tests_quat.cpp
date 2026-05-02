#include "common.h"

#include <cmath>
#include <limits>
#include <glm/gtx/quaternion.hpp>
#include "quat.hpp"
#include "quat_utils.hpp"

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

using namespace nem_tests;

#define REQUIRE_EQ(a, b) REQUIRE_THAT(a, WithinAbs(b, kEps));

TEST_CASE("quat::init default same as glm")
{
    nem::quatr q0;
    glm::quat  q1(0,0,0,0);

    REQUIRE_EQ(q0.s, q1.x);
    REQUIRE_EQ(q0.x, q1.y);
    REQUIRE_EQ(q0.y, q1.z);
    REQUIRE_EQ(q0.z, q1.w);
}

TEST_CASE("quat::init same as glm")
{
    float s = 1, x = 2, y = 3, z = 4;
    nem::quatr q0 = nem::make_quat<float>(s, x, y, z);
    glm::quat  q1(s, x, y, z);

    REQUIRE_EQ(q0.s, q1.x);
    REQUIRE_EQ(q0.x, q1.y);
    REQUIRE_EQ(q0.y, q1.z);
    REQUIRE_EQ(q0.z, q1.w);
}

TEST_CASE("quat::order same as glm")
{
    float s = 1, x = 2, y = 3, z = 4;
    nem::quat<float> q0 = nem::make_quat<float>(s, x, y, z);
    glm::quat  q1(s, x, y, z);

    float* q0p = reinterpret_cast<float*>(&q0);
    float* q1p = reinterpret_cast<float*>(&q1);

    REQUIRE_EQ(q0p[0], q1p[0]);
    REQUIRE_EQ(q0p[1], q1p[1]);
    REQUIRE_EQ(q0p[2], q1p[2]);
    REQUIRE_EQ(q0p[3], q1p[3]);
}