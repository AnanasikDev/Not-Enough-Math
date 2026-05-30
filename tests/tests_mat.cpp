#include "tests_common.hpp"

#include <limits>

using nem::float2;
using nem::float3;
using nem::float4;
using nem::mat2;
using nem::mat3;
using nem::mat4;

// ===========================================================================

TEST(MatrixIndex, ChainInitListThenAt)
{
    mat3 m({ 
            { 0,  1,  4}, 
            { 9, 16, 25}, 
            {36, 49, 64} });

    EXPECT_NEAR(m.at_r(0), 0, fEps);
    EXPECT_NEAR(m.at_r(1), 1, fEps);
    EXPECT_NEAR(m.at_r(2), 4, fEps);
    EXPECT_NEAR(m.at_r(3), 9, fEps);
    EXPECT_NEAR(m.at_r(4), 16, fEps);
    EXPECT_NEAR(m.at_r(5), 25, fEps);
    EXPECT_NEAR(m.at_r(6), 36, fEps);
    EXPECT_NEAR(m.at_r(7), 49, fEps);
    EXPECT_NEAR(m.at_r(8), 64, fEps);

    EXPECT_NEAR(m.at_rw(0), 0, fEps);
    EXPECT_NEAR(m.at_rw(1), 1, fEps);
    EXPECT_NEAR(m.at_rw(2), 4, fEps);
    EXPECT_NEAR(m.at_rw(3), 9, fEps);
    EXPECT_NEAR(m.at_rw(4), 16, fEps);
    EXPECT_NEAR(m.at_rw(5), 25, fEps);
    EXPECT_NEAR(m.at_rw(6), 36, fEps);
    EXPECT_NEAR(m.at_rw(7), 49, fEps);
    EXPECT_NEAR(m.at_rw(8), 64, fEps);
}

TEST(MatrixIndex, ChainInitListThenIndex)
{
    mat3 m({
            { 0,  1,  4},
            { 9, 16, 25},
            {36, 49, 64} });

    EXPECT_NEAR(*m[0], 0, fEps);
    EXPECT_NEAR(*m[1], 9, fEps);
    EXPECT_NEAR(*m[2], 36, fEps);
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

    EXPECT_NEAR(m[0][0], 0, fEps);
    EXPECT_NEAR(m[0][1], 1, fEps);
    EXPECT_NEAR(m[0][2], 4, fEps);
    EXPECT_NEAR(m[1][0], 9, fEps);
    EXPECT_NEAR(m[1][1], 16, fEps);
    EXPECT_NEAR(m[1][2], 25, fEps);
    EXPECT_NEAR(m[2][0], 36, fEps);
    EXPECT_NEAR(m[2][1], 49, fEps);
    EXPECT_NEAR(m[2][2], 64, fEps);
}

TEST(MatrixUpscale, ChainInitListThen2x2To3x3)
{
    mat2 src({ {3, 4}, {8, 9} });

    mat3 dst = nem::upscale<float, 2, 2, 3, 3>(src);

    EXPECT_NEAR(dst[0][0], 3, fEps);
    EXPECT_NEAR(dst[0][1], 4, fEps);
    EXPECT_NEAR(dst[0][2], 0, fEps);
    EXPECT_NEAR(dst[1][0], 8, fEps);
    EXPECT_NEAR(dst[1][1], 9, fEps);
    EXPECT_NEAR(dst[1][2], 0, fEps);
    EXPECT_NEAR(dst[2][0], 0, fEps);
    EXPECT_NEAR(dst[2][1], 0, fEps);
    EXPECT_NEAR(dst[2][2], 0, fEps);
}

TEST(MatrixDeterminant, Simple2x2_Flip)
{
    mat2 m({ {1, 2}, {3, 4} });

    float det = nem::determinant<float>(m);

    EXPECT_NEAR(det, -2.0f, fEps);
}

TEST(MatrixDeterminant, Simple2x2)
{
    mat2 m({ {1, 1}, {-1, 1} });

    float det = nem::determinant<float>(m);

    EXPECT_NEAR(det, 2.0f, fEps);
}

TEST(MatrixRotate, Simple2x2)
{
    mat2 result = nem::rotate(90.0f);

    EXPECT_NEAR(result[0][0], 0, fEps);
    EXPECT_NEAR(result[0][1], -1, fEps);
    EXPECT_NEAR(result[1][0], 1, fEps);
    EXPECT_NEAR(result[1][1], 0, fEps);
}

TEST(MatrixRotate, Simple2x2_FullRevolution)
{
    mat2 ident({ {1, 0}, {0, 1} });

    mat2 result = nem::rotate(360.0f);

    EXPECT_NEAR(result[0][0], ident[0][0], fEps);
    EXPECT_NEAR(result[0][1], ident[0][1], fEps);
    EXPECT_NEAR(result[1][0], ident[1][0], fEps);
    EXPECT_NEAR(result[1][1], ident[1][1], fEps);
}

TEST(MatrixRotate, Simple2x2_Chain)
{
    mat2 ident({ {1, 0}, {0, 1} });

    mat2 result = nem::rotate(90.0f) * nem::rotate(90.0f);

    EXPECT_NEAR(result[0][0], -ident[0][0], fEps);
    EXPECT_NEAR(result[0][1], -ident[0][1], fEps);
    EXPECT_NEAR(result[1][0], -ident[1][0], fEps);
    EXPECT_NEAR(result[1][1], -ident[1][1], fEps);
}

TEST(MatrixScale, Simple2x2)
{
    mat2 result = nem::scale(nem::float2(0.1f, 0.2f));

    EXPECT_NEAR(result[0][0], 0.1f, fEps);
    EXPECT_NEAR(result[0][1], 0.0f, fEps);
    EXPECT_NEAR(result[1][0], 0.0f, fEps);
    EXPECT_NEAR(result[1][1], 0.2f, fEps);
}

TEST(MatrixScale, Simple3x3)
{
    mat3 result = nem::scale(nem::float3(3.0f, 0.0f, 2.0f));

    EXPECT_NEAR(result[0][0], 3.0f, fEps);
    EXPECT_NEAR(result[0][1], 0.0f, fEps);
    EXPECT_NEAR(result[0][2], 0.0f, fEps);

    EXPECT_NEAR(result[1][0], 0.0f, fEps);
    EXPECT_NEAR(result[1][1], 0.0f, fEps);
    EXPECT_NEAR(result[1][2], 0.0f, fEps);
    
    EXPECT_NEAR(result[2][0], 0.0f, fEps);
    EXPECT_NEAR(result[2][1], 0.0f, fEps);
    EXPECT_NEAR(result[2][2], 2.0f, fEps);
}

TEST(MatrixScale, Chain_3x3)
{
    mat3 result = nem::scale(nem::float3(3.0f, 0.0f, 2.0f)) * nem::scale(nem::float3(2.0f, 9.0f, 2.5f));

    EXPECT_NEAR(result[0][0], 6.0f, fEps);
    EXPECT_NEAR(result[0][1], 0.0f, fEps);
    EXPECT_NEAR(result[0][2], 0.0f, fEps);

    EXPECT_NEAR(result[1][0], 0.0f, fEps);
    EXPECT_NEAR(result[1][1], 0.0f, fEps);
    EXPECT_NEAR(result[1][2], 0.0f, fEps);
    
    EXPECT_NEAR(result[2][0], 0.0f, fEps);
    EXPECT_NEAR(result[2][1], 0.0f, fEps);
    EXPECT_NEAR(result[2][2], 5.0f, fEps);
}

TEST(MatrixTranslate, Simple3x3)
{
    mat4 result = nem::translate_3D(nem::float3(3.0f, 7.0f, 2.0f));

    EXPECT_NEAR(result[0][0], 1.0f, fEps);
    EXPECT_NEAR(result[0][1], 0.0f, fEps);
    EXPECT_NEAR(result[0][2], 0.0f, fEps);
    EXPECT_NEAR(result[0][3], 3.0f, fEps);

    EXPECT_NEAR(result[1][0], 0.0f, fEps);
    EXPECT_NEAR(result[1][1], 1.0f, fEps);
    EXPECT_NEAR(result[1][2], 0.0f, fEps);
    EXPECT_NEAR(result[1][3], 7.0f, fEps);

    EXPECT_NEAR(result[2][0], 0.0f, fEps);
    EXPECT_NEAR(result[2][1], 0.0f, fEps);
    EXPECT_NEAR(result[2][2], 1.0f, fEps);
    EXPECT_NEAR(result[2][3], 2.0f, fEps);

    EXPECT_NEAR(result[3][0], 0.0f, fEps);
    EXPECT_NEAR(result[3][1], 0.0f, fEps);
    EXPECT_NEAR(result[3][2], 0.0f, fEps);
    EXPECT_NEAR(result[3][3], 1.0f, fEps);
}

TEST(MatrixTranslate, Simple2x2)
{
    mat3 result = nem::translate_2D(nem::float2(9.0f, 2.0f));

    EXPECT_NEAR(result[0][0], 1.0f, fEps);
    EXPECT_NEAR(result[0][1], 0.0f, fEps);
    EXPECT_NEAR(result[0][2], 9.0f, fEps);

    EXPECT_NEAR(result[1][0], 0.0f, fEps);
    EXPECT_NEAR(result[1][1], 1.0f, fEps);
    EXPECT_NEAR(result[1][2], 2.0f, fEps);

    EXPECT_NEAR(result[2][0], 0.0f, fEps);
    EXPECT_NEAR(result[2][1], 0.0f, fEps);
    EXPECT_NEAR(result[2][2], 1.0f, fEps);
}