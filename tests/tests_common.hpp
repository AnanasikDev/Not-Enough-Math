#pragma once

#include <gtest/gtest.h>
#include "nem.hpp"

static constexpr float  fEps = nem::Eps<float>();
static constexpr double dEps = 1e-9;

static constexpr float FNAN = std::numeric_limits<float>::quiet_NaN();
static constexpr float FMAX = std::numeric_limits<float>::max();

static bool IS_SAFE_INVALID(float scalar)
{
#ifdef NEM_ERR_USE_NAN
    return std::isnan(scalar);
#elif defined(NEM_ERR_SAFE_FALLBACK)
    return nem::is_zero(scalar);
#else
    return nem::is_zero(scalar);
#endif
}

template<typename Derived, typename T, size_t N>
static bool IS_SAFE_INVALID(const nem::BaseVectorT<Derived, T, N>& vec)
{
    static_assert(std::is_same_v<T, float>,
        "IS_SAFE_INVALID vector helper only supports floats");
    for (size_t i = 0; i < N; i++)
    {
        if (IS_SAFE_INVALID(vec[i])) return true;
    }
    return false;
}

static void require_valid_basis(nem::float3 n, nem::float3 b1, nem::float3 b2)
{
    EXPECT_NEAR(nem::length(b1), 1.f, fEps);
    EXPECT_NEAR(nem::length(b2), 1.f, fEps);
    EXPECT_NEAR(nem::dot(n, b1), 0.f, fEps);
    EXPECT_NEAR(nem::dot(n, b2), 0.f, fEps);
    EXPECT_NEAR(nem::dot(b1, b2), 0.f, fEps);
}

static void range_accuracy_test(float min, float max, int iterations, float (*fun1)(float), float (*fun2)(float), float eps)
{
    float length = max - min;
    float maxerr = 0;
    float x = min;
    float step = length / static_cast<float>(iterations);
    float totalerror = 0;
    for (int i = 0; i < iterations; i++)
    {
        const float nem_result = fun1(x);
        const float std_result = fun2(x);
        const float error = nem::abs(nem_result - std_result);
        totalerror += error;
        if (error > maxerr)
        {
            maxerr = error;
        }
        x += step;
    }
    printf("Max error: |%.6f|\nAverage error: |%.6f|", maxerr, totalerror / iterations);
    ASSERT_NEAR(maxerr, 0.0f, eps);
}