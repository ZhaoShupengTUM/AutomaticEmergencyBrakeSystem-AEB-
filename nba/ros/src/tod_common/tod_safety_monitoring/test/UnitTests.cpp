// Copyright 2021 Hoffmann

#include <gtest/gtest.h>
#include "ros/ros.h"
#include <iostream>
#include "tod_safety_monitoring/SafetyMonitor.h"

class TestSuite : public ::testing::Test {
    public:
        TestSuite(){}
        ~TestSuite(){}
        ros::NodeHandle* node;
        SafetyMonitor* monitor;

        void SetUp() override {
            ::testing::Test::SetUp();
            node = new ros::NodeHandle();
            monitor = new SafetyMonitor(*node);
        }
        void TearDown() override {
            ros::shutdown();
            delete this->monitor;
            delete this->node;
            ::testing::Test::TearDown();
        }
};

TEST_F(TestSuite, testCase1) {
    monitor->min_value("test_error_min", 10, 5, tod_safety_monitoring::SafetyIssue::WARNING, "The minimum value was exceeded within a test");
    monitor->min_value("test_error_min", 10, 5, tod_safety_monitoring::SafetyIssue::WARNING, "The minimum value was exceeded within a test");
    monitor->min_value("test_error_min2", 10, 5, tod_safety_monitoring::SafetyIssue::WARNING, "The minimum value was exceeded within a test");
    monitor->min_value("test_error_min", 10, 5, tod_safety_monitoring::SafetyIssue::ERROR, "The minimum value was exceeded within a test");
    monitor->min_value("test_error_min", 4, 5, tod_safety_monitoring::SafetyIssue::ERROR, "The minimum value was exceeded within a test");
    ASSERT_EQ(monitor->get_number_of_issues(), 4);
    ASSERT_EQ(monitor->get_number_by_level(tod_safety_monitoring::SafetyIssue::WARNING), 3);
    //Todo: get number by level;
}


int main(int argc, char** argv) {
    ros::init(argc, argv, "test_node");
/*  if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug)) {
        ros::console::notifyLoggerLevelsChanged();
    } */
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
