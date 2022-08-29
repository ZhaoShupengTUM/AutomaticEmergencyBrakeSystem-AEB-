#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

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

int main() {

    std::vector<Pose> traj{};
    for (size_t i = 0; i < 50; i++)
    {
        traj.emplace_back(i*2, i*1.1, 20);
    }

    for (auto pose : traj)
    {
        std::cout << "dist = " << std::sqrt(pose.x*pose.x + pose.y*pose.y) << std::endl;
    }
    
    

    return 0;
}