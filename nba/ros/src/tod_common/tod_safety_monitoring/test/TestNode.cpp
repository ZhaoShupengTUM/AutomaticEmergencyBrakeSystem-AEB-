// Copyright 2020 Simon Hoffmann
#include "ros/ros.h"
#include "ros/debug.h"
#include "tod_safety_monitoring/SafetyMonitor.h"
#include <tod_safety_monitoring/SafetyStatus.h>


int main(int argc, char **argv) {
    ros::init(argc, argv, "SafetyMonitoringTestNode");
    ros::NodeHandle nh;
    ros::Rate r(100);
    SafetyMonitor monitor(nh);
    monitor.start();
    std::string _nodeName{ros::this_node::getName()};
    std::string _key{"default"};
    int _level{1};
    if(!nh.getParam(_nodeName + "/key", _key)){
        ROS_ERROR("%s: Could not get param key, using: %s", _nodeName.c_str(), _key.c_str());
    }
    if(!nh.getParam(_nodeName + "/level", _level)){
        ROS_ERROR("%s: Could not get param level, using: %i", _nodeName.c_str(), _level);
    }
    while (ros::ok()) { 
        monitor.min_value(_key, 10, 5, static_cast<uint8_t>(_level), "The minimum value was exceeded within a test");
        ros::spinOnce();
        r.sleep();
    }
    return 0;
}
