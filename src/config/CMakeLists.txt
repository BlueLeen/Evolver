cmake_minimum_required(VERSION 2.8.3)
project (config)
ADD_DEFINITIONS(-DANDROID)
include(${CMAKE_INSTALL_PREFIX}/../CMakeLists.txt)
find_package(catkin REQUIRED COMPONENTS message_generation std_msgs roscpp common_lib)
option(EVODEBUG "Use tutorial provided math implementation" OFF)

add_subdirectory(xml)

message(${EVODEBUG})
# Generate messages in the 'msg' folder
 add_message_files(
   DIRECTORY cfms/msg
   FILES
   node_info.msg
   charge_info.msg
 )

# Generate services in the 'srv' folder
 add_service_files(
   DIRECTORY cfms/srv
   FILES
   node_req.srv
   charge_info_req.srv
 )
 
# Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
 ) 
# Declare our catkin package .
catkin_package(CATKIN_DEPENDS message_runtime std_msgs)

# Specify locations of header files .
include_directories(include ${catkin_INCLUDE_DIRS})
link_directories(${PROJECT_SOURCE_DIR}/lib ${catkin_LIBRARIES} ${CMAKE_INSTALL_PREFIX}/lib/)

# Declare the executable , along with its sourcefiles . If
# there are multiple executables ,use multiple copies of
# this line .
add_executable (
	config
	src/chargefile.cpp  
	src/driboardfile.cpp
	src/config.cpp 
	src/actcfg.cpp
	src/commucfg.cpp 
	src/concfg.cpp
	src/devcfg.cpp
	src/sencfg.cpp
	src/upgcfg.cpp
	src/updatemanager.cpp
)
add_dependencies(config config_generate_messages_cpp)
# Specify libraries against which to link. Again , this
# line should be copied for each distinct executable in
# the package .
target_link_libraries(config ${catkin_LIBRARIES} intelligence_comm tiny_xml_proc)
install(TARGETS config
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

install(DIRECTORY include/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h")
