#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

struct Pose {
    Pose (float x_in, float y_in, float yaw_in) {
        x = x_in; y = y_in; yaw = yaw_in;
    }
    Pose(){};
    float x;
    float y;
    float yaw;
};

int main() {
    std::vector<Pose> trajectory;
    float x{0}, y{0}, yaw{20};
    for (int i=0; i<50; i++) {
        trajectory.emplace_back(x, y, yaw);
        x += 2;
        y += 1.1;
    }

    for(const Pose& pose : trajectory){
        std::cout << std::sqrt(pose.x*pose.x + pose.y*pose.y) << std::endl;
    }

    return 0;
}
