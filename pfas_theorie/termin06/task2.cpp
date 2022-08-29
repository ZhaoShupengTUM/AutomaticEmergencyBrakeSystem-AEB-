#include <iostream>
#include <vector>
#include <algorithm>

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


int main (){
    Pose pose1(1, 2, 1.1);
    Pose pose2(2, 3, 2.2);
    Pose pose3(3, 4, 3.3);
    std::vector<Pose> v1{pose1, pose2, pose3};

    std::vector<Pose> v2{v1};

    std::reverse(v2.begin(), v2.end());

    v1.insert(v1.end(), v2.begin(), v2.end());

    std::cout << v1.size() << std::endl;
    std::cout << v1.at(4).y << std::endl;

    return 0;
}