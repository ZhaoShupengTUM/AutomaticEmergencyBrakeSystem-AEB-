// Copyright 2020 Feiler

#include <gtest/gtest.h>
#include "tod_helper/geometry/Conversion.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Point32.h"

TEST(PointToPoint32, copyValues) {
    double value = 5.1;
    geometry_msgs::Point point;
    point.x = point.y = point.z = value;
    geometry_msgs::Point32 expectedPoint;
    expectedPoint.x = expectedPoint.y = expectedPoint.z = (float) value;

    geometry_msgs::Point32 result = tod_helper::Geometry::Conversion::PointToPoint32(point);

    ASSERT_FLOAT_EQ(expectedPoint.x, result.x);
    ASSERT_FLOAT_EQ(expectedPoint.y, result.y);
    ASSERT_FLOAT_EQ(expectedPoint.z, result.z);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
