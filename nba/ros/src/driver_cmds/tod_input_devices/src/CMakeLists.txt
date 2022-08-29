set(QT_MINIMUM_VERSION 5.9)
find_package(Qt5 REQUIRED COMPONENTS Widgets)
if(Qt5_VERSION VERSION_LESS QT_MINIMUM_VERSION)
    MESSAGE(FATAL_ERROR "Minimum supported Qt version: ${QT_MINIMUM_VERSION}.
        Installed version: ${Qt5_VERSION}.")
endif()

# ------------------------- Add Specific Input Devices -----------------
# adds target to variable DEVICE_TARGETS
add_subdirectory(VirtualDevice)
add_subdirectory(UsbInputDevice)

# not for open source
option(SENSO "Build Senso target" OFF)
if (${SENSO})
    message("building ${PROJECT_NAME} with SENSO")
    add_definitions(-DSENSO_MACRO=1)
    add_subdirectory(SensoWheel)
else()
    add_definitions(-DSENSO_MACRO=0)
    message("skipping SENSO build in ${PROJECT_NAME}")
endif()

# ------------------ Specify Files for InputDeviceController -----------
set(GENERAL_CPP
        InputDeviceController.cpp
        RosInterface.cpp
        InputDeviceNode.cpp  
        General/InputDevice.cpp
)

# --------------------------- Build Executables ------------------------
add_executable(InputDevice ${GENERAL_CPP})
target_compile_features(InputDevice PRIVATE cxx_std_17)
add_dependencies(InputDevice ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_include_directories(InputDevice PRIVATE ${catkin_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} General )
target_link_libraries(InputDevice
    PRIVATE
    Qt5::Widgets
    ${DEVICE_TARGETS}
    ${catkin_LIBRARIES}
    stdc++fs
)


install(TARGETS
    InputDevice
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)


