#pragma once

#include <iostream>
#include <math.h>
#include "VehicleParams.h"
#include <vector>
#include "Pose.h"

class TrajectoryPrediction{
    public:
        double braking_distance(double velocity, double deceleration);
        double calc_beta(const double rwa);
        std::vector<Pose> predict_vehicle_trajectory(double rwa, double s);
};