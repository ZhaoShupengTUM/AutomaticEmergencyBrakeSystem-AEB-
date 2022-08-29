#pragma once

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