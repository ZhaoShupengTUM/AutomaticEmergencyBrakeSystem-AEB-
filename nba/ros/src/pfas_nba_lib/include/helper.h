#pragma once

#include <vector>
#include <Pose.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_datatypes.h>
#include "VehicleParams.h"

double calc_dist_between_poses(Pose point1, Pose point2){
    return std::sqrt(std::pow(point1.get_x()-point2.get_x(), 2) + std::pow(point1.get_y()-point2.get_y(), 2));
}

std::vector<Pose> calc_vehicle_edges(nav_msgs::Odometry odom){
    Pose fr, fl, rr, rl;
    tf::Quaternion quat(odom.pose.pose.orientation.x, odom.pose.pose.orientation.y, odom.pose.pose.orientation.z, odom.pose.pose.orientation.w);
    Pose com(odom.pose.pose.position.x, odom.pose.pose.position.y, tf::getYaw(quat));
    std::vector<Pose> edges;
    
    fr.set_x(com.get_x() + VehicleParams::distance_front_bumper * std::cos(float(com.get_yaw())) + (VehicleParams::width_edge_to_edge/2) * std::sin(float(com.get_yaw())));
    fr.set_y(com.get_y() + VehicleParams::distance_front_bumper * std::sin(float(com.get_yaw())) - (VehicleParams::width_edge_to_edge/2) * std::cos(float(com.get_yaw())));
    edges.push_back(fr);

    fl.set_x(com.get_x() + VehicleParams::distance_front_bumper * std::cos(float(com.get_yaw())) - (VehicleParams::width_edge_to_edge/2) * std::sin(float(com.get_yaw())));
    fl.set_y(com.get_y() + VehicleParams::distance_front_bumper * std::sin(float(com.get_yaw())) + (VehicleParams::width_edge_to_edge/2) * std::cos(float(com.get_yaw())));
    edges.push_back(fl);

    rr.set_x(com.get_x() - VehicleParams::distance_rear_bumper * std::cos(float(com.get_yaw())) + (VehicleParams::width_edge_to_edge/2) * std::sin(float(com.get_yaw())));
    rr.set_y(com.get_y() - VehicleParams::distance_rear_bumper * std::sin(float(com.get_yaw())) - (VehicleParams::width_edge_to_edge/2) * std::cos(float(com.get_yaw())));
    edges.push_back(rr);

    rl.set_x(com.get_x() - VehicleParams::distance_rear_bumper * std::cos(float(com.get_yaw())) - (VehicleParams::width_edge_to_edge/2) * std::sin(float(com.get_yaw())));
    rl.set_y(com.get_y() - VehicleParams::distance_rear_bumper * std::sin(float(com.get_yaw())) + (VehicleParams::width_edge_to_edge/2) * std::cos(float(com.get_yaw())));
    edges.push_back(rl);

    return edges;
}

std::vector<Pose> calc_multiple_edges(nav_msgs::Odometry odom, int numberOfEdges = 10){
    Pose fr, fl, rr, rl;
    tf::Quaternion quat(odom.pose.pose.orientation.x, odom.pose.pose.orientation.y, odom.pose.pose.orientation.z, odom.pose.pose.orientation.w);
    Pose com(odom.pose.pose.position.x, odom.pose.pose.position.y, tf::getYaw(quat));
    std::vector<Pose> edges;
    
    std::vector<double> widths;
    std::vector<double> distances_front;
    std::vector<double> distances_rear;

    for (size_t i = 0; i <= numberOfEdges; i++)
    {
        widths.push_back(i * VehicleParams::width_edge_to_edge/numberOfEdges);
        distances_front.push_back(i * VehicleParams::distance_front_bumper/numberOfEdges);
        distances_rear.push_back(i * VehicleParams::distance_rear_bumper/numberOfEdges);
    }
    
    for (size_t i = 0; i < numberOfEdges; i++)
    {    
        fr.set_x(com.get_x() + distances_front[i] * std::cos(float(com.get_yaw())) + (VehicleParams::width_edge_to_edge/2) * std::sin(float(com.get_yaw())));
        fr.set_y(com.get_y() + distances_front[i] * std::sin(float(com.get_yaw())) - (VehicleParams::width_edge_to_edge/2) * std::cos(float(com.get_yaw())));
        edges.push_back(fr);

        fl.set_x(com.get_x() + distances_front[i] * std::cos(float(com.get_yaw())) - (VehicleParams::width_edge_to_edge/2) * std::sin(float(com.get_yaw())));
        fl.set_y(com.get_y() + distances_front[i] * std::sin(float(com.get_yaw())) + (VehicleParams::width_edge_to_edge/2) * std::cos(float(com.get_yaw())));
        edges.push_back(fl);

        rr.set_x(com.get_x() - distances_rear[i] * std::cos(float(com.get_yaw())) + (VehicleParams::width_edge_to_edge/2) * std::sin(float(com.get_yaw())));
        rr.set_y(com.get_y() - distances_rear[i] * std::sin(float(com.get_yaw())) - (VehicleParams::width_edge_to_edge/2) * std::cos(float(com.get_yaw())));
        edges.push_back(rr);

        rl.set_x(com.get_x() - distances_rear[i] * std::cos(float(com.get_yaw())) - (VehicleParams::width_edge_to_edge/2) * std::sin(float(com.get_yaw())));
        rl.set_y(com.get_y() - distances_rear[i] * std::sin(float(com.get_yaw())) + (VehicleParams::width_edge_to_edge/2) * std::cos(float(com.get_yaw())));
        edges.push_back(rl);    
    }

    for (size_t i = 0; i < numberOfEdges; i++)
    {    
        fr.set_x(com.get_x() + VehicleParams::distance_front_bumper * std::cos(float(com.get_yaw())) + (widths[i]/2) * std::sin(float(com.get_yaw())));
        fr.set_y(com.get_y() + VehicleParams::distance_front_bumper * std::sin(float(com.get_yaw())) - (widths[i]/2) * std::cos(float(com.get_yaw())));
        edges.push_back(fr);

        fl.set_x(com.get_x() + VehicleParams::distance_front_bumper * std::cos(float(com.get_yaw())) - (widths[i]/2) * std::sin(float(com.get_yaw())));
        fl.set_y(com.get_y() + VehicleParams::distance_front_bumper * std::sin(float(com.get_yaw())) + (widths[i]/2) * std::cos(float(com.get_yaw())));
        edges.push_back(fl);

        rr.set_x(com.get_x() - VehicleParams::distance_rear_bumper * std::cos(float(com.get_yaw())) + (widths[i]/2) * std::sin(float(com.get_yaw())));
        rr.set_y(com.get_y() - VehicleParams::distance_rear_bumper * std::sin(float(com.get_yaw())) - (widths[i]/2) * std::cos(float(com.get_yaw())));
        edges.push_back(rr);

        rl.set_x(com.get_x() - VehicleParams::distance_rear_bumper * std::cos(float(com.get_yaw())) - (widths[i]/2) * std::sin(float(com.get_yaw())));
        rl.set_y(com.get_y() - VehicleParams::distance_rear_bumper * std::sin(float(com.get_yaw())) + (widths[i]/2) * std::cos(float(com.get_yaw())));
        edges.push_back(rl);    
    }
    return edges;
}

double estimate_min_dist(nav_msgs::Odometry odom1, nav_msgs::Odometry odom2) {
    std::vector<Pose> rect1 = calc_multiple_edges(odom1);
    std::vector<Pose> rect2 = calc_multiple_edges(odom2);

    double min_dist = calc_dist_between_poses(rect1[0], rect2[0]);

    for (auto pose1 : rect1) {
        for (auto pose2: rect2) {
            double dist = calc_dist_between_poses(pose1, pose2);
            if (dist < min_dist) {
                min_dist = dist; 
            }
        }
    }
    
    return min_dist;
}
