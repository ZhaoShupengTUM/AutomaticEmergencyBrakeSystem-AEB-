cmake_minimum_required(VERSION 3.10)
project(pfas_nba_lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin)

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES pfas_nba_lib
)

add_executable(pfas_nba 
    src/main.cpp
    src/TrajectoryPrediction.cpp
    src/CorridorCreation.cpp
    src/CollisionDetection.cpp)

target_include_directories(pfas_nba PRIVATE include)

add_library(pfas_nba_lib
    src/TrajectoryPrediction.cpp
    src/CorridorCreation.cpp
    src/CollisionDetection.cpp)

target_include_directories(pfas_nba_lib PUBLIC include)