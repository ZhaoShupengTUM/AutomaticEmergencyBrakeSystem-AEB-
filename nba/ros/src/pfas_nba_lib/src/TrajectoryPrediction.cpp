#include "TrajectoryPrediction.h"


double TrajectoryPrediction::braking_distance(double velocity, double deceleration){
    return pow(velocity,2)/(2.0*deceleration);
}

double TrajectoryPrediction::calc_beta(const double rwa) {
    return std::atan(VehicleParams::distance_rear_axle * std::tan(rwa) / 
        (VehicleParams::distance_front_axle + VehicleParams::distance_rear_axle));
}

std::vector<Pose> TrajectoryPrediction::predict_vehicle_trajectory(double rwa, double s) {
    std::vector<Pose> trajectory;
    
    int numberOfPoints{50};
    double beta = calc_beta(rwa);
    double ds = s / (numberOfPoints -1);

    double xCoM{0.0}, yCoM{0.0}, yawCoM{0.0};
    for (int i=0; i < numberOfPoints; ++i) {
        trajectory.emplace_back(xCoM, yCoM, yawCoM);
        xCoM +=  ds * std::cos(yawCoM + beta);
        yCoM +=  ds * std::sin(yawCoM + beta);
        yawCoM +=  ds * std::sin(beta) / VehicleParams::distance_rear_axle;
    }
    return trajectory; 
}