cmake_minimum_required(VERSION 2.8.3)
project (config)
include(${CMAKE_INSTALL_PREFIX}/../CMakeLists.txt)

#find_package(catkin REQUIRED COMPONENTS roscpp common_msgs platform)
find_package(catkin)

# Specify locations of header files .
#include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(include)
#link_directories(${PROJECT_SOURCE_DIR}/lib ${catkin_LIBRARIES} ${CMAKE_INSTALL_PREFIX}/lib/)
link_directories(${PROJECT_SOURCE_DIR}/lib ${CMAKE_INSTALL_PREFIX}/lib/)

# Declare our catkin package .
catkin_package()

add_library(tiny_xml_proc  
   src/Configer.cpp
   src/tinystr.cpp
   src/tinyxml.cpp
   src/tinyxmlerror.cpp 
   src/tinyxmlparser.cpp
)

install(TARGETS tiny_xml_proc
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_SHARE_DESTINATION})

#install(TARGETS tiny_xml_proc
#  ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
#  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
#  RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

