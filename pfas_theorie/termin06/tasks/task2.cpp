#include <iostream>
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

int main() {
    std::vector<Pose> v1;
    v1.emplace_back(1.1, 2.0, 30);
    v1.emplace_back(2.0, 3.2, 10);
    v1.emplace_back(3.3, 3.0, 5);

    std::vector<Pose> v2 = v1;
    std::reverse(v2.begin(), v2.end());
    v1.insert(v1.end(), v2.begin(), v2.end());

    std::cout << "Laenge von v1: " << v1.size() << "; y-Position von Element 5: " <<
        v1.at(4).y << std::endl;

    return 0;
}