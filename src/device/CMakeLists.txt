cmake_minimum_required(VERSION 2.8.3)
project (device)
include(${CMAKE_INSTALL_PREFIX}/../CMakeLists.txt)
find_package(catkin REQUIRED COMPONENTS roscpp actionlib_msg actionlib_srv )

# Specify locations of header files .
include_directories(include ${catkin_INCLUDE_DIRS})
link_directories(${PROJECT_SOURCE_DIR}/lib ${catkin_LIBRARIES} ${CMAKE_INSTALL_PREFIX}/lib/)

# Declare our catkin package .
catkin_package()
# Declare the executable , along with its sourcefiles . If
# there are multiple executables ,use multiple copies of
# this line .
add_executable (device  src/device.cpp)
# Specify libraries against which to link. Again , this
# line should be copied for each distinct executable in
# the package .
target_link_libraries(device ${catkin_LIBRARIES})
install(TARGETS device
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})
