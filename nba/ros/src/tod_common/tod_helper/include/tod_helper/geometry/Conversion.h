// Copyright 2020 Feiler
// not for open source
// Also, "Conversion" is not a good name


#pragma once

#include "geometry_msgs/Point.h"
#include "geometry_msgs/Point32.h"

namespace tod_helper::Geometry {

class Conversion {
public:
    inline static geometry_msgs::Point32 PointToPoint32(
        const geometry_msgs::Point& point) {
        geometry_msgs::Point32 point32;
        point32.x = (float) point.x;
        point32.y = (float) point.y;
        point32.z = (float) point.z;
        return point32;
    }
};
} // namespace tod_helper::Geometry
