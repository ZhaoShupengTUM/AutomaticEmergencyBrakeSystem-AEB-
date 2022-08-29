// Copyright 2020 Simon Hoffmann
#include "ros/ros.h"
#include <iostream>
#include "tod_msgs/VehicleData.h"
#include "nav_msgs/Path.h"
#include "tf2/utils.h"
#include <geometry_msgs/PolygonStamped.h>
#include "CorridorCreation.h"

ros::Publisher _corrPub;
CorridorCreation _corrCreator;

void callback_trajectory(const nav_msgs::Path& msg) {
    // Write Input to std::vector<Pose>
    std::vector<Pose> traj_in;
    for (const geometry_msgs::PoseStamped& pose : msg.poses){
        traj_in.emplace_back(pose.pose.position.x, pose.pose.position.y,
             tf2::getYaw(pose.pose.orientation));
    }
    // Calc Corridor
    std::vector<Pose> corridor = _corrCreator.calc_corridor(traj_in);

    // Write Corridor to PolygonMsg
    geometry_msgs::PolygonStamped corridorPolygon;
    for (const Pose& pose : corridor){
        geometry_msgs::Point32 point;
        point.x = pose.get_x();
        point.y = pose.get_y();
        corridorPolygon.polygon.points.push_back(point);
    }
    corridorPolygon.header.frame_id = ("base_footprint");

    //Publish
    _corrPub.publish(corridorPolygon);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "CorridorCreation");
    ros::NodeHandle n;
    ros::Rate r(100);
    ros::Subscriber trajSubs = n.subscribe("/Vehicle/NBA/predicted_trajectory", 10, callback_trajectory);
    _corrPub = n.advertise<geometry_msgs::PolygonStamped>("/Vehicle/NBA/predicted_corridor", 10);
    
    while (ros::ok()) {
        ros::spinOnce();
        r.sleep();
    }
    return 0;
}
