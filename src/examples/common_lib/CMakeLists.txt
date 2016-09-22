cmake_minimum_required(VERSION 2.8.3)
project (common_lib_demo)

ADD_DEFINITIONS(-DANDROID)
SET(SRC_FILES
	src/common_lib_demo.cpp
)

#SET(INCLUDE_DIRS
#	${CMAKE_CURRENT_SOURCE_DIR}/../include
#	${PTHREADS_INCLUDE_DIR}
#)

find_package(catkin REQUIRED COMPONENTS common_lib)

# Specify locations of header files .
include_directories(include ${catkin_INCLUDE_DIRS})
link_directories(${catkin_LIBRARIES}  ${CMAKE_INSTALL_PREFIX}/lib/)
catkin_package()
# Make sure the compiler can find include files from our library.
INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

ADD_EXECUTABLE(demo_common_lib src/demo_common_lib.cpp)

IF(ANDROID)
    target_link_libraries(demo_common_lib  ${catkin_LIBRARIES} intelligence_comm )
ELSE()
    target_link_libraries(demo_common_lib  ${catkin_LIBRARIES} pthread intelligence_comm )
ENDIF()

INSTALL(TARGETS demo_common_lib 
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

		
#INSTALL(DIRECTORY include/
#  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#  FILES_MATCHING PATTERN "*.h")

#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/ DESTINATION "${INSTALL_INCLUDE_DIR}" COMPONENT devel FILES_MATCHING PATTERN "*.h" PATTERN ".svn" EXCLUDE)

