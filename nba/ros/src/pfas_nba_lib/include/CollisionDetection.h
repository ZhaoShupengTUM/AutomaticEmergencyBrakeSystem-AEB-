#pragma once
#include <vector>
#include "Pose.h"
#include <iostream>

class CollisionDetection {
    public:
        bool check_for_collisions(const std::vector<Pose>& polygon, const std::vector<Pose>& pose);

    private:
        bool point_in_polygon(const std::vector<Pose>& polygon, const Pose& pose);
};