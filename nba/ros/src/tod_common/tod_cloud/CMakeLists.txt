cmake_minimum_required(VERSION 2.8.3)
set(PROJECT_NAME tod_cloud)
project(${PROJECT_NAME})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(catkin REQUIRED COMPONENTS
    roscpp
    tod_msgs
    )
find_package(CURLPP REQUIRED)
find_package(CURL REQUIRED)
find_package(JsonCpp REQUIRED)

catkin_package(
    INCLUDE_DIRS include # The exported include paths (i.e. cflags) for the package
    LIBRARIES ${PROJECT_NAME} # The exported libraries from the project
    CATKIN_DEPENDS roscpp
    DEPENDS JSONCPP
    )
###### BUILD LIBRARY #######
add_library(${PROJECT_NAME}
    src/HttpHandler.cpp
    src/todHttpMsgs.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${catkin_INCLUDE_DIRS}
    src
    PUBLIC include)

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${catkin_LIBRARIES}
    curlpp::curlpp
    # CURL::libcurl
    PUBLIC
    jsoncpp::jsoncpp
    )
install(DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
)

###### ADD TESTS ########
add_subdirectory(test)