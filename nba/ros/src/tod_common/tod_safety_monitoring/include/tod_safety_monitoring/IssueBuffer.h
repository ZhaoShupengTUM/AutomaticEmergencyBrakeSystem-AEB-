#pragma once

#include "ros/ros.h"
#include "ros/debug.h"
#include <vector>
#include <map>
#include <thread>
#include <tod_safety_monitoring/SafetyStatus.h>

class IssueBuffer{
    public:
        IssueBuffer();
        ~IssueBuffer();
        void add_issue(tod_safety_monitoring::SafetyIssue issue);
        std::vector<tod_safety_monitoring::SafetyIssue> get_and_clear_buffer();
        std::vector<tod_safety_monitoring::SafetyIssue> get_buffer();
        std::vector<tod_safety_monitoring::SafetyIssue> get_buffer(uint8_t level);
        int get_size();


    private:
        std::map<uint8_t, std::vector<tod_safety_monitoring::SafetyIssue>> _buffer;

};



