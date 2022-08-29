// Copyright 2020 Feiler

#include <gtest/gtest.h>
#include "tod_msgs/Status.h"
#include "tod_helper/status/ChangeDetector.h"
#include <memory>

class stateIsTeleoperation : public ::testing::Test {
    protected:
        tod_msgs::Status status;
        std::unique_ptr<tod_helper::Status::TodStatusChangeDetector> detector;
        virtual void SetUp() {
            status.tod_status = tod_msgs::Status::TOD_STATUS_TELEOPERATION;
            detector = std::make_unique<tod_helper::Status::TodStatusChangeDetector>(
                &status, tod_msgs::Status::TOD_STATUS_TELEOPERATION);
        }
};

TEST_F(stateIsTeleoperation, correctlyInitialized) {
    ASSERT_EQ(detector->statusChanged(), false);
}

TEST_F(stateIsTeleoperation, detectChange) {
    ASSERT_EQ(detector->statusChanged(), false);
    status.tod_status = tod_msgs::Status::TOD_STATUS_IDLE;

    // change should be detected only once
    ASSERT_EQ(detector->statusChanged(), true);
    ASSERT_EQ(detector->statusChanged(), false);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
