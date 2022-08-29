cmake_minimum_required(VERSION 3.0.2)
set(PROJECT_NAME tod_helper)
project(${PROJECT_NAME})

set(DEPRECATION_FLAG "-Wno-deprecated-declarations -Wno-format")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEPRECATION_FLAG}")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(catkin REQUIRED COMPONENTS
    roscpp roslib tf tf2 tf2_geometry_msgs sensor_msgs geometry_msgs visualization_msgs nav_msgs tod_msgs)

catkin_package(
    INCLUDE_DIRS include
    CATKIN_DEPENDS roscpp roslib tf tf2 tf2_geometry_msgs sensor_msgs geometry_msgs visualization_msgs nav_msgs tod_msgs
)

option(NOT_OPEN_SOURCE "Build open source and not for open source" ON)
if (${NOT_OPEN_SOURCE})
    add_definitions(-DNOT_OPEN_SOURCE_MACRO=1)
else()
    add_definitions(-DNOT_OPEN_SOURCE_MACRO=0)
endif()
# PERCEPTION MODIFICATION TRUE MACRO
option(INCLUDE_PERCEPTION_MODIFICATION "Build incl. perc mod" ON)
if (${INCLUDE_PERCEPTION_MODIFICATION})
    add_definitions(-DPERCEPTION_MODIFICATION_TRUE_MACRO=1)
else()
    add_definitions(-DPERCEPTION_MODIFICATION_TRUE_MACRO=0)
endif()
#get_directory_property( DirDefs COMPILE_DEFINITIONS )
#message( "tod_helper: COMPILE_DEFINITIONS = ${DirDefs}" )

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
