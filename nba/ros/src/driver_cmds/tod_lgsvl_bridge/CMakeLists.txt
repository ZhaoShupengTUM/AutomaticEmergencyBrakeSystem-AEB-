cmake_minimum_required(VERSION 2.8.3)
project(tod_lgsvl_bridge)

add_compile_options(-std=c++17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    std_msgs
    tod_msgs
    lgsvl_msgs
    autoware_msgs
    tod_vehicle_config
    tf2
    tf2_ros
)
catkin_package(
    INCLUDE_DIRS #include
    CATKIN_DEPENDS roscpp tod_msgs lgsvl_msgs tod_vehicle_config
    )

include_directories(
    ${catkin_INCLUDE_DIRS}
    ../../devel/include #Todo: Why required????
)

add_subdirectory(src)

install(DIRECTORY 
    launch
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
