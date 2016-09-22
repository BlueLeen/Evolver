cmake_minimum_required(VERSION 2.8.3)
project(sensor_srv)
include(${CMAKE_INSTALL_PREFIX}/../CMakeLists.txt)
find_package(catkin REQUIRED COMPONENTS message_generation std_msgs)
option(EVODEBUG "Use tutorial provided math implementation" OFF)

message(${EVODEBUG})
add_service_files(
  DIRECTORY srv
  FILES
)

generate_messages(DEPENDENCIES std_msgs) 
catkin_package(CATKIN_DEPENDS message_runtime std_msgs)

install(DIRECTORY include/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h")
