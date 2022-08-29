// Copyright 2020 TUMFTM
#pragma once
#include <string>

namespace tod_network {

static const int RX_MQTT = 1883; // same for operator and vehicle
static const std::string AutoboxIp = "192.168.140.6"; // not for open source

enum VehiclePorts { // only what is sent via udp
    RX_PRIMARYCONTROL_COMMAND = 70000,
    RX_CLOTHOIDCONTROL_COMMAND = 70001,         // NOT FOR OPEN SOURCE
    // RX_SOMETHING = 70002,                    // NOT FOR OPEN SOURCE
    RX_SECONDARY_COMMAND = 70003,
    RX_PATHGUIDANCE_REQUEST = 70020,            // NOT FOR OPEN SOURCE
    RX_PERCMOD_REQUEST = 55030,                 // NOT FOR OPEN SOURCE
    RX_PERCMOD_APPROVAL = 55031,                // NOT FOR OPEN SOURCE
    RX_PERCMOD_VELOCITY_CHANGE = 55032,         // NOT FOR OPEN SOURCE
    RX_SAFETY_DRIVER_STATUS_AUTOBOX = 60000,
    RX_VEHICLEDATA_AUTOBOX = 60001,
    RX_VIDEO_RTSP = 8554,
    RX_VEHICLE_AUDIO = 62000                    // NOT FOR OPEN SOURCE
};

enum AutoboxPorts {
    RX_DIRECTCONTROL_AUTOBOX_COMMAND = 30000
};

enum OperatorPorts { // only what is sent via udp
    RX_LIDAR_OBJECTLIST = 50000,
    // 50001 occupied on CarPC4  - NOT FOR OPEN SOURCE
    RX_VEHICLESTATE_VEHICLEDATA = 50002,
    // 50003
    RX_VEHICLESTATE_ODOMETRY = 50005,
    RX_VEHICLESTATE_GPS = 50006,
    RX_SHAREDCONTROL_POLYGON = 50007,                   // NOT FOR OPEN SOURCE
    RX_SHAREDCONTROL_COMMAND = 50008,                   // NOT FOR OPEN SOURCE
    RX_SHAREDCONTROL_LOG = 50009,                       // NOT FOR OPEN SOURCE
    RX_SHAREDCONTROL_OBJECTS = 50010,                   // NOT FOR OPEN SOURCE
    RX_BITRATE_PREDICTIONS = 50011,                     // NOT FOR OPEN SOURCE
    RX_PATHGUIDANCE_RESPONSE = 50020,                   // NOT FOR OPEN SOURCE
    RX_PERCMOD_RESPONSE = 50030,                        // NOT FOR OPEN SOURCE
    RX_PERCMOD_GRIDMAP = 50031,                         // NOT FOR OPEN SOURCE
    RX_PERCMOD_OBJECTS = 50032,                         // NOT FOR OPEN SOURCE
    RX_LIDAR_DATA_RANGE_FROM = 50100,
    RX_LIDAR_DATA_RANGE_TO = 50199,
    RX_LIDAR_OBJECTS_RANGE_FROM = 50200,
    RX_LIDAR_OBJECTS_RANGE_TO = 50299,
    RX_LIDAR_OBJECT_MARKER_RANGE_FROM = 50300,
    RX_LIDAR_OBJECT_MARKER_RANGE_TO = 50399,
    RX_AUTOWARE_LANE = 51010,                           // NOT FOR OPEN SOURCE
    RX_OPERATOR_AUDIO = 52000,                          // NOT FOR OPEN SOURCE
    RX_ROUTE = 52100
};

namespace MqttTopics {
static const std::string DesiredVideoConfig{"/Operator/Video/DesiredVideoConfig"};
static const std::string ActualVideoConfig{"/Vehicle/Video/ActualVideoConfig"};
static const std::string DesiredBitrateConfig{"/Operator/Video/DesiredBitrateConfig"};
static const std::string ActualBitrateConfig{"/Vehicle/Video/ActualBitrateConfig"};
};

}; // namespace tod_network
