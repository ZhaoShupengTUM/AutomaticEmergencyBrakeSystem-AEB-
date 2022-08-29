catkin_add_gtest(testGeometryHelpers testGeometryHelpers.cpp)
add_dependencies(testGeometryHelpers ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(testGeometryHelpers ${catkin_LIBRARIES})
target_include_directories(testGeometryHelpers PRIVATE ${catkin_INCLUDE_DIRS} ../../include)