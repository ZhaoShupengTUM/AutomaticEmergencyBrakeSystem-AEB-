set(THREADS_PREFER_PTHREAD_FLAG ON) # required?
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})

find_package(PCAN REQUIRED)
find_package(Threads REQUIRED)

set(SENSO_SOURCES
    src/SensoInputDevice.cpp
    src/SensoController.cpp
    src/CanInterface.cpp
    src/AudiSteeringWheelController.cpp
)

add_library(SensoInputDevice
    ${SENSO_SOURCES}
)  

target_include_directories(SensoInputDevice 
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../General
        ${CMAKE_CURRENT_SOURCE_DIR}/src

    PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR} # why PUBLIC required for this and next
        ${CMAKE_CURRENT_SOURCE_DIR}/src # only include and put SensowheelInputDevice.h there
)

target_link_libraries(SensoInputDevice 
    PRIVATE
        PCAN::PCAN
        Threads::Threads
)

set(DEVICE_TARGETS ${DEVICE_TARGETS} SensoInputDevice PARENT_SCOPE)
