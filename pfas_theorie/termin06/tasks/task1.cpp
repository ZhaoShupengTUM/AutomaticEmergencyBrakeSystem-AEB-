#include <iostream>

int main() {
    float velocity{10.0}, deceleration{6.0};
    float braking_distance = (velocity * velocity) / (2 * deceleration);
    std::cout << "Der Bremsweg betraegt: " << braking_distance  << " m"<< std::endl;
    return 0;
}