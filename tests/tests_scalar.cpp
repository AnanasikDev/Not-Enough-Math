#include "common.h"

using namespace nem_tests;

// ---------------------------------------------------------------------------
// clamp
// ---------------------------------------------------------------------------

TEST_CASE("clamp: in-range value is unchanged", "[scalar][clamp]") {
    int result = nem::clamp(5, 0, 10);
    REQUIRE(result == 5);
}

TEST_CASE("clamp: value below min becomes min", "[scalar][clamp]") {
    int result = nem::clamp(-1, 0, 10);
    REQUIRE(result == 0);
}

TEST_CASE("clamp: value above max becomes max", "[scalar][clamp]") {
    int result = nem::clamp(11, 0, 10);
    REQUIRE(result == 10);
}

TEST_CASE("clamp: boundary values are inclusive", "[scalar][clamp]") {
    SECTION("lower boundary") {
        int result = nem::clamp(0, 0, 10);
        REQUIRE(result == 0);
    }
    SECTION("upper boundary") {
        int result = nem::clamp(10, 0, 10);
        REQUIRE(result == 10);
    }
}

TEST_CASE("clamp01: maps to [0, 1]", "[scalar][clamp]") {
    SECTION("below zero becomes zero") {
        float result = nem::clamp01(-0.5f);
        REQUIRE_THAT(result, WithinAbs(0.f, kEps));
    }
    SECTION("above one becomes one") {
        float result = nem::clamp01(1.5f);
        REQUIRE_THAT(result, WithinAbs(1.f, kEps));
    }
    SECTION("in-range value is unchanged") {
        float result = nem::clamp01(0.5f);
        REQUIRE_THAT(result, WithinAbs(0.5f, kEps));
    }
}

// ---------------------------------------------------------------------------
// abs
// ---------------------------------------------------------------------------

TEST_CASE("abs: returns unsigned magnitude", "[scalar][abs]") {
    SECTION("negative integer") {
        int result = nem::abs(-7);
        REQUIRE(result == 7);
    }
    SECTION("positive integer is unchanged") {
        int result = nem::abs(7);
        REQUIRE(result == 7);
    }
    SECTION("negative float") {
        float result = nem::abs(-2.5f);
        REQUIRE_THAT(result, WithinAbs(2.5f, kEps));
    }
}

// ---------------------------------------------------------------------------
// sqr / cube
// ---------------------------------------------------------------------------

TEST_CASE("sqr: returns x squared", "[scalar][sqr]") {
    SECTION("positive")                 { REQUIRE(nem::sqr(5)  == 25); }
    SECTION("negative yields positive") { REQUIRE(nem::sqr(-5) == 25); }
}

TEST_CASE("cube: returns x cubed", "[scalar][cube]") {
    SECTION("positive")                { REQUIRE(nem::cube(3)  == 27); }
    SECTION("negative preserves sign") { REQUIRE(nem::cube(-2) == -8); }
}

// ---------------------------------------------------------------------------
// pow2 / pow3 / pow4
//
// pow2 and pow3 are currently implemented as sqr(sqr(x)) = x^4 (copy-paste bug).
// The tests below encode EXPECTED semantics; failures identify the broken functions.
// ---------------------------------------------------------------------------

TEST_CASE("pow2: computes x^2", "[scalar][pow]") {
    int result = nem::pow2(3);
    REQUIRE(result == 9);
}

TEST_CASE("pow3: computes x^3", "[scalar][pow]") {
    int result = nem::pow3(2);
    REQUIRE(result == 8);
}

TEST_CASE("pow4: computes x^4", "[scalar][pow]") {
    SECTION("base 2") { REQUIRE(nem::pow4(2) == 16); }
    SECTION("base 3") { REQUIRE(nem::pow4(3) == 81); }
}

// ---------------------------------------------------------------------------
// sqrt
// ---------------------------------------------------------------------------

TEST_CASE("sqrt (float): converges to true square root", "[scalar][sqrt]") {
    SECTION("perfect square") {
        double result = nem::sqrt(4.0);
        REQUIRE_THAT(result, WithinAbs(2.0, kEpsD));
    }
    SECTION("irrational result matches std::sqrt") {
        double result = nem::sqrt(2.0);
        REQUIRE_THAT(result, WithinAbs(std::sqrt(2.0), kEpsD));
    }
    SECTION("zero") {
        double result = nem::sqrt(0.0);
        REQUIRE_THAT(result, WithinAbs(0.0, kEpsD));
    }
    SECTION("negative input returns zero") {
        double result = nem::sqrt(-1.0);
        REQUIRE_THAT(result, WithinAbs(0.0, kEpsD));
    }
}

TEST_CASE("sqrt (integer): returns truncated integer square root", "[scalar][sqrt]") {
    SECTION("zero")  { REQUIRE(nem::sqrt(0)  == 0); }
    SECTION("4")     { REQUIRE(nem::sqrt(4)  == 2); }
    SECTION("9")     { REQUIRE(nem::sqrt(9)  == 3); }
    SECTION("25")    { REQUIRE(nem::sqrt(25) == 5); }
}

// ---------------------------------------------------------------------------
// lerp
// ---------------------------------------------------------------------------

TEST_CASE("lerp: linearly interpolates between a and b", "[scalar][lerp]") {
    SECTION("t=0 returns a") {
        double result = nem::lerp(0.0, 10.0, 0.0);
        REQUIRE_THAT(result, WithinAbs(0.0, kEpsD));
    }
    SECTION("t=1 returns b") {
        double result = nem::lerp(0.0, 10.0, 1.0);
        REQUIRE_THAT(result, WithinAbs(10.0, kEpsD));
    }
    SECTION("t=0.5 returns midpoint") {
        double result = nem::lerp(0.0, 10.0, 0.5);
        REQUIRE_THAT(result, WithinAbs(5.0, kEpsD));
    }
    SECTION("t=0.25 on asymmetric range") {
        double result = nem::lerp(2.0, 8.0, 0.25);
        REQUIRE_THAT(result, WithinAbs(3.5, kEpsD));
    }
    SECTION("negative range: midpoint is zero") {
        double result = nem::lerp(-4.0, 4.0, 0.5);
        REQUIRE_THAT(result, WithinAbs(0.0, kEpsD));
    }
}

// ---------------------------------------------------------------------------
// smoothstep
// ---------------------------------------------------------------------------

TEST_CASE("smoothstep: produces hermite S-curve", "[scalar][smoothstep]") {
    SECTION("returns 0 at edge0") {
        double result = nem::smoothstep(0.0, 1.0, 0.0);
        REQUIRE_THAT(result, WithinAbs(0.0, kEpsD));
    }
    SECTION("returns 1 at edge1") {
        double result = nem::smoothstep(0.0, 1.0, 1.0);
        REQUIRE_THAT(result, WithinAbs(1.0, kEpsD));
    }
    SECTION("returns 0.5 at symmetric midpoint") {
        double result = nem::smoothstep(0.0, 1.0, 0.5);
        REQUIRE_THAT(result, WithinAbs(0.5, kEpsD));
    }
    SECTION("clamps below edge0") {
        double result = nem::smoothstep(0.0, 1.0, -1.0);
        REQUIRE_THAT(result, WithinAbs(0.0, kEpsD));
    }
    SECTION("clamps above edge1") {
        double result = nem::smoothstep(0.0, 1.0, 2.0);
        REQUIRE_THAT(result, WithinAbs(1.0, kEpsD));
    }
    SECTION("known value at t=0.25: 3t^2 - 2t^3 = 0.15625") {
        double result = nem::smoothstep(0.0, 1.0, 0.25);
        REQUIRE_THAT(result, WithinAbs(0.15625, kEpsD));
    }
    SECTION("S-curve is slower than linear in first quarter") {
        double result = nem::smoothstep(0.0, 1.0, 0.25);
        REQUIRE(result < 0.25);
    }
    SECTION("S-curve is faster than linear in third quarter") {
        double result = nem::smoothstep(0.0, 1.0, 0.75);
        REQUIRE(result > 0.75);
    }
}

// ---------------------------------------------------------------------------
// is_nearly_zero
// ---------------------------------------------------------------------------

TEST_CASE("is_nearly_zero: detects values within epsilon of zero", "[scalar][is_nearly_zero]") {
    SECTION("exact zero") {
        bool result = nem::is_nearly_zero(0.0);
        REQUIRE(result);
    }
    SECTION("within default epsilon") {
        bool result = nem::is_nearly_zero(1e-7);
        REQUIRE(result);
    }
    SECTION("negative within default epsilon") {
        bool result = nem::is_nearly_zero(-1e-7);
        REQUIRE(result);
    }
    SECTION("outside default epsilon") {
        bool result = nem::is_nearly_zero(0.01);
        REQUIRE_FALSE(result);
    }
    SECTION("within custom epsilon") {
        bool result = nem::is_nearly_zero(0.05, 0.1);
        REQUIRE(result);
    }
    SECTION("outside custom epsilon") {
        bool result = nem::is_nearly_zero(0.15, 0.1);
        REQUIRE_FALSE(result);
    }
}
