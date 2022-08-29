// Copyright 2021 Feiler

#include <gtest/gtest.h>
#include <tod_helper/trajectory/BrakeIntoStillStand.h>
#include "tod_msgs/Trajectory.h"
#include <iostream>

double goalVelocityInMS { 2.0 };
double spacingBetweenPointsInM { 0.3 };
int numberOfTrajPoints { 30 };

int indexOfDesiredStandstill { 20 };
double brakeAccelerationMS2 { -2.0 };

tod_msgs::Trajectory initTrajectory() {
    tod_msgs::Trajectory straightTrajectory;
    for ( int trajPointIt = 0; trajPointIt != numberOfTrajPoints; ++trajPointIt ) {
        tod_msgs::TrajectoryPoint tmpPoint;
        tmpPoint.twist.twist.linear.x = goalVelocityInMS;
        tmpPoint.pose.pose.position.x = (double) trajPointIt * spacingBetweenPointsInM;
//        std::cout <<  goalVelocityInMS << "  " << tmpPoint.pose.pose.position.x << std::endl;
        straightTrajectory.points.push_back(tmpPoint);
    }
    return straightTrajectory;
}

int getIndexLastUntouchedPoint() {
    double brakeDistance = std::abs(std::pow(goalVelocityInMS, 2) / (2.00 * brakeAccelerationMS2));
    int numberOfBrakeTrajPoints = (int) std::floor(brakeDistance/spacingBetweenPointsInM) + 1;
    int indexOfLastUntouchedPoint = indexOfDesiredStandstill - numberOfBrakeTrajPoints;
    return indexOfLastUntouchedPoint;
}

class BrakeIntoStillStand : public ::testing::Test {
    protected:
        tod_msgs::Trajectory straightTrajectory;
        virtual void SetUp() {
            straightTrajectory = initTrajectory();
        }
};

TEST_F(BrakeIntoStillStand, CheckEndPoints) {
    tod_helper::Trajectory::brakeIntoStillStand(straightTrajectory, indexOfDesiredStandstill,
                                            goalVelocityInMS, brakeAccelerationMS2);

    for ( int iterator = indexOfDesiredStandstill; iterator != numberOfTrajPoints; ++iterator ) {
        ASSERT_DOUBLE_EQ(straightTrajectory.points.at(iterator).twist.twist.linear.x, 0.0);
    }
}

TEST_F(BrakeIntoStillStand, CheckUntouchedPoints) {
    tod_helper::Trajectory::brakeIntoStillStand(straightTrajectory, indexOfDesiredStandstill,
                                            goalVelocityInMS, brakeAccelerationMS2);

    int indexOfLastUntouchedPoint = getIndexLastUntouchedPoint();

    for ( int iterator = 0; iterator != indexOfLastUntouchedPoint; ++iterator ) {
        ASSERT_DOUBLE_EQ(straightTrajectory.points.at(iterator).twist.twist.linear.x, goalVelocityInMS);
    }
}

TEST_F(BrakeIntoStillStand, CheckVelocityModifiedPoints) {
    tod_helper::Trajectory::brakeIntoStillStand(straightTrajectory, indexOfDesiredStandstill,
                                            goalVelocityInMS, brakeAccelerationMS2);

    int indexOfLastUntouchedPoint = getIndexLastUntouchedPoint();

    for ( int iterator = indexOfLastUntouchedPoint+1; iterator != indexOfDesiredStandstill; ++iterator ) {
        ASSERT_LT(straightTrajectory.points.at(iterator).twist.twist.linear.x, goalVelocityInMS);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
