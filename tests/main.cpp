#include <catch2/catch_test_macros.hpp>
#include "nem.hpp"

namespace nem_tests
{
    TEST_CASE("Addition", "[math]")
    {
        REQUIRE(2 + 2 == 4);
        REQUIRE((nem::float3(1) * nem::float3(5)).z == 5);
    }

    TEST_CASE("Edge cases", "[math][edge]")
    {
        SECTION("Adding zeros")
        {
            CHECK((nem::float3(0) * nem::float3()).x == 0);
        }
    }
}
