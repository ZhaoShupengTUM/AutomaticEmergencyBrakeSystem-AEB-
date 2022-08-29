// Copyright 2020 Hoffmann
// not for open source
#pragma once

#include <cmath>
#include "geometry_msgs/Point.h"
#include <tf/transform_datatypes.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2/utils.h>

namespace tod_helper::Geometry {
inline double calc_horizontal_distance(const geometry_msgs::Point &pt0, const geometry_msgs::Point &pt1) {
    tf::Vector3 v1{pt0.x, pt0.y, 0.0};
    tf::Vector3 v2{pt1.x, pt1.y, 0.0};
    return tf::tfDistance(v1, v2);
}

inline geometry_msgs::Point calc_relative_position(
    geometry_msgs::Point point_msg, geometry_msgs::Pose current_pose) {
    tf::Transform inverse;
    tf::poseMsgToTF(current_pose, inverse);
    tf::Transform transform = inverse.inverse();
    tf::Point p;
    pointMsgToTF(point_msg, p);
    tf::Point tf_p = transform * p;
    geometry_msgs::Point tf_point_msg;
    pointTFToMsg(tf_p, tf_point_msg);

    return tf_point_msg;
}

inline geometry_msgs::Point calcAbsoluteCoordinate(
    geometry_msgs::Point point_msg, geometry_msgs::Pose current_pose) {
    tf::Transform inverse;
    tf::poseMsgToTF(current_pose, inverse);
    tf::Point p;
    pointMsgToTF(point_msg, p);
    tf::Point tf_p = inverse * p;
    geometry_msgs::Point tf_point_msg;
    pointTFToMsg(tf_p, tf_point_msg);
    return tf_point_msg;
}

inline double calc_relative_angle(geometry_msgs::Pose waypoint_pose, geometry_msgs::Pose vehicle_pose) {
    geometry_msgs::Point relative_p1 = tod_helper::Geometry::calc_relative_position(
        waypoint_pose.position, vehicle_pose);
    geometry_msgs::Point p2;
    p2.x = 1.0;
    geometry_msgs::Point relative_p2 = tod_helper::Geometry::calc_relative_position(
        tod_helper::Geometry::calcAbsoluteCoordinate(p2, waypoint_pose), vehicle_pose);
    tf::Vector3 relative_waypoint_v(relative_p2.x - relative_p1.x, relative_p2.y - relative_p1.y,
                                    relative_p2.z - relative_p1.z);
    relative_waypoint_v.normalize();
    tf::Vector3 relative_pose_v(1, 0, 0);
    double angle = relative_pose_v.angle(relative_waypoint_v) * 180 / M_PI;

    return angle;
}

inline static double get_yaw_from_quaternion(const geometry_msgs::Quaternion& orientation) {
    return tf2::getYaw(orientation);
}

inline static double perpendicular_from_pt_on_line(const geometry_msgs::Point &pt, const geometry_msgs::Point &line0,
                                                   const geometry_msgs::Point &line1, geometry_msgs::Point &perpendicular) {
    double x0 = line0.x; double y0 = line0.y;
    double x1 = line1.x; double y1 = line1.y;
    double x2 = pt.x; double y2 = pt.y;
    // first convert line to normalized unit vector
    double dx = x1 - x0;
    double dy = y1 - y0;
    double mag = sqrt(dx*dx + dy*dy);
    dx /= mag;
    dy /= mag;
    // translate the point and get the dot product
    double lambda = (dx * (x2 - x0)) + (dy * (y2 - y0));
    perpendicular.x = (dx * lambda) + x0;
    perpendicular.y = (dy * lambda) + y0;
    return lambda;
}

}; // namespace tod_helper::Geometry
