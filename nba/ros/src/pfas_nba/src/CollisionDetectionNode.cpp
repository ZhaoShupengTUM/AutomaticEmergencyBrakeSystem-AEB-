// Copyright 2020 Simon Hoffmann
#include "ros/ros.h"
#include <iostream>
#include <algorithm>
#include <geometry_msgs/PolygonStamped.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <autoware_msgs/VehicleCmd.h>
#include "CollisionDetection.h"
#include "VehicleParams.h"

std::vector<Pose> _corridor;
std::vector<Pose> _laserPoints;
autoware_msgs::VehicleCmd _vehicleCmd;

void scan_callback(const sensor_msgs::PointCloud2& msg){
    sensor_msgs::PointCloud pc;
    sensor_msgs::convertPointCloud2ToPointCloud(msg, pc);
    _laserPoints.clear();
    for (const geometry_msgs::Point32& point : pc.points)
        _laserPoints.emplace_back(point.x+VehicleParams::distance_front_bumper, point.y, 0);
}

void corridor_callback(const geometry_msgs::PolygonStamped& msg){
    _corridor.clear();
    for (const geometry_msgs::Point32& point : msg.polygon.points)
        _corridor.emplace_back(point.x, point.y, 0);
}

void vehicle_cmd_callback(const autoware_msgs::VehicleCmd& msg){
    _vehicleCmd = msg;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "CollisionDetection");
    ros::NodeHandle n;
    ros::Rate r(50);
    ros::Subscriber laserSubs = n.subscribe("/LidarFront", 10, scan_callback);
    ros::Subscriber trajectorySubs = n.subscribe("/Vehicle/NBA/predicted_corridor", 10, corridor_callback);
    ros::Subscriber VehicleCmdSubs = n.subscribe("/vehicle_cmd", 10, vehicle_cmd_callback);
    ros::Publisher brakeSignalPub = n.advertise<autoware_msgs::VehicleCmd>("/VehicleCmd", 10);
    
    CollisionDetection collisionDetector;
    //autoware_msgs::VehicleCmd brakeSignal;
    //brakeSignal.brake_cmd.brake = 1;
    while (ros::ok()) {
        ros::spinOnce();
        if(_corridor.size()>3 && _laserPoints.size()>=1)
            if(collisionDetector.check_for_collisions(_corridor, _laserPoints)) {
                //brakeSignalPub.publish(brakeSignal);
                _vehicleCmd.twist_cmd.twist.linear.x = 0;
            };
        brakeSignalPub.publish(_vehicleCmd);
        r.sleep();
    }
    return 0;
}
