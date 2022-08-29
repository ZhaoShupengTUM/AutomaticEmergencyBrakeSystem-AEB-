
set(TARGET_CHECKER testControlModeChecker)
set(CHECKER_SRC testControlModeChecker.cpp)
add_executable(${TARGET_CHECKER}
        ${CHECKER_SRC})
target_include_directories(${TARGET_CHECKER} PRIVATE
    ${catkin_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../include)
add_dependencies(${TARGET_CHECKER} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${TARGET_CHECKER}
    PRIVATE
    ${catkin_LIBRARIES}
    ${catkin_LIBRARIES}
    ${GTEST_LIBRARIES}
    )
set_property(TARGET ${TARGET_CHECKER} PROPERTY CXX_STANDARD 17)

set(TARGET_CHECKER testStatusChangeDetector)
set(CHECKER_SRC testStatusChangeDetector.cpp)
add_executable(${TARGET_CHECKER}
    ${CHECKER_SRC})
target_include_directories(${TARGET_CHECKER} PRIVATE
    ${catkin_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ../../include)
add_dependencies(${TARGET_CHECKER} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${TARGET_CHECKER}
    PRIVATE
    ${catkin_LIBRARIES}
    ${GTEST_LIBRARIES})
set_property(TARGET ${TARGET_CHECKER} PROPERTY CXX_STANDARD 17)
