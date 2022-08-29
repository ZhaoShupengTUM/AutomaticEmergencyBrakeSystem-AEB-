#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

struct Pose
{
    Pose (float _x, float _y, float _yaw) {
        x = _x;
        y = _y;
        yaw = _yaw;
    }
    Pose () {};
    float x{0};
    float y{0};
    float yaw{0};
};

float calc_braking_dist(float v, float a) {
    float d = v*a;
    std::cout << "Braking distance: " << d << std::endl;
    return d;
}

std::vector<Pose> reverse_traj(std::vector<Pose> traj_in) {
    std::vector<Pose> traj_2{traj_in};
    std::reverse(traj_2.begin(), traj_2.end());
    traj_in.insert(traj_in.end(), traj_2.begin(), traj_2.end());

    return traj_in;
}



int main() {

    float d1 = calc_braking_dist(1, 2);

    std::vector<Pose> traj{};
    for (size_t i = 0; i < 50; i++)
    {
        traj.emplace_back(i*2, i*1.1, 20);
    }

    std::vector<Pose> traj_new{reverse_traj(traj)};
    
    for (auto pose : traj_new)
    {
        std::cout << "dist = " << std::sqrt(pose.x*pose.x + pose.y*pose.y) << std::endl;
    }
    return 0;
}