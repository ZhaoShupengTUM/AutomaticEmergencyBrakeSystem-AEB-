// Copyright 2022 Florian Pfab
#include "ros/ros.h"
#include <autoware_msgs/VehicleCmd.h>

int main(int argc, char **argv) {
    ros::init(argc, argv, "Autopilot");
    ros::NodeHandle n("~");
    ros::Rate r(100);
    std::string topic_name;
    if (n.hasParam("topic_name"))
        n.getParam("topic_name", topic_name);
    else
        topic_name="/vehicle_cmd";

    ros::Publisher vehCmdPub = n.advertise<autoware_msgs::VehicleCmd>(topic_name, 10);
    
    autoware_msgs::VehicleCmd vehCmd;

    ros::Time begin(ros::Time::now());
    double start_velocity, target_velocity, velocity_delay, target_steering, steering_delay, target_acceleration, acceleration_delay;
    n.getParam("start_velocity", start_velocity);
    n.getParam("target_velocity", target_velocity);
    n.getParam("velocity_delay", velocity_delay);
    n.getParam("target_steering", target_steering);
    n.getParam("steering_delay", steering_delay);
    n.getParam("target_acceleration", target_acceleration);
    n.getParam("acceleration_delay", acceleration_delay);

    if (!n.hasParam("start_velocity"))
    {
        start_velocity = 0.0;
    }

    double velocity{start_velocity};

    while (ros::ok()) {
        vehCmd.twist_cmd.twist.linear.x = start_velocity;
        if (n.hasParam("target_velocity") && n.hasParam("target_velocity"))
        {
            if ((ros::Time::now()-begin) <= ros::Duration(velocity_delay))
                vehCmd.twist_cmd.twist.linear.x = start_velocity;
            else
                vehCmd.twist_cmd.twist.linear.x = target_velocity;
        }

        if (n.hasParam("steering_delay") && n.hasParam("target_steering"))
        {
            if ((ros::Time::now()-begin) <= ros::Duration(steering_delay))
                vehCmd.twist_cmd.twist.angular.z = 0;
            else
                vehCmd.twist_cmd.twist.angular.z = target_steering;
        }

        if (n.hasParam("acceleration_delay") && n.hasParam("target_acceleration"))
        {
            if ((ros::Time::now()-begin) <= ros::Duration(acceleration_delay))
                vehCmd.twist_cmd.twist.linear.x = velocity;
            else
                velocity += 0.01 * target_acceleration;
                vehCmd.twist_cmd.twist.linear.x = velocity < 0.0 ? 0.0 : velocity;
        }

        vehCmdPub.publish(vehCmd);
        ros::spinOnce();
        r.sleep();
    }
    return 0;
}
