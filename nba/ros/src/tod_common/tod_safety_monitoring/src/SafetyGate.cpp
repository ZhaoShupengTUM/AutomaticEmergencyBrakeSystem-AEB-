#include "tod_safety_monitoring/SafetyGate.h"

SafetyGate::SafetyGate(ros::NodeHandle &nh) 
        : _nh(nh),
        _isRunning(true) {
    bool debug{false};
    _nh.getParam(ros::this_node::getName() + "/debug", debug);
    if (debug) // print ROS_DEBUG
        if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug))
            ros::console::notifyLoggerLevelsChanged();

}

SafetyGate::~SafetyGate() {
   _isRunning = false;
}

void SafetyGate::run() {
    ros::Rate r(100);
    while (ros::ok() && _isRunning){
        update_topic_list();
        // publish Traj, constantly update Traj only if tested
        ros::spinOnce();
        r.sleep();
    }
}

void SafetyGate::start() {
    run();
}

std::vector<std::string> SafetyGate::get_topic_list(const std::string& msg_type) {
    ros::master::V_TopicInfo topic_info;
    ros::master::getTopics(topic_info);
    std::vector<std::string> topicList;
    for (ros::master::V_TopicInfo::const_iterator it = topic_info.begin(); it != topic_info.end(); it++) {
        if (it->datatype == msg_type){
            topicList.push_back(it->name);
        }
    }
    return topicList;
}

void SafetyGate::update_topic_list() {
   std::vector<std::string> topics = get_topic_list("tod_safety_monitoring/SafetyStatus");
    for(auto topic : topics){
        if (_topicsToMonitor.find(topic) == _topicsToMonitor.end()){
            _topicsToMonitor.insert(topic);
            create_new_monitoring_object(topic);
        }
    }
}

void SafetyGate::create_new_monitoring_object(std::string& topic) {
    auto object = _monitoringObjects.emplace_back(
        std::make_shared<MonitoringObject>(topic));
    object->subscriber = _nh.subscribe<tod_safety_monitoring::SafetyStatus>(topic, 10,
       boost::bind(&SafetyGate::callback_safety_status,this,boost::placeholders::_1, object));
    ROS_DEBUG_STREAM("New Subscriber for Topic " << topic << " created");
}

void SafetyGate::callback_safety_status(const tod_safety_monitoring::SafetyStatusConstPtr& msg,
        std::shared_ptr<MonitoringObject> obj) {
}

// check if topic visible if nothing is published