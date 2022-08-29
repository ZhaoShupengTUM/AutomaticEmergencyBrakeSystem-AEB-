cmake_minimum_required(VERSION 3.0.2)
project(pfas)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(
  INCLUDE_DIRS
  CATKIN_DEPENDS
)

add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
target_include_directories(talker PRIVATE ${catkin_INCLUDE_DIRS})

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
target_include_directories(listener PRIVATE ${catkin_INCLUDE_DIRS})