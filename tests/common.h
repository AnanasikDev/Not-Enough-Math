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

    // Defined in common.cpp — one definition, no ODR conflicts.
    extern const float  kEps;
    extern const double kEpsD;

    // MatApprox must live in the header because it is a class template.
    // Virtual functions in a template are safe here: the compiler emits
    // the vtable as a weak/comdat symbol and the linker deduplicates it.
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

} // namespace nem_tests
