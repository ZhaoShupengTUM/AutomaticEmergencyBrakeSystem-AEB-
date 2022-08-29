cmake_minimum_required(VERSION 2.8.3)
set(PROJECT_NAME tod_msgs)
project(${PROJECT_NAME})

find_package(catkin REQUIRED COMPONENTS
    std_msgs
    geometry_msgs
    message_generation
    sensor_msgs
    )

add_message_files(
    DIRECTORY msg
    FILES
        Color.msg # PERCEPTION MODIFICATION
        ColoredPoint.msg
        ColoredPolygon.msg
        KeyPress.msg
        Mesh.msg # PERCEPTION MODIFICATION
        ObjectData.msg
        ObjectList.msg
        PaketInfo.msg
        PrimaryControlCmd.msg
        SafetyDriverStatus.msg
        SecondaryControlCmd.msg
        Status.msg
        Trajectory.msg # NOT FOR OPEN SOURCE
        TrajectoryPoint.msg # NOT FOR OPEN SOURCE
        VehicleData.msg
        VideoInfo.msg
    )

add_service_files(
    DIRECTORY srv
    FILES
    InputDevice.srv
    Audio.srv # NOT FOR OPEN SOURCE
 )

generate_messages(
    DEPENDENCIES
    std_msgs
    geometry_msgs
    sensor_msgs
    )

catkin_package(
    INCLUDE_DIRS include
    )

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
