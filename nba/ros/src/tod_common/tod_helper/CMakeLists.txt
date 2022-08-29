cmake_minimum_required(VERSION 2.8.3)
set(PROJECT_NAME tod_helper)
project(${PROJECT_NAME})

set(DEPRECATION_FLAG "-Wno-deprecated-declarations -Wno-format")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEPRECATION_FLAG}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED COMPONENTS
    roscpp roslib tf2 sensor_msgs geometry_msgs visualization_msgs nav_msgs tod_msgs)

catkin_package(
    INCLUDE_DIRS include
    CATKIN_DEPENDS roscpp roslib tf2 sensor_msgs geometry_msgs visualization_msgs nav_msgs tod_msgs
)

add_subdirectory(src)

install(DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

# NOT FOR OPEN SOURCE
option(TEST "Build test targets" OFF)
if (${TEST})
    add_subdirectory(test/geometry)
    add_subdirectory(test/status)
    add_subdirectory(test/trajectory)
else()
    # message("skipping ${PROJECT_NAME} test targets")
endif()
