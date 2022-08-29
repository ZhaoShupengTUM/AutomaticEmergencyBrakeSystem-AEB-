cmake_minimum_required(VERSION 2.8.3)
set(PROJECT_NAME tod_safety_monitoring)
project(${PROJECT_NAME})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(catkin REQUIRED COMPONENTS
    roscpp
    tod_msgs
    std_msgs
    message_generation
    )
find_package(rostest REQUIRED)

add_message_files(
    DIRECTORY msg
    FILES SafetyStatus.msg SafetyIssue.msg
    )

generate_messages(DEPENDENCIES std_msgs tod_safety_monitoring)

catkin_package(
    INCLUDE_DIRS include # The exported include paths (i.e. cflags) for the package
    LIBRARIES ${PROJECT_NAME} # The exported libraries from the project
    CATKIN_DEPENDS roscpp message_generation tod_msgs
    DEPENDS
    )



###### BUILD LIBRARY #######
add_library(${PROJECT_NAME}
    src/SafetyMonitor.cpp
    src/IssueBuffer.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${catkin_INCLUDE_DIRS}
    src
    PUBLIC include)

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${catkin_LIBRARIES}
    )

add_executable(safety_gate
    src/SafetyGateNode.cpp
    src/SafetyGate.cpp
)
target_include_directories(safety_gate PRIVATE
    ${catkin_INCLUDE_DIRS}
    src
    PUBLIC include)

add_dependencies(safety_gate ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(safety_gate
    PRIVATE
    ${catkin_LIBRARIES}
    )

install(DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

add_subdirectory(test)