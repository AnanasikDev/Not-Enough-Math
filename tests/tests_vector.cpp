#include "common.h"

using namespace nem_tests;
using nem::float2;
using nem::float3;
using nem::float4;

// NOTE: BaseVectorT::lerp is excluded — it calls the non-static comp_r()
// from a static context and will not compile (bug in the implementation).
//
// reflect() is also excluded — its expression `scalar * vector` requires a
// free operator*(T, Derived) which does not exist (bug in the implementation).

// ---------------------------------------------------------------------------
// Construction
// ---------------------------------------------------------------------------

TEST_CASE("float3: default construction is zero-initialized", "[vec][construction]") {
    float3 v;
    REQUIRE(v.x == 0.f);
    REQUIRE(v.y == 0.f);
    REQUIRE(v.z == 0.f);
}

TEST_CASE("float3: scalar construction fills all components", "[vec][construction]") {
    float3 v(3.f);
    REQUIRE(v.x == 3.f);
    REQUIRE(v.y == 3.f);
    REQUIRE(v.z == 3.f);
}

TEST_CASE("float3: component-wise construction", "[vec][construction]") {
    float3 v(1.f, 2.f, 3.f);
    REQUIRE(v.x == 1.f);
    REQUIRE(v.y == 2.f);
    REQUIRE(v.z == 3.f);
}

TEST_CASE("float2: union aliases are the same storage", "[vec][construction]") {
    float2 v(4.f, 5.f);
    REQUIRE(v.u == v.x);
    REQUIRE(v.v == v.y);
}

TEST_CASE("float4: union aliases are the same storage", "[vec][construction]") {
    float4 v(0.1f, 0.2f, 0.3f, 1.f);
    REQUIRE(v.r == v.x);
    REQUIRE(v.g == v.y);
    REQUIRE(v.b == v.z);
    REQUIRE(v.a == v.w);
}

// ---------------------------------------------------------------------------
// operator[]
// ---------------------------------------------------------------------------

TEST_CASE("float3: operator[] reads components by index", "[vec][access]") {
    float3 v(10.f, 20.f, 30.f);

    REQUIRE(v[0] == 10.f);
    REQUIRE(v[1] == 20.f);
    REQUIRE(v[2] == 30.f);
}

TEST_CASE("float3: operator[] write updates named component", "[vec][access]") {
    float3 v(1.f, 2.f, 3.f);

    v[1] = 99.f;

    REQUIRE(v.y == 99.f);
}

// ---------------------------------------------------------------------------
// Arithmetic
// ---------------------------------------------------------------------------

TEST_CASE("float3: addition is component-wise", "[vec][arithmetic]") {
    float3 a(1.f, 2.f, 3.f);
    float3 b(4.f, 5.f, 6.f);

    auto result = a + b;

    REQUIRE_THAT(result.x, WithinAbs(5.f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(7.f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(9.f, kEps));
}

TEST_CASE("float3: subtraction is component-wise", "[vec][arithmetic]") {
    float3 a(5.f, 7.f, 9.f);
    float3 b(1.f, 2.f, 3.f);

    auto result = a - b;

    REQUIRE_THAT(result.x, WithinAbs(4.f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(5.f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(6.f, kEps));
}

TEST_CASE("float3: self-subtraction is zero", "[vec][arithmetic]") {
    float3 a(1.f, 2.f, 3.f);

    auto result = a - a;

    REQUIRE_THAT(result.x, WithinAbs(0.f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(0.f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(0.f, kEps));
}

TEST_CASE("float3: scalar multiplication scales all components", "[vec][arithmetic]") {
    float3 a(1.f, 2.f, 3.f);

    auto result = a * 3.f;

    REQUIRE_THAT(result.x, WithinAbs(3.f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(6.f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(9.f, kEps));
}

TEST_CASE("float3: component-wise multiplication", "[vec][arithmetic]") {
    float3 a(2.f, 3.f, 4.f);
    float3 b(5.f, 6.f, 7.f);

    auto result = a * b;

    REQUIRE_THAT(result.x, WithinAbs(10.f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(18.f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(28.f, kEps));
}

TEST_CASE("float3: scalar division scales all components", "[vec][arithmetic]") {
    float3 a(2.f, 4.f, 6.f);

    auto result = a / 2.f;

    REQUIRE_THAT(result.x, WithinAbs(1.f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(2.f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(3.f, kEps));
}

TEST_CASE("float3: component-wise division", "[vec][arithmetic]") {
    float3 a(6.f, 8.f, 10.f);
    float3 b(2.f, 4.f,  5.f);

    auto result = a / b;

    REQUIRE_THAT(result.x, WithinAbs(3.f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(2.f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(2.f, kEps));
}

TEST_CASE("float3: operator*= multiplies components in-place", "[vec][arithmetic]") {
    float3 a(1.f, 2.f, 3.f);
    float3 b(2.f, 3.f, 4.f);

    a *= b;

    REQUIRE_THAT(a.x, WithinAbs(2.f,  kEps));
    REQUIRE_THAT(a.y, WithinAbs(6.f,  kEps));
    REQUIRE_THAT(a.z, WithinAbs(12.f, kEps));
}

// ---------------------------------------------------------------------------
// Length
// ---------------------------------------------------------------------------

TEST_CASE("float3: sqrLength is the sum of squared components", "[vec][length]") {
    float3 v(3.f, 4.f, 0.f);

    float result = v.sqrLength();

    REQUIRE_THAT(result, WithinAbs(25.f, kEps));
}

TEST_CASE("float3: length is the Euclidean norm", "[vec][length]") {
    float3 v(3.f, 4.f, 0.f);

    float result = v.length();

    REQUIRE_THAT(result, WithinAbs(5.f, kEps));
}

TEST_CASE("float3: unit vector has length 1", "[vec][length]") {
    float3 v(1.f, 0.f, 0.f);

    float result = v.length();

    REQUIRE_THAT(result, WithinAbs(1.f, kEps));
}

TEST_CASE("float2: length on 3-4-5 right triangle", "[vec][length]") {
    float2 v(3.f, 4.f);

    float result = v.length();

    REQUIRE_THAT(result, WithinAbs(5.f, kEps));
}

// ---------------------------------------------------------------------------
// normalize
// ---------------------------------------------------------------------------

TEST_CASE("float3: normalized produces a unit vector", "[vec][normalize]") {
    float3 v(3.f, 4.f, 0.f);

    float3 result = v.normalized();

    REQUIRE_THAT(result.x, WithinAbs(0.6f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(0.8f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(0.0f, kEps));
    REQUIRE_THAT(result.length(), WithinAbs(1.f, kEps));
}

TEST_CASE("normalize free function: result is unit length", "[vec][normalize]") {
    float3 v(0.f, 0.f, 5.f);

    float3 result = nem::normalize(v);

    REQUIRE_THAT(result.x, WithinAbs(0.f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(0.f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(1.f, kEps));
}

// ---------------------------------------------------------------------------
// dot
// ---------------------------------------------------------------------------

TEST_CASE("dot: perpendicular vectors yield zero", "[vec][dot]") {
    float3 a(1.f, 0.f, 0.f);
    float3 b(0.f, 1.f, 0.f);

    float result = nem::dot(a, b);

    REQUIRE_THAT(result, WithinAbs(0.f, kEps));
}

TEST_CASE("dot: parallel unit vectors yield one", "[vec][dot]") {
    float3 a(1.f, 0.f, 0.f);
    float3 b(1.f, 0.f, 0.f);

    float result = nem::dot(a, b);

    REQUIRE_THAT(result, WithinAbs(1.f, kEps));
}

TEST_CASE("dot: anti-parallel unit vectors yield negative one", "[vec][dot]") {
    float3 a(1.f, 0.f, 0.f);
    float3 b(-1.f, 0.f, 0.f);

    float result = nem::dot(a, b);

    REQUIRE_THAT(result, WithinAbs(-1.f, kEps));
}

TEST_CASE("dot: general case matches hand-computed sum of products", "[vec][dot]") {
    float3 a(1.f, 2.f, 3.f);
    float3 b(4.f, 5.f, 6.f);

    float result = nem::dot(a, b);  // 1*4 + 2*5 + 3*6 = 32

    REQUIRE_THAT(result, WithinAbs(32.f, kEps));
}

TEST_CASE("dot: dot(v, v) equals sqrLength", "[vec][dot]") {
    float3 v(3.f, 4.f, 5.f);

    float result = nem::dot(v, v);

    REQUIRE_THAT(result, WithinAbs(v.sqrLength(), kEps));
}

// ---------------------------------------------------------------------------
// cross
// ---------------------------------------------------------------------------

TEST_CASE("cross: standard basis vectors produce the third", "[vec][cross]") {
    float3 x(1.f, 0.f, 0.f);
    float3 y(0.f, 1.f, 0.f);
    float3 z(0.f, 0.f, 1.f);

    SECTION("x cross y = z") {
        auto result = nem::cross(x, y);
        REQUIRE_THAT(result.x, WithinAbs(0.f, kEps));
        REQUIRE_THAT(result.y, WithinAbs(0.f, kEps));
        REQUIRE_THAT(result.z, WithinAbs(1.f, kEps));
    }
    SECTION("y cross z = x") {
        auto result = nem::cross(y, z);
        REQUIRE_THAT(result.x, WithinAbs(1.f, kEps));
        REQUIRE_THAT(result.y, WithinAbs(0.f, kEps));
        REQUIRE_THAT(result.z, WithinAbs(0.f, kEps));
    }
    SECTION("z cross x = y") {
        auto result = nem::cross(z, x);
        REQUIRE_THAT(result.x, WithinAbs(0.f, kEps));
        REQUIRE_THAT(result.y, WithinAbs(1.f, kEps));
        REQUIRE_THAT(result.z, WithinAbs(0.f, kEps));
    }
}

TEST_CASE("cross: reversed operands negate the result", "[vec][cross]") {
    float3 a(1.f, 2.f, 3.f);
    float3 b(4.f, 5.f, 6.f);

    float3 ab = nem::cross(a, b);
    float3 ba = nem::cross(b, a);

    REQUIRE_THAT(ab.x, WithinAbs(-ba.x, kEps));
    REQUIRE_THAT(ab.y, WithinAbs(-ba.y, kEps));
    REQUIRE_THAT(ab.z, WithinAbs(-ba.z, kEps));
}

TEST_CASE("cross: parallel vectors yield zero vector", "[vec][cross]") {
    float3 v(1.f, 2.f, 3.f);

    auto result = nem::cross(v, v);

    REQUIRE_THAT(result.x, WithinAbs(0.f, kEps));
    REQUIRE_THAT(result.y, WithinAbs(0.f, kEps));
    REQUIRE_THAT(result.z, WithinAbs(0.f, kEps));
}

TEST_CASE("cross: result is perpendicular to both inputs", "[vec][cross]") {
    float3 a(1.f, 2.f, 3.f);
    float3 b(4.f, 5.f, 6.f);

    auto result = nem::cross(a, b);

    REQUIRE_THAT(nem::dot(result, a), WithinAbs(0.f, kEps));
    REQUIRE_THAT(nem::dot(result, b), WithinAbs(0.f, kEps));
}

// ---------------------------------------------------------------------------
// comp_sum / comp_mul
// ---------------------------------------------------------------------------

TEST_CASE("comp_sum: returns the sum of all components", "[vec][comp]") {
    SECTION("float3") {
        float3 v(2.f, 3.f, 4.f);
        float result = nem::comp_sum(v);
        REQUIRE_THAT(result, WithinAbs(9.f, kEps));
    }
    SECTION("float2") {
        float2 v(5.f, 6.f);
        float result = nem::comp_sum(v);
        REQUIRE_THAT(result, WithinAbs(11.f, kEps));
    }
    SECTION("float4") {
        float4 v(1.f, 2.f, 3.f, 4.f);
        float result = nem::comp_sum(v);
        REQUIRE_THAT(result, WithinAbs(10.f, kEps));
    }
}

TEST_CASE("comp_mul: returns the product of all components", "[vec][comp]") {
    SECTION("float3") {
        float3 v(2.f, 3.f, 4.f);
        float result = nem::comp_mul(v);
        REQUIRE_THAT(result, WithinAbs(24.f, kEps));
    }
    SECTION("float2") {
        float2 v(5.f, 6.f);
        float result = nem::comp_mul(v);
        REQUIRE_THAT(result, WithinAbs(30.f, kEps));
    }
}

// ---------------------------------------------------------------------------
// is_nearly_zero (vector overload)
// ---------------------------------------------------------------------------

TEST_CASE("is_nearly_zero (vector): true when all components are near zero", "[vec][is_nearly_zero]") {
    float3 v(0.f, 0.f, 0.f);
    bool result = nem::is_nearly_zero(v);
    REQUIRE(result);
}

TEST_CASE("is_nearly_zero (vector): true when components are within epsilon", "[vec][is_nearly_zero]") {
    float3 v(1e-8f, 0.f, 0.f);
    bool result = nem::is_nearly_zero(v);
    REQUIRE(result);
}

TEST_CASE("is_nearly_zero (vector): false when any component exceeds epsilon", "[vec][is_nearly_zero]") {
    SECTION("x exceeds epsilon") {
        bool result = nem::is_nearly_zero(float3(0.01f, 0.f, 0.f));
        REQUIRE_FALSE(result);
    }
    SECTION("z exceeds epsilon") {
        bool result = nem::is_nearly_zero(float3(0.f, 0.f, 1.f));
        REQUIRE_FALSE(result);
    }
}

// ---------------------------------------------------------------------------
// orthogonal_3d_basis
// ---------------------------------------------------------------------------

static void require_valid_basis(float3 n, float3 b1, float3 b2) {
    REQUIRE_THAT(b1.length(),          WithinAbs(1.f, kEps));
    REQUIRE_THAT(b2.length(),          WithinAbs(1.f, kEps));
    REQUIRE_THAT(nem::dot(n,  b1),     WithinAbs(0.f, kEps));
    REQUIRE_THAT(nem::dot(n,  b2),     WithinAbs(0.f, kEps));
    REQUIRE_THAT(nem::dot(b1, b2),     WithinAbs(0.f, kEps));
}

TEST_CASE("orthogonal_3d_basis: produces orthonormal pair perpendicular to input", "[vec][basis]") {
    SECTION("general direction") {
        float3 n(0.f, 1.f, 0.f);
        float3 b1, b2;
        bool ok = nem::orthogonal_3d_basis(n, b1, b2);
        REQUIRE(ok);
        require_valid_basis(n, b1, b2);
    }
    SECTION("near-Z axis (triggers alternate branch)") {
        float3 n(0.f, 0.f, 1.f);
        float3 b1, b2;
        bool ok = nem::orthogonal_3d_basis(n, b1, b2);
        REQUIRE(ok);
        require_valid_basis(n, b1, b2);
    }
    SECTION("diagonal direction") {
        float3 n = nem::normalize(float3(1.f, 1.f, 0.f));
        float3 b1, b2;
        bool ok = nem::orthogonal_3d_basis(n, b1, b2);
        REQUIRE(ok);
        require_valid_basis(n, b1, b2);
    }
}

TEST_CASE("orthogonal_3d_basis: returns false for zero vector", "[vec][basis]") {
    float3 b1, b2;
    bool result = nem::orthogonal_3d_basis(float3(0.f, 0.f, 0.f), b1, b2);
    REQUIRE_FALSE(result);
}
