#pragma once
#include "VehicleParams.h"
#include "Pose.h"
#include <vector>
#include <math.h>
#include <algorithm>

class CorridorCreation{
    public:
        void calc_vehicle_front_edges(const Pose& poseCoM, Pose& poseFR, Pose& poseFL);
        std::vector<Pose> calc_corridor(const std::vector<Pose>& trajectory);

};