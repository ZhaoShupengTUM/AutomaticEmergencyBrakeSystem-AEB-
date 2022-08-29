// Copyright 2021 FTM

#include "ros/ros.h"
#include "tod_msgs/PrimaryControlCmd.h"
#include "tod_msgs/SecondaryControlCmd.h"
#include "autoware_msgs/VehicleCmd.h"
#include "tod_msgs/VehicleEnums.h"

ros::Publisher _autowareMsgPub;
autoware_msgs::VehicleCmd _veh_cmd;

void callback_command(const tod_msgs::PrimaryControlCmdConstPtr& msg) {
    //autoware_msgs::VehicleCmd veh_cmd;
    _veh_cmd.twist_cmd.twist.linear.x = msg->velocity;
    _veh_cmd.twist_cmd.twist.angular.z = msg->steeringWheelAngle;
    //_autowareMsgPub.publish(veh_cmd);
}

void callback_sec_command(const tod_msgs::SecondaryControlCmdConstPtr& msg) {
    //autoware_msgs::VehicleCmd veh_cmd;
    _veh_cmd.gear_cmd.gear = (msg->gearPosition==GEARPOSITION_REVERSE) ? 1 : -1;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "VehicleCommandToLGSVL");
    ros::NodeHandle n;
    ros::Subscriber subControlCommand = n.subscribe("primary_control_cmd", 1, callback_command);
//    ros::Subscriber subSecControlCommand = n.subscribe("/Operator/CommandCreation/secondary_control_cmd", 1, callback_sec_command);
    _autowareMsgPub = n.advertise<autoware_msgs::VehicleCmd>("vehicle_cmd", 1);
    ros::Rate r(100);
    while (ros::ok()) {
        r.sleep();
        ros::spinOnce();
        _autowareMsgPub.publish(_veh_cmd);
    }
    return 0;
}
