// Copyright 2021 Schimpe
// NOT FOR OPEN SOURCE

#pragma once
#include <ros/ros.h>

namespace tod_helper::Timer {

class ScopedTimer {
public:
    explicit ScopedTimer(const std::string &name) : _name{name}, _start{ros::Time::now()} {}
    ~ScopedTimer() { ROS_ERROR("Timer %s lived for %f ms", _name.c_str(), elapsedMS()); }
    double elapsedMS() const { return (ros::Time::now() - _start).toSec() * 1000.0; }

private:
    std::string _name;
    ros::Time _start;
};

}; // namespace tod_helper::Timer
