#include "tests_common.hpp"
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"
#include "glm/mat3x3.hpp"

#include <limits>

using nem::float2;
using nem::float3;
using nem::float4;
using nem::mat2;
using nem::mat3;
using nem::mat4;

// ===========================================================================

TEST(MatrixIndex, OperatorBracketIsColumnMajor)
{
    // written row-by-row, as it reads on paper
    mat3 m({
            { 0,  1,  4},
            { 9, 16, 25},
            {36, 49, 64} });

    // m[c][r]: column c, row r
    EXPECT_NEAR(m[0][0], 0, fEps);
    EXPECT_NEAR(m[0][1], 9, fEps);
    EXPECT_NEAR(m[0][2], 36, fEps);
    EXPECT_NEAR(m[1][0], 1, fEps);
    EXPECT_NEAR(m[1][1], 16, fEps);
    EXPECT_NEAR(m[1][2], 49, fEps);
    EXPECT_NEAR(m[2][0], 4, fEps);
    EXPECT_NEAR(m[2][1], 25, fEps);
    EXPECT_NEAR(m[2][2], 64, fEps);
}

TEST(MatrixIndex, AtMatchesRowMajorLiteral)
{
    mat3 m({
            { 0,  1,  4},
            { 9, 16, 25},
            {36, 49, 64} });

    EXPECT_NEAR(m.at(0, 0), 0, fEps);
    EXPECT_NEAR(m.at(1, 0), 9, fEps);
    EXPECT_NEAR(m.at(2, 0), 36, fEps);
    EXPECT_NEAR(m.at(2, 1), 49, fEps);
}

TEST(MatrixIndex, AtAndOperatorBracketAgree)
{
    mat3 m({
            { 0,  1,  4},
            { 9, 16, 25},
            {36, 49, 64} });

    for (size_t r = 0; r < 3; ++r)
    {
        for (size_t c = 0; c < 3; ++c)
        {
            EXPECT_TRUE(&m.at(r, c) == &m[c][r]);
        }
    }
}

TEST(MatrixIndex, StorageIsColumnMajor)
{
    mat3 m({
            { 0,  1,  4},
            { 9, 16, 25},
            {36, 49, 64} });

    // each column is contiguous in memory
    EXPECT_NEAR(m.item(0), 0, fEps);
    EXPECT_NEAR(m.item(1), 9, fEps);
    EXPECT_NEAR(m.item(2), 36, fEps);
    EXPECT_NEAR(m.item(3), 1, fEps);
    EXPECT_NEAR(m.item(4), 16, fEps);
    EXPECT_NEAR(m.item(5), 49, fEps);
    EXPECT_NEAR(m.item(6), 4, fEps);
    EXPECT_NEAR(m.item(7), 25, fEps);
    EXPECT_NEAR(m.item(8), 64, fEps);
}

TEST(MatrixInit, SameAsGLM3x3)
{
    // GLM's flat constructor fills columns first; transpose recovers the
    // matrix as it reads row-by-row above, so it can be compared directly
    // against nem's row-major initializer-list syntax.
    glm::mat3x3 glm_m(0, 1, 4, 9, 16, 25, 36, 49, 64);
    glm_m = glm::transpose(glm_m);

    mat3 m({{0, 1, 4}, {9, 16, 25}, {36, 49, 64}});

    for (int c = 0; c < 3; ++c)
    {
        for (int r = 0; r < 3; ++r)
        {
            EXPECT_NEAR(m[c][r], glm_m[c][r], fEps);
            EXPECT_NEAR(m.at(r, c), glm_m[c][r], fEps);
        }
    }
}

TEST(MatrixInit, SameAsGLM4x4)
{
    glm::mat4x4 glm_mat = {3, -7, 11, 2,
                        5, -8, 231, -29,
                        16, 33, -91, -72,
                        100, 102, -92, 32};
    glm_mat = glm::transpose(glm_mat);

    nem::mat4 nem_mat({{3, -7, 11, 2},
                       {5, -8, 231, -29},
                       {16, 33, -91, -72},
                       {100, 102, -92, 32}});

    for (int c = 0; c < 4; ++c)
    {
        for (int r = 0; r < 4; ++r)
        {
            EXPECT_NEAR(nem_mat[c][r], glm_mat[c][r], fEps);
            EXPECT_NEAR(nem_mat.at(r, c), glm_mat[c][r], fEps);
        }
    }
}

TEST(MatrixUpscale, ChainInitListThen2x2To3x3)
{
    mat2 src({ {3, 4}, {8, 9} });

    mat3 dst = nem::upscale<float, 2, 2, 3, 3>(src);

    EXPECT_NEAR(dst.at(0, 0), 3, fEps);
    EXPECT_NEAR(dst.at(0, 1), 4, fEps);
    EXPECT_NEAR(dst.at(0, 2), 0, fEps);
    EXPECT_NEAR(dst.at(1, 0), 8, fEps);
    EXPECT_NEAR(dst.at(1, 1), 9, fEps);
    EXPECT_NEAR(dst.at(1, 2), 0, fEps);
    EXPECT_NEAR(dst.at(2, 0), 0, fEps);
    EXPECT_NEAR(dst.at(2, 1), 0, fEps);
    EXPECT_NEAR(dst.at(2, 2), 0, fEps);
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
    mat2 result = nem::rotate(nem::degrees(90.0f));

    EXPECT_NEAR(result.at(0, 0), 0, fEps);
    EXPECT_NEAR(result.at(0, 1), -1, fEps);
    EXPECT_NEAR(result.at(1, 0), 1, fEps);
    EXPECT_NEAR(result.at(1, 1), 0, fEps);
}

TEST(MatrixRotate, Simple2x2_FullRevolution)
{
    mat2 ident({ {1, 0}, {0, 1} });

    mat2 result = nem::rotate(nem::degrees(360.0f));

    for (int r = 0; r < 2; ++r)
    {
        for (int c = 0; c < 2; ++c)
        {
            EXPECT_NEAR(result.at(r, c), ident.at(r, c), fEps);
        }
    }
}

TEST(MatrixRotate, Simple2x2_Chain)
{
    mat2 ident({ {1, 0}, {0, 1} });

    mat2 result = nem::rotate(nem::degrees(90.0f)) * nem::rotate(nem::degrees(90.0f));

    for (int r = 0; r < 2; ++r)
    {
        for (int c = 0; c < 2; ++c)
        {
            EXPECT_NEAR(result.at(r, c), -ident.at(r, c), fEps);
        }
    }
}

TEST(MatrixScale, Simple2x2)
{
    mat2 result = nem::scale(nem::float2(0.1f, 0.2f));

    EXPECT_NEAR(result.at(0, 0), 0.1f, fEps);
    EXPECT_NEAR(result.at(0, 1), 0.0f, fEps);
    EXPECT_NEAR(result.at(1, 0), 0.0f, fEps);
    EXPECT_NEAR(result.at(1, 1), 0.2f, fEps);
}

TEST(MatrixScale, Simple3x3)
{
    mat3 result = nem::scale(nem::float3(3.0f, 0.0f, 2.0f));

    EXPECT_NEAR(result.at(0, 0), 3.0f, fEps);
    EXPECT_NEAR(result.at(0, 1), 0.0f, fEps);
    EXPECT_NEAR(result.at(0, 2), 0.0f, fEps);
    EXPECT_NEAR(result.at(1, 0), 0.0f, fEps);
    EXPECT_NEAR(result.at(1, 1), 0.0f, fEps);
    EXPECT_NEAR(result.at(1, 2), 0.0f, fEps);
    EXPECT_NEAR(result.at(2, 0), 0.0f, fEps);
    EXPECT_NEAR(result.at(2, 1), 0.0f, fEps);
    EXPECT_NEAR(result.at(2, 2), 2.0f, fEps);
}

TEST(MatrixScale, Chain_3x3)
{
    mat3 result = nem::scale(nem::float3(3.0f, 0.0f, 2.0f)) * nem::scale(nem::float3(2.0f, 9.0f, 2.5f));

    EXPECT_NEAR(result.at(0, 0), 6.0f, fEps);
    EXPECT_NEAR(result.at(0, 1), 0.0f, fEps);
    EXPECT_NEAR(result.at(0, 2), 0.0f, fEps);
    EXPECT_NEAR(result.at(1, 0), 0.0f, fEps);
    EXPECT_NEAR(result.at(1, 1), 0.0f, fEps);
    EXPECT_NEAR(result.at(1, 2), 0.0f, fEps);
    EXPECT_NEAR(result.at(2, 0), 0.0f, fEps);
    EXPECT_NEAR(result.at(2, 1), 0.0f, fEps);
    EXPECT_NEAR(result.at(2, 2), 5.0f, fEps);
}

TEST(MatrixTranslate, Simple3x3)
{
    mat4 result = nem::translate_3D(nem::float3(3.0f, 7.0f, 2.0f));

    EXPECT_NEAR(result.at(0, 0), 1.0f, fEps);
    EXPECT_NEAR(result.at(0, 1), 0.0f, fEps);
    EXPECT_NEAR(result.at(0, 2), 0.0f, fEps);
    EXPECT_NEAR(result.at(0, 3), 3.0f, fEps);
    EXPECT_NEAR(result.at(1, 0), 0.0f, fEps);
    EXPECT_NEAR(result.at(1, 1), 1.0f, fEps);
    EXPECT_NEAR(result.at(1, 2), 0.0f, fEps);
    EXPECT_NEAR(result.at(1, 3), 7.0f, fEps);
    EXPECT_NEAR(result.at(2, 0), 0.0f, fEps);
    EXPECT_NEAR(result.at(2, 1), 0.0f, fEps);
    EXPECT_NEAR(result.at(2, 2), 1.0f, fEps);
    EXPECT_NEAR(result.at(2, 3), 2.0f, fEps);
    EXPECT_NEAR(result.at(3, 0), 0.0f, fEps);
    EXPECT_NEAR(result.at(3, 1), 0.0f, fEps);
    EXPECT_NEAR(result.at(3, 2), 0.0f, fEps);
    EXPECT_NEAR(result.at(3, 3), 1.0f, fEps);
}

TEST(MatrixTranslate, Simple2x2)
{
    mat3 result = nem::translate_2D(nem::float2(9.0f, 2.0f));

    EXPECT_NEAR(result.at(0, 0), 1.0f, fEps);
    EXPECT_NEAR(result.at(0, 1), 0.0f, fEps);
    EXPECT_NEAR(result.at(0, 2), 9.0f, fEps);
    EXPECT_NEAR(result.at(1, 0), 0.0f, fEps);
    EXPECT_NEAR(result.at(1, 1), 1.0f, fEps);
    EXPECT_NEAR(result.at(1, 2), 2.0f, fEps);
    EXPECT_NEAR(result.at(2, 0), 0.0f, fEps);
    EXPECT_NEAR(result.at(2, 1), 0.0f, fEps);
    EXPECT_NEAR(result.at(2, 2), 1.0f, fEps);
}

TEST(MatrixTransform, TRS)
{
    mat4 result = nem::transform(nem::float3(1, 2, 3), nem::from_axis_angle(nem::float3(1, 1, 1), nem::degrees(45.0f)), nem::float3(1, 1, 1));

    std::cout << "TRS: \n" << result << std::endl;
}

TEST(MatrixVectorMul, SameAsGLM4x4)
{
    glm::mat4x4 glm_mat = {3, -7, 11, 2,
                        5, -8, 231, -29,
                        16, 33, -91, -72,
                        100, 102, -92, 32};
    glm_mat = glm::transpose(glm_mat);
    nem::mat4 nem_mat({{3, -7, 11, 2},
                       {5, -8, 231, -29},
                       {16, 33, -91, -72},
                       {100, 102, -92, 32}});

    glm::vec4 glm_vec = {5, -2, 7, 12};
    nem::float4 nem_vec(5.f, -2.f, 7.f, 12.f);

    glm::vec4 glm_result = glm_mat * glm_vec;
    nem::float4 nem_result = nem_mat * nem_vec;

    EXPECT_NEAR(nem_result[0], glm_result[0], fEps);
    EXPECT_NEAR(nem_result[1], glm_result[1], fEps);
    EXPECT_NEAR(nem_result[2], glm_result[2], fEps);
    EXPECT_NEAR(nem_result[3], glm_result[3], fEps);
}

TEST(MatrixFromQuat, MatchesQuatVectorRotation)
{
    nem::quat q = nem::normalize(nem::make_quat<float>(1.0f, 2.0f, 3.0f, 4.0f));
    nem::mat3 r = nem::norm_quaterion_to_rotation_matrix(q);

    nem::float3 v(3.0f, -1.0f, 7.0f);

    nem::float3 v_by_quat = q * v;
    nem::float3 v_by_mat = r * v;

    EXPECT_NEAR(v_by_mat[0], v_by_quat[0], fEps);
    EXPECT_NEAR(v_by_mat[1], v_by_quat[1], fEps);
    EXPECT_NEAR(v_by_mat[2], v_by_quat[2], fEps);
}
