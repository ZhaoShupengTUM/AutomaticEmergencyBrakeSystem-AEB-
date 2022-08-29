cmake_minimum_required(VERSION 3.10)
find_package(PahoMqttCpp REQUIRED)

add_executable(Gtester Gtester.cpp)
target_include_directories(Gtester PRIVATE ${catkin_INCLUDE_DIRS})
add_dependencies(Gtester ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(Gtester PRIVATE ${catkin_LIBRARIES} tod_network ${GTEST_LIBRARIES})
set_property(TARGET Gtester PROPERTY CXX_STANDARD 17)
