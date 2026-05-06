#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include "nem.hpp"

static constexpr float  kEps = 1e-4f;
static constexpr double kEpsD = 1e-9;

using nem::float2;
using nem::float3;
using nem::float4;
using nem::mat2;
using nem::mat3;
using nem::mat4;

// ===========================================================================
// Test helpers
// ===========================================================================

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

TEST(MatrixIndex, ChainInitListThenAt)
{
    mat3 m({ 
            { 0,  1,  4}, 
            { 9, 16, 25}, 
            {36, 49, 64} });

    EXPECT_NEAR(m.at_r(0), 0, kEps);
    EXPECT_NEAR(m.at_r(1), 1, kEps);
    EXPECT_NEAR(m.at_r(2), 4, kEps);
    EXPECT_NEAR(m.at_r(3), 9, kEps);
    EXPECT_NEAR(m.at_r(4), 16, kEps);
    EXPECT_NEAR(m.at_r(5), 25, kEps);
    EXPECT_NEAR(m.at_r(6), 36, kEps);
    EXPECT_NEAR(m.at_r(7), 49, kEps);
    EXPECT_NEAR(m.at_r(8), 64, kEps);

    EXPECT_NEAR(m.at_rw(0), 0, kEps);
    EXPECT_NEAR(m.at_rw(1), 1, kEps);
    EXPECT_NEAR(m.at_rw(2), 4, kEps);
    EXPECT_NEAR(m.at_rw(3), 9, kEps);
    EXPECT_NEAR(m.at_rw(4), 16, kEps);
    EXPECT_NEAR(m.at_rw(5), 25, kEps);
    EXPECT_NEAR(m.at_rw(6), 36, kEps);
    EXPECT_NEAR(m.at_rw(7), 49, kEps);
    EXPECT_NEAR(m.at_rw(8), 64, kEps);
}

TEST(MatrixIndex, ChainInitListThenIndex)
{
    mat3 m({
            { 0,  1,  4},
            { 9, 16, 25},
            {36, 49, 64} });

    EXPECT_NEAR(*m[0], 0, kEps);
    EXPECT_NEAR(*m[1], 9, kEps);
    EXPECT_NEAR(*m[2], 36, kEps);
}

TEST(MatrixIndex, ChainInitListThenCheckAddress)
{
    mat3 m({
            { 0,  1,  4},
            { 9, 16, 25},
            {36, 49, 64} });

    EXPECT_TRUE(&m[0][0] == &m.at_r(0));
    EXPECT_TRUE(&m[0][1] == &m.at_r(1));
    EXPECT_TRUE(&m[0][2] == &m.at_r(2));
    EXPECT_TRUE(&m[1][0] == &m.at_r(3));
    EXPECT_TRUE(&m[1][1] == &m.at_r(4));
    EXPECT_TRUE(&m[1][2] == &m.at_r(5));
    EXPECT_TRUE(&m[2][0] == &m.at_r(6));
    EXPECT_TRUE(&m[2][1] == &m.at_r(7));
    EXPECT_TRUE(&m[2][2] == &m.at_r(8));
}

TEST(MatrixIndex, ChainInitListThenDoubleIndex)
{
    mat3 m({
            { 0,  1,  4},
            { 9, 16, 25},
            {36, 49, 64} });

    EXPECT_NEAR(m[0][0], 0, kEps);
    EXPECT_NEAR(m[0][1], 1, kEps);
    EXPECT_NEAR(m[0][2], 4, kEps);
    EXPECT_NEAR(m[1][0], 9, kEps);
    EXPECT_NEAR(m[1][1], 16, kEps);
    EXPECT_NEAR(m[1][2], 25, kEps);
    EXPECT_NEAR(m[2][0], 36, kEps);
    EXPECT_NEAR(m[2][1], 49, kEps);
    EXPECT_NEAR(m[2][2], 64, kEps);
}

TEST(MatrixUpscale, ChainInitListThen2x2To3x3)
{
    mat2 src({ {3, 4}, {8, 9} });

    mat3 dst = nem::upscale<float, 2, 2, 3, 3>(src);

    EXPECT_NEAR(dst[0][0], 3, kEps);
    EXPECT_NEAR(dst[0][1], 4, kEps);
    EXPECT_NEAR(dst[0][2], 0, kEps);
    EXPECT_NEAR(dst[1][0], 8, kEps);
    EXPECT_NEAR(dst[1][1], 9, kEps);
    EXPECT_NEAR(dst[1][2], 0, kEps);
    EXPECT_NEAR(dst[2][0], 0, kEps);
    EXPECT_NEAR(dst[2][1], 0, kEps);
    EXPECT_NEAR(dst[2][2], 0, kEps);
}