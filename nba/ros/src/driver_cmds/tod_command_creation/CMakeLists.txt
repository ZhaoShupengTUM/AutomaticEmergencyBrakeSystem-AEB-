cmake_minimum_required(VERSION 2.8.3)
set(PROJECT_NAME tod_command_creation)
project(${PROJECT_NAME})

add_compile_options(-std=c++17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    tod_msgs
    tod_helper
)

catkin_package(
    CATKIN_DEPENDS roscpp tod_msgs tod_helper
)

add_subdirectory(src)

install(DIRECTORY
    launch
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
