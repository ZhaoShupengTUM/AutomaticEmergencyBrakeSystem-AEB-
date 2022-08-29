#include "CorridorCreation.h"

void CorridorCreation::calc_vehicle_front_edges(const Pose& poseCoM, Pose& poseFR, Pose& poseFL) {
    poseFL.set_x( poseCoM.get_x() + VehicleParams::distance_front_bumper
        * std::cos(float(poseCoM.get_yaw())) - VehicleParams::width_edge_to_edge * std::sin(float(poseCoM.get_yaw())) / 2.0);
    poseFL.set_y( poseCoM.get_y() + VehicleParams::distance_front_bumper 
        * std::sin(float(poseCoM.get_yaw())) + VehicleParams::width_edge_to_edge * std::cos(float(poseCoM.get_yaw())) / 2.0);
    
    poseFR.set_x( poseCoM.get_x() + VehicleParams::distance_front_bumper
        * std::cos(float(poseCoM.get_yaw())) + VehicleParams::width_edge_to_edge * std::sin(float(poseCoM.get_yaw())) / 2.0);
    poseFR.set_y( poseCoM.get_y() + VehicleParams::distance_front_bumper
        * std::sin(float(poseCoM.get_yaw())) - VehicleParams::width_edge_to_edge * std::cos(float(poseCoM.get_yaw())) / 2.0);
}

std::vector<Pose> CorridorCreation::calc_corridor(const std::vector<Pose>& trajectory) {
    std::vector<Pose> leftLane, rightLane;
    for (const auto& pose : trajectory){
        Pose left, right;
        calc_vehicle_front_edges(pose, right, left);
        leftLane.push_back(left);
        rightLane.push_back(right);
    }
    std::vector<Pose> corridor = leftLane;
    std::reverse(rightLane.begin(), rightLane.end());
    corridor.insert(corridor.end(), rightLane.begin(), rightLane.end());
    return corridor;
}
