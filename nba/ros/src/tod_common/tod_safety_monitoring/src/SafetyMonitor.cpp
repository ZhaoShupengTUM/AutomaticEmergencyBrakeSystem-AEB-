#include "tod_safety_monitoring/SafetyMonitor.h"

SafetyMonitor::SafetyMonitor(ros::NodeHandle &nh) 
        : _nh(nh),
        _isRunning(true) {
    _nodeName = ros::this_node::getName();
    _statusPub = _nh.advertise<tod_safety_monitoring::SafetyStatus>(_nodeName + "/node_status", 5);
    _issueBuffer = std::make_unique<IssueBuffer>();
    ROS_DEBUG_STREAM("SafetyMonitor for Node " << ros::this_node::getName() << " started!");
}

SafetyMonitor::~SafetyMonitor() {
   _isRunning = false;
   if (_thread.joinable())
        _thread.join();
}

void SafetyMonitor::run() {
    ros::Rate r(100);
    while (ros::ok() && _isRunning){
        tod_safety_monitoring::SafetyStatus status;
        status.nodeName = _nodeName;
        status.issues = _issueBuffer->get_and_clear_buffer();
        _statusPub.publish(status);
        r.sleep();
    }
}

void SafetyMonitor::start() {
    _thread = std::thread(&SafetyMonitor::run, this);
}

void SafetyMonitor::min_value(const std::string& key, const float value, const float min_value,
        const uint8_t level, const std::string& description) {
    if (value >= min_value){
        tod_safety_monitoring::SafetyIssue issue;
        issue.header.stamp = ros::Time::now();
        issue.errorDescription = description;
        issue.errorLevel = level;
        issue.parentNode = _nodeName;
        issue.errorKey = key;
        add_safety_issue(issue);    
    }
}

void SafetyMonitor::add_safety_issue(const tod_safety_monitoring::SafetyIssue& issue) {
    _issueBuffer->add_issue(issue);
}

int SafetyMonitor::get_number_by_level(uint8_t level) {
    return _issueBuffer->get_buffer(level).size();
}

int SafetyMonitor::get_number_of_issues() {
    return _issueBuffer->get_buffer().size();   
}

// Next steps: 
// safety gate
// avoid dublicates (If same node, same error level and same key)
// include in software
// tests
