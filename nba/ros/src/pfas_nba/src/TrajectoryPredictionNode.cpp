// Copyright 2020 Simon Hoffmann
#include "ros/ros.h"
#include <iostream>
//#include "tod_msgs/VehicleData.h"
#include <lgsvl_msgs/CanBusData.h>
#include "nav_msgs/Path.h"
#include "tf/tf.h"
#include "TrajectoryPrediction.h"
#include "VehicleParams.h"

ros::Publisher _trajPub;
TrajectoryPrediction _trajPred;

void callback_vehicle_data(const lgsvl_msgs::CanBusData& msg) {
    const float rwa = -msg.steer_pct * VehicleParams::maximum_road_wheel_angle;
    const float length = _trajPred.braking_distance(msg.speed_mps, 6.0) + 0.5;
    std::vector<Pose> poses = _trajPred.predict_vehicle_trajectory(rwa, length);
    
    nav_msgs::Path trajectory;    
    for (const Pose& pose : poses) {
        geometry_msgs::PoseStamped pose_out;
        pose_out.pose.position.x = pose.get_x();
        pose_out.pose.position.y = pose.get_y();
        pose_out.pose.orientation = tf::createQuaternionMsgFromYaw(pose.get_yaw());
        trajectory.poses.push_back(pose_out);
    }
    trajectory.header.frame_id = "base_footprint";
    _trajPub.publish(trajectory);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "TrajectoryPrediction");
    ros::NodeHandle n;
    ros::Rate r(100);
    
    ros::Subscriber vehicleDataSubs = n.subscribe("/CANBus", 10, callback_vehicle_data);
    _trajPub = n.advertise<nav_msgs::Path>("/Vehicle/NBA/predicted_trajectory", 10);
    
    while (ros::ok()) {
        ros::spinOnce();
        r.sleep();
    }
    return 0;
}
