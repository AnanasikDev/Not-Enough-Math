#include "tests_common.hpp"
#include "easing.hpp"

#define TEST_EASE(function, name, input, output)\
    TEST(function, name)\
    {\
        const float result = nem::ease::function(input);\
        ASSERT_NEAR(result, output, fEps);\
    }

#define TEST_EASE_BOUNDS(function, name)\
    TEST_EASE(function, name##min, 0.f, 0.0f)\
    TEST_EASE(function, name##max, 1.f, 1.0f)


TEST_EASE_BOUNDS(in_out_back, bounds)
TEST_EASE_BOUNDS(in_back, bounds)
TEST_EASE_BOUNDS(out_back, bounds)
TEST_EASE_BOUNDS(in_sine, bounds)
TEST_EASE_BOUNDS(out_sine, bounds)
TEST_EASE_BOUNDS(in_out_sine, bounds)
TEST_EASE_BOUNDS(in_bounce, bounds)
TEST_EASE_BOUNDS(out_bounce, bounds)
TEST_EASE_BOUNDS(in_out_bounce, bounds)
TEST_EASE_BOUNDS(in_elastic, bounds)
TEST_EASE_BOUNDS(out_elastic, bounds)
TEST_EASE_BOUNDS(in_out_elastic, bounds)
TEST_EASE_BOUNDS(in_cubic, bounds)
TEST_EASE_BOUNDS(out_cubic, bounds)
TEST_EASE_BOUNDS(in_out_cubic, bounds)
