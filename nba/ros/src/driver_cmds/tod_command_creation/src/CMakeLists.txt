set(TARGETS ${TARGETS} OperatorCommandCreator)
add_executable(OperatorCommandCreator CommandCreatorNode.cpp CommandCreator.cpp)
add_dependencies(OperatorCommandCreator ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(OperatorCommandCreator ${catkin_LIBRARIES})
target_include_directories(OperatorCommandCreator PRIVATE ${catkin_INCLUDE_DIRS})

install(TARGETS ${TARGETS}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
