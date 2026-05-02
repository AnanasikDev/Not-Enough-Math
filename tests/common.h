#pragma once

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <cmath>
#include <string>

#include "utils.hpp"
#include "vec.hpp"
#include "vec_utils.hpp"
#include "mat.hpp"
#include "mat_utils.hpp"

using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

namespace nem_tests
{

    inline constexpr float  kEps = 1e-4f;
    inline constexpr double kEpsD = 1e-9;


    template <typename T, size_t R, size_t C>
    class MatApprox : public Catch::Matchers::MatcherBase<nem::mat<T, R, C>>
    {
        nem::mat<T, R, C> m_expected;
        T                 m_eps;
    public:
        explicit MatApprox(nem::mat<T, R, C> expected, T eps = static_cast<T>(kEps))
            : m_expected(expected), m_eps(eps)
        {
        }

        bool match(const nem::mat<T, R, C>& actual) const override
        {
            for (size_t i = 0; i < R * C; ++i)
                if (std::abs(actual.at(i) - m_expected.at(i)) >= m_eps) return false;
            return true;
        }

        std::string describe() const override { return "approximately equals expected matrix"; }
    };

    template <typename T, size_t R, size_t C>
    MatApprox<T, R, C> MatEq(const nem::mat<T, R, C>& expected, T eps = static_cast<T>(kEps))
    {
        return MatApprox<T, R, C>(expected, eps);
    }

}
