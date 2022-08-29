#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

class Pose {
    public:
        Pose (float x, float y, float yaw) {
            this->x = x; this->y = y; this->yaw = yaw;
        }
        Pose(){};

        float get_x() const {return x;};
        float get_y() const {return y;};
        float get_yaw() const {return yaw;};
        float get_yaw_deg() const {return (yaw/3.1415)*180;};
        void set_x(float x) {this->x = x;};
        void set_y(float y) {this->y = y;};
        void set_yaw(float yaw) {this->yaw = yaw;};
        void set_yaw_from_deg(float yaw) {this->yaw = (yaw/180.0)*3.1415;};

    private:
        float x{0};
        float y{0};
        float yaw{0}; // in rad
};

namespace VehicleParams{
    const float mass {2887.0};
    const float yaw_inertia {4700.0};
    const float distance_front_axle {1.446};
    const float distance_rear_axle {1.556};
    const float width_edge_to_edge {2.177};
    const float track_width {1.651};
    const float cornering_force_front {280666.0};
    const float cornering_force_rear {278903.0};
    const float maximum_road_wheel_angle {0.6108};
    const float maximum_steering_wheel_angle {7.8538};
    const float height {1.737};
    const float distance_front_bumper {2.408};
    const float distance_rear_bumper {2.681};
};

double braking_distance(double velocity, double deceleration){
    return pow(velocity,2)/(2.0*deceleration);
}

double calc_beta(const double rwa) {
    return std::atan(VehicleParams::distance_rear_axle * std::tan(rwa) / 
        (VehicleParams::distance_front_axle + VehicleParams::distance_rear_axle));
}

std::vector<Pose> predict_vehicle_trajectory(double rwa, double s) {
    std::vector<Pose> trajectory;
    
    int numberOfPoints{50};
    double beta = calc_beta(rwa);
    double ds = s / (numberOfPoints-1); // Todo: numberOfPoints-1?

    double xCoM{0.0}, yCoM{0.0}, yawCoM{0.0};
    for (int i=0; i < numberOfPoints; ++i) {
        trajectory.emplace_back(xCoM, yCoM, yawCoM);
        xCoM +=  ds * std::cos(yawCoM + beta);
        yCoM +=  ds * std::sin(yawCoM + beta);
        yawCoM +=  ds * std::sin(beta) / VehicleParams::distance_rear_axle;
    }
    return trajectory; 
}

void calc_vehicle_front_edges(const Pose& poseCoM, Pose& poseFR, Pose& poseFL) {
    poseFL.set_x( poseCoM.get_x() + VehicleParams::distance_front_bumper
        * std::cos(float(poseCoM.get_yaw())) - VehicleParams::width_edge_to_edge * std::sin(float(poseCoM.get_yaw())) / 2.0);
    poseFL.set_y( poseCoM.get_y() + VehicleParams::distance_front_bumper 
        * std::sin(float(poseCoM.get_yaw())) + VehicleParams::width_edge_to_edge * std::cos(float(poseCoM.get_yaw())) / 2.0);
    
    poseFR.set_x( poseCoM.get_x() + VehicleParams::distance_front_bumper
        * std::cos(float(poseCoM.get_yaw())) + VehicleParams::width_edge_to_edge * std::sin(float(poseCoM.get_yaw())) / 2.0);
    poseFR.set_y( poseCoM.get_y() + VehicleParams::distance_front_bumper
        * std::sin(float(poseCoM.get_yaw())) - VehicleParams::width_edge_to_edge * std::cos(float(poseCoM.get_yaw())) / 2.0);
}

std::vector<Pose> calc_corridor(const std::vector<Pose>& trajectory) {
    std::vector<Pose> leftLane, rightLane;
    for (const auto& pose : trajectory){
        Pose left, right;
        calc_vehicle_front_edges(pose, left, right);
        leftLane.push_back(left);
        rightLane.push_back(right);
    }
    std::vector<Pose> corridor = leftLane;
    std::reverse(rightLane.begin(), rightLane.end());
    corridor.insert(corridor.end(), rightLane.begin(), rightLane.end());
    return corridor;
}

int main() {
    // Test Aufgabe 2 
    std::cout << "# Test Aufgabe 2:" << std::endl;
    std::cout << "Braking Distance: " << braking_distance(10, 6) << std::endl;
    std::cout << "Beta: " << calc_beta(1.5) << std::endl;  
    std::cout << std::endl << "------------" << std::endl;
 //----------------------------------------------------------------------------------------------
    // Test Aufgabe 3
    std::cout << "# Test Aufgabe 3:" << std::endl;
    std::vector<Pose> traj = predict_vehicle_trajectory(0, 100);
    std::cout << "Size of Trajectory: " << traj.size() << std::endl;

    std::cout << "x-Positions: ";
    for (const Pose& pose : traj)
        std::cout << pose.get_x() << ", ";
    
    std::cout << std::endl << std::endl;

    std::vector<Pose> traj2 = predict_vehicle_trajectory(0.5, 20);
    std::cout << "Trajectory Pose at Position 20: ("<< traj.at(20).get_x() 
        << ", " << traj.at(20).get_y() << ")" << std::endl;

    std::cout << std::endl << "------------" << std::endl;
 //----------------------------------------------------------------------------------------------
    // Test Aufgabe 4 calc_vehicle_front_edges:
    std::cout << "# Test Aufgabe 4 - calc_vehicle_front_edges" << std::endl;
    Pose poseCoM{10, 5, 0.4};
    Pose poseFL{0, 0, 0};
    Pose poseFR{0, 0, 0};
    calc_vehicle_front_edges(poseCoM, poseFR, poseFL);
    std::cout << "PoseFR: (" << poseFR.get_x() << ", " << poseFR.get_y() << ")" << std::endl;
    std::cout << "PoseFR: (" << poseFL.get_x() << ", " << poseFL.get_y() << ")" << std::endl;
    std::cout << std::endl;

    // Test Aufgabe 4 Final:
    std::cout << "# Test Aufgabe 4 - Final" << std::endl;
    double brakingDistance = braking_distance(10, 6);
    std::vector<Pose> predictedTrajectory = predict_vehicle_trajectory(-0.4, brakingDistance);
    std::vector<Pose> predictedCorridor = calc_corridor(predictedTrajectory);
    std::cout << predictedCorridor.at(60).get_x() << ", " << predictedCorridor.at(60).get_y() << std::endl;

    return 0;
}
