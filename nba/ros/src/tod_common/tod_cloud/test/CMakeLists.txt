# ------------------------------------------------------------------------
# --------------------------- Testing ------------------------
# ------------------------------------------------------------------------

set(EXECUTABLE testHttpHandler)

catkin_add_gtest(${EXECUTABLE} testTodHttpMsgs.cpp)
add_dependencies(${EXECUTABLE} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_include_directories(${EXECUTABLE} PRIVATE
    ${catkin_INCLUDE_DIRS}
    ../include/)
target_link_libraries(${EXECUTABLE} ${catkin_LIBRARIES} ${PROJECT_NAME})

