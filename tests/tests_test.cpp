#include <gtest/gtest.h>

TEST(MyFunction, MyAssert)
{
    int a = 4;
    EXPECT_EQ(a, 4);
}

TEST(MyFunction2, MyAssert2)
{
    int a = 5;
    EXPECT_EQ(a, 5);
}

TEST(MyFunction3, MyAssert3)
{
    float a = 1.0000001f;
    EXPECT_FLOAT_EQ(a, 1.f);
}