#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
struct Pose {
    Pose (float x_in, float y_in, float yaw_in) {
        x = x_in; y = y_in; yaw = yaw_in;
    }
    Pose(){};
    float x;
    float y;
    float yaw;
};

double braking_distance(double velocity, double deceleration){
    return pow(velocity,2)/(2.0*deceleration);
};

std::vector<Pose> new_trajectory(const std::vector<Pose>& traj_in){
    std::vector<Pose> traj_out = traj_in;
    std::reverse(traj_out.begin(), traj_out.end());
    traj_out.insert(traj_out.begin(), traj_in.begin(), traj_in.end());
    return traj_out;
}

int main() {
    std::cout << "Der Bremsweg beträgt: " << braking_distance(10,6) << " m" << std::endl;
    
    std::vector<Pose> trajectory;
    float x{0}, y{0}, yaw{20};
    for (int i=0; i<50; i++) {
        trajectory.emplace_back(x, y, yaw);
        x += 2;
        y += 1.1;
    }

    std::vector<Pose> traj2 = new_trajectory(trajectory);
    for(const Pose& pose : traj2){
        std::cout << std::sqrt(pose.x*pose.x + pose.y*pose.y) << std::endl;
    }

    return 0;
}
