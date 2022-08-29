###### ADD TESTS ########
catkin_add_gtest(${PROJECT_NAME}_test UnitTests.cpp)
add_dependencies(${PROJECT_NAME}_test ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_include_directories(${PROJECT_NAME}_test PRIVATE
    ${catkin_INCLUDE_DIRS}
    PUBLIC ../include)
target_link_libraries(${PROJECT_NAME}_test ${catkin_LIBRARIES} ${PROJECT_NAME})

catkin_add_gtest(${PROJECT_NAME}_node TestNode.cpp)
add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_include_directories(${PROJECT_NAME}_node PRIVATE
    ${catkin_INCLUDE_DIRS}
    PUBLIC ../include)
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES} ${PROJECT_NAME})