#pragma once

#include "ros/ros.h"
#include "ros/debug.h"
#include <vector>
#include <map>
#include <thread>
#include <tod_safety_monitoring/SafetyStatus.h>
#include "std_msgs/String.h"
#include <tod_safety_monitoring/IssueBuffer.h>
#include "sensor_msgs/Image.h"

enum eGateStatus {
    STARTUP = 0,
    INITIALIZED = 1
};

struct MonitoringObject {
    ros::Subscriber subscriber;
    ros::Time lastStamp;
    std::string topicName;
    MonitoringObject(const std::string& topic) { topicName = topic; }
    //is_mandatory
    //status ?!
};

class SafetyGate{
    public:
        SafetyGate(ros::NodeHandle &nh);
        ~SafetyGate();
        void start();
        void update_topic_list();

    private:
        ros::NodeHandle _nh;
        void run();
        bool _isRunning;
        std::vector<std::string> get_topic_list(const std::string& msg_type);
        std::set<std::string> _topicsToMonitor;
        std::vector<std::shared_ptr<MonitoringObject>> _monitoringObjects;
        void create_new_monitoring_object(std::string& topic);
        void callback_safety_status(const tod_safety_monitoring::SafetyStatusConstPtr& msg,
            std::shared_ptr<MonitoringObject> obj);
};





