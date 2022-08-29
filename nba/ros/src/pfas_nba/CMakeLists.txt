cmake_minimum_required(VERSION 2.8.3)
project(pfas_nba)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    nav_msgs
    tod_msgs
    lgsvl_msgs
    geometry_msgs
    sensor_msgs
    autoware_msgs
    pfas_nba_lib
)

catkin_package(
)

add_executable(CollisionDetection src/CollisionDetectionNode.cpp)
target_link_libraries(CollisionDetection ${catkin_LIBRARIES})
target_include_directories(CollisionDetection PRIVATE ${catkin_INCLUDE_DIRS})

add_executable(CorridorCreation src/CorridorCreationNode.cpp)
target_link_libraries(CorridorCreation ${catkin_LIBRARIES})
target_include_directories(CorridorCreation PRIVATE ${catkin_INCLUDE_DIRS})

add_executable(TrajectoryPrediction src/TrajectoryPredictionNode.cpp)
target_link_libraries(TrajectoryPrediction ${catkin_LIBRARIES})
target_include_directories(TrajectoryPrediction PRIVATE ${catkin_INCLUDE_DIRS})

add_executable(Autopilot src/AutopilotNode.cpp)
target_link_libraries(Autopilot ${catkin_LIBRARIES})
target_include_directories(Autopilot PRIVATE ${catkin_INCLUDE_DIRS})

add_executable(ScenarioEvaluation src/ScenarioEvaluationNode.cpp)
target_link_libraries(ScenarioEvaluation ${catkin_LIBRARIES})
target_include_directories(ScenarioEvaluation PRIVATE ${catkin_INCLUDE_DIRS})