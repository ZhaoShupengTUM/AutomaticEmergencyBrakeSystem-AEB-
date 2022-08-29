#pragma once

#include "ros/ros.h"
#include "ros/debug.h"
#include <vector>
#include <map>
#include <thread>
#include <tod_safety_monitoring/SafetyStatus.h>
#include <tod_safety_monitoring/IssueBuffer.h>
struct SafetyTest {
    //result
    //test func -- provide some generals, option for specific ones

};

class SafetyMonitor{
    public:
        SafetyMonitor(ros::NodeHandle &nh);
        ~SafetyMonitor();
        void start();
        void min_value(const std::string& key, const float value, const float min_value, const uint8_t type, const std::string& description);
        void add_safety_issue(const tod_safety_monitoring::SafetyIssue& issue);
        int get_number_by_level(uint8_t level);
        int get_number_of_issues();
        std::vector<tod_safety_monitoring::SafetyIssue> get_all_issues();

    private:
        ros::NodeHandle _nh;
        std::thread _thread;
        std::string _nodeName;
        void run();
        bool _isRunning;
        ros::Publisher _statusPub;
        std::unique_ptr<IssueBuffer> _issueBuffer;

};