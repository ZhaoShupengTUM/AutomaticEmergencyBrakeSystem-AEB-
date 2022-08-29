// Copyright 2021 Hoffmann

#include <gtest/gtest.h>
#include "tod_helper/trajectory/Helpers.h"
#include "tod_msgs/Trajectory.h"
#include <iostream>

double spacingBetweenPointsInM { 0.3 };
int numberOfTrajPoints { 30 };
    
tod_msgs::Trajectory initTrajectory() {
    tod_msgs::Trajectory straightTrajectory;
    for ( int trajPointIt = 0; trajPointIt != numberOfTrajPoints; ++ trajPointIt ) {
        tod_msgs::TrajectoryPoint tmpPoint;
        tmpPoint.pose.pose.position.x = (double) trajPointIt * spacingBetweenPointsInM;
        straightTrajectory.points.push_back(tmpPoint);
    }
    return straightTrajectory;
}

geometry_msgs::Pose initPose(double x){
    geometry_msgs::Pose pose;
    pose.position.x= x;
    pose.orientation.w = 1.0;
    return pose;
}

class StraightTrajectoryFixture : public ::testing::TestWithParam<double> {
protected:
    tod_msgs::Trajectory trajectory;
    geometry_msgs::Pose pose;

    virtual void SetUp() {
        trajectory = initTrajectory();
        pose = initPose(0.0);
    }
};

TEST_P(StraightTrajectoryFixture, get_distance_of_trajectory_points) {
    pose.position.x = GetParam();
    tod_msgs::TrajectoryPtr traj(new tod_msgs::Trajectory(trajectory));
    std::vector<float> distances = tod_helper::Trajectory::get_distance_of_trajectory_points(traj, pose.position);
/*     std::for_each(distances.begin(), distances.end(), [](auto &n){std::cout << n << "; "; }); */
    ASSERT_FLOAT_EQ(distances.at(0), GetParam());
}

TEST_P(StraightTrajectoryFixture, accumulated_distance) {
    pose.position.x = GetParam();
    tod_msgs::TrajectoryPtr traj(new tod_msgs::Trajectory(trajectory));
    std::vector<double> distances = tod_helper::Trajectory::accumulated_distance(traj);
/*     std::for_each(distances.begin(), distances.end(), [](auto &n){std::cout << n << "; "; }); */
/*     ROS_ERROR_STREAM(distances.size() << "; " <<  trajectory.points.size()); */
    ASSERT_FLOAT_EQ(distances.at(numberOfTrajPoints-1), (numberOfTrajPoints-1)*spacingBetweenPointsInM);
}

TEST_P(StraightTrajectoryFixture, get_closest_trajectory_point) {
    pose.position.x = GetParam();
    tod_msgs::TrajectoryPtr traj(new tod_msgs::Trajectory(trajectory));
    int closestPoint = tod_helper::Trajectory::get_closest_trajectory_point(traj, pose);
    int result = std::round(GetParam()/spacingBetweenPointsInM);
    if (result > (numberOfTrajPoints-1)) 
        result = numberOfTrajPoints-1;
    ASSERT_EQ(closestPoint, result);
}

TEST_P(StraightTrajectoryFixture, get_closest_trajectory_point_in_x_dir) {
    pose.position.x = GetParam();
    tod_msgs::TrajectoryPtr traj(new tod_msgs::Trajectory(trajectory));
    int closestPoint = tod_helper::Trajectory::get_closest_trajectory_point_in_x_dir(traj, pose);
    int result = std::ceil(GetParam()/spacingBetweenPointsInM);
    if (result > (numberOfTrajPoints-1)) 
        result = -1;
    ASSERT_EQ(closestPoint, result);
}

TEST_P(StraightTrajectoryFixture, is_point_ahead_in_x_dir) {
    pose.position.x = GetParam();
    tod_msgs::TrajectoryPtr traj(new tod_msgs::Trajectory(trajectory));
    bool isahead = tod_helper::Trajectory::is_point_ahead_in_x_dir(traj->points.at(16).pose.pose.position, pose);
    ASSERT_EQ(isahead, false);
}

/* TEST_P(StraightTrajectoryFixture, Test_calc_relative_position_in_x) {// Todo: Move to geometry Helpers
    pose.position.x = GetParam();
    tod_msgs::TrajectoryPtr traj(new tod_msgs::Trajectory(trajectory)); //Convert To TrajPtr
    double relPosX = GeometryHelpers::calc_relative_position(traj->points.at(16).pose.pose.position, pose).x;
    ASSERT_FLOAT_EQ(relPosX, -0.11);
} */

INSTANTIATE_TEST_CASE_P(
        TrajectoryHelperTests,
        StraightTrajectoryFixture,
        ::testing::Values(4.91, 9.0));

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
