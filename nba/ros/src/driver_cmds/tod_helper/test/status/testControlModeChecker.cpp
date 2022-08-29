// Copyright 2020 Feiler
#include <gtest/gtest.h>
#include "ros/ros.h"
#include "tod_msgs/Status.h"
#include "tod_helper/status/ControlModeChecker.h"
#include <exception>

class ControlModeCheckerTests : public ::testing::Test {
    protected:
        tod_msgs::Status _status;
};

TEST_F(ControlModeCheckerTests, modeIsChosen) {
    _status.operator_control_mode = (uint8_t) tod_msgs::Status::CONTROL_MODE_DIRECT;
    tod_helper::Status::ControlModeChecker controlModeChoser(tod_msgs::Status::CONTROL_MODE_DIRECT,
        &_status);
    EXPECT_TRUE(controlModeChoser.modeIsChosen());
}

TEST_F(ControlModeCheckerTests, modeIsNotChosen) {
    _status.operator_control_mode = tod_msgs::Status::CONTROL_MODE_PERCEPTION_MODIFICATION;
    tod_helper::Status::ControlModeChecker controlModeChoser((uint8_t) tod_msgs::Status::CONTROL_MODE_DIRECT,
        &_status);
    EXPECT_FALSE(controlModeChoser.modeIsChosen());
}

TEST(ModeChecker, statusMsgDoesNotExist) {
    tod_helper::Status::ControlModeChecker controlModeChoser((uint8_t) tod_msgs::Status::CONTROL_MODE_DIRECT,
        nullptr);
    EXPECT_THROW(controlModeChoser.modeIsChosen(), std::exception);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
