// Copyright 2020 Simon Hoffmann
#include "ros/ros.h"
#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_datatypes.h>
#include "helper.h"
#include "CollisionDetection.h"

nav_msgs::Odometry _odom, _odomObst;

void odom_callback(const nav_msgs::Odometry& msg){
    _odom = msg;
}

void odom_obst_callback(const nav_msgs::Odometry& msg){
    _odomObst = msg;
}

double calc_rel_velocity(nav_msgs::Odometry odom1, nav_msgs::Odometry odom2){
    double x1, x2, y1, y2, v1, phi1, v2, phi2;
    tf::Quaternion quat1(odom1.pose.pose.orientation.x, odom1.pose.pose.orientation.y, odom1.pose.pose.orientation.z, odom1.pose.pose.orientation.w);
    tf::Quaternion quat2(odom2.pose.pose.orientation.x, odom2.pose.pose.orientation.y, odom2.pose.pose.orientation.z, odom2.pose.pose.orientation.w);
    v1 = odom1.twist.twist.linear.x;
    phi1 = tf::getYaw(quat1.normalize());
    v2 = odom2.twist.twist.linear.x;
    phi2 = tf::getYaw(quat2.normalize());
    x1 = v1 * std::cos(phi1);
    y1 = v1 * std::sin(phi1);
    x2 = v2 * std::cos(phi2);
    y2 = v2 * std::sin(phi2);
    return std::sqrt(std::pow(x1-x2, 2) + std::pow(y1-y2, 2));
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "ScenarioEvaluation");
    ros::NodeHandle n;
    ros::Rate r(50);
    ros::Subscriber odomSubs = n.subscribe("/odometry", 10, odom_callback);
    ros::Subscriber odomObstSubs = n.subscribe("/odometryObst", 10, odom_obst_callback);
    ros::Publisher distPub = n.advertise<std_msgs::Float32>("/ScenarioEval/Distance", 10);
    ros::Publisher mindistPub = n.advertise<std_msgs::Float32>("/ScenarioEval/MinDistance", 10);
    ros::Publisher relVelPub = n.advertise<std_msgs::Float32>("/ScenarioEval/RelVel", 10);
    ros::Publisher colPub = n.advertise<std_msgs::Int16>("/ScenarioEval/Collision", 10);
    std_msgs::Float32 dist;
    std_msgs::Float32 minDist;
    minDist.data = 50;
    std_msgs::Float32 relVel;
    std_msgs::Int16 col;
    
    CollisionDetection collisionDetector;
    bool crashed(false);
    col.data=0;

    while (ros::ok()) {
        ros::spinOnce();
        dist.data = estimate_min_dist(_odom, _odomObst);
        distPub.publish(dist);
        if (dist.data < minDist.data)
            minDist.data = dist.data;
        mindistPub.publish(minDist);
        relVel.data = calc_rel_velocity(_odom, _odomObst);
        relVelPub.publish(relVel);
        if (collisionDetector.check_for_collisions(calc_vehicle_edges(_odom), calc_vehicle_edges(_odomObst))) 
        {
            col.data=1;
            if (!crashed)
            {
                std::cout << "The vehicle crashed!\nRelative Velocity at the crash = " << relVel.data << std::endl;
                crashed = true;
            }
        }
        colPub.publish(col);
        r.sleep();
    }
    return 0;
}