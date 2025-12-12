#include <gtest/gtest.h>
#include <cmath>
#include <angle/degrees.hpp>
#include <angle/radians.hpp>
#include <angle/conversions.hpp>

using namespace ang;

const double PI = 3.14159265358979323846;

TEST(DegreesTest, ConstructorAndDoubleConversion) {
    degrees deg(45.0);
    EXPECT_DOUBLE_EQ(static_cast<double>(deg), 45.0);
}

TEST(DegreesTest, ToRadiansConversion) {
    degrees deg(180.0);
    radians rad = to_radians(deg);
    EXPECT_DOUBLE_EQ(rad.value(), PI);
}

TEST(DegreesTest, Addition) {
    degrees deg1(30.0);
    degrees deg2(15.0);
    degrees result = deg1 + deg2;
    EXPECT_DOUBLE_EQ(static_cast<double>(result), 45.0);
}

TEST(DegreesTest, Multiplication) {
    degrees deg1(3.0);
    degrees result = deg1 * 4.0;
    EXPECT_DOUBLE_EQ(static_cast<double>(result), 12.0);
}

TEST(DegreesTest, Division) {
    degrees deg1(15.0);
    degrees result = deg1 / 3.0;
    EXPECT_DOUBLE_EQ(static_cast<double>(result), 5.0);
}

TEST(DegreesTest, ComparisonLessThan) {
    degrees deg1(30.0);
    degrees deg2(60.0);
    EXPECT_TRUE(deg1 < deg2);
    EXPECT_FALSE(deg2 < deg1);
}

TEST(RadiansTest, ToDegreesConversion) {
    radians rad(PI);
    degrees deg = to_degrees(rad);
    EXPECT_DOUBLE_EQ(deg.value(), 180.0);
}

TEST(RadiansTest, Addition) {
    radians rad1(PI / 2);
    radians rad2(PI / 4);
    radians result = rad1 + rad2;
    EXPECT_DOUBLE_EQ(result.value(), 3.0 * PI / 4.0);
}

TEST(RadiansTest, Subtraction) {
    radians rad1(PI);
    radians rad2(PI / 3.0);
    radians result = rad1 - rad2;
    EXPECT_DOUBLE_EQ(result.value(), 2.0 * PI / 3.0);
}

TEST(RadiansTest, ComparisonLessThan) {
    radians rad1(PI / 6.0);
    radians rad2(PI / 2.0);
    EXPECT_TRUE(rad1 < rad2);
    EXPECT_FALSE(rad2 < rad1);
}

TEST(IntegrationTest, DegreesToRadiansAndBack) {
    degrees original_deg(270.0);
    radians rad   = to_radians(original_deg);
    degrees converted_deg = to_degrees(rad);

    EXPECT_DOUBLE_EQ(original_deg.value(), converted_deg.value());
}

TEST(IntegrationTest, RadiansToDegreesAndBack) {
    radians original_rad(5.0 * PI / 6.0);
    degrees deg   = to_degrees(original_rad);
    radians converted_rad = to_radians(deg);

    EXPECT_DOUBLE_EQ(original_rad.value(), converted_rad.value());
}

TEST(IntegrationTest, MixedOperations) {
    degrees deg1(90.0);
    radians rad1 = to_radians(deg1);

    degrees deg2(45.0);
    radians rad2 = to_radians(deg2);

    radians sum_rad = rad1 + rad2;
    degrees sum_deg = to_degrees(sum_rad);

    EXPECT_DOUBLE_EQ(sum_deg.value(), 135.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}