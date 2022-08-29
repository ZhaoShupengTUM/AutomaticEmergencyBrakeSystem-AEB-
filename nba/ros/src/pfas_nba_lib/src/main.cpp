#include <iostream>
#include <math.h>
#include "TrajectoryPrediction.h"
#include "CorridorCreation.h"
#include "CollisionDetection.h"

int main(){
    TrajectoryPrediction trajPred;
    CorridorCreation corrCreation;
    // Test Trajectory Prediction 
    std::cout << std::endl;
    std::cout << "# Test TrajectoryPrediction:" << std::endl;
    std::cout << "Braking Distance: " << trajPred.braking_distance(10, 6) << std::endl;
    std::cout << "Beta: " << trajPred.calc_beta(1.5) << std::endl;  
 //----------------------------------------------------------------------------------------------
    
    std::vector<Pose> traj = trajPred.predict_vehicle_trajectory(0, 100);
    std::cout << "Size of Trajectory: " << traj.size() << std::endl;

    std::cout << "x-Positions: ";
    for (const Pose& pose : traj)
        std::cout << pose.get_x() << ", ";
    
    std::cout << std::endl << std::endl;

    std::vector<Pose> traj2 = trajPred.predict_vehicle_trajectory(0.5, 20);
    std::cout << "Trajectory Pose at Position 20: ("<< traj2.at(20).get_x()
        << ", " << traj2.at(20).get_y() << ")" << std::endl;

    std::cout << std::endl << "------------" << std::endl;
    
    // Test calc_vehicle_front_edges:
    std::cout << "# Test CorridorCreation - calc_vehicle_front_edges" << std::endl;
    Pose poseCoM{10, 5, 0.4};
    Pose poseFL{0, 0, 0};
    Pose poseFR{0, 0, 0};
    corrCreation.calc_vehicle_front_edges(poseCoM, poseFR, poseFL);
    std::cout << "PoseFR: (" << poseFR.get_x() << ", " << poseFR.get_y() << ")" << std::endl;
    std::cout << "PoseFR: (" << poseFL.get_x() << ", " << poseFL.get_y() << ")" << std::endl;
    std::cout << std::endl;

    // Test Final:
    std::cout << "# Test - Final" << std::endl;
    double brakingDistance = trajPred.braking_distance(10, 6);
    std::vector<Pose> predictedTrajectory = trajPred.predict_vehicle_trajectory(-0.4, brakingDistance);
    std::vector<Pose> predictedCorridor = corrCreation.calc_corridor(predictedTrajectory);
    std::cout << predictedCorridor.at(60).get_x() << ", " << predictedCorridor.at(60).get_y() << std::endl;
    std::cout << std::endl << "------------" << std::endl;


    // Test Collision Detection
    std::cout << "# Test Collision Detection" << std::endl;
    std::vector<Pose> testCorridor;
    testCorridor.emplace_back(0.0,0.0,0.0);
    testCorridor.emplace_back(5.0,0.0,0.0);
    testCorridor.emplace_back(5.0,5.0,0.0);
    testCorridor.emplace_back(0.0,5.0,0.0);

    std::vector<Pose> poses;
    poses.emplace_back(2.0,-1.0,0.0); // outside
    poses.emplace_back(2.0,2.0,0.0); // inside
    poses.emplace_back(2.0,3.0,0.0); // inside
    poses.emplace_back(2.0,6.0,0.0); // outside
    poses.emplace_back(6.0,2.0,0.0); // outside

    CollisionDetection collisionDetector;
    collisionDetector.check_for_collisions(testCorridor, poses);
}