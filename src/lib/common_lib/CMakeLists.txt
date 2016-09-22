cmake_minimum_required(VERSION 2.8.3)
project (common_lib)

SET(SRC_FILES
	src/UEventsManager.cpp
    src/UEventsHandler.cpp
    src/UEventsSender.cpp
    src/UFile.cpp
    src/UDirectory.cpp
    src/UConversion.cpp
    src/ULogger.cpp
    src/UThread.cpp
    src/UTimer.cpp
    src/UProcessInfo.cpp
    src/UVariant.cpp
	src/Parameters.cpp
	src/ConvertUTF.c
)
IF(DEFINED ANDROID)
    ADD_DEFINITIONS(-DANDROID)
ELSE()
    MESSAGE("NOT DEFINED ANDROID")
ENDIF()

if(UNIX AND NOT ANDROID)
    FIND_PACKAGE(Pthreads REQUIRED)
ENDIF(UNIX AND NOT ANDROID)
#SET(INCLUDE_DIRS
#	${CMAKE_CURRENT_SOURCE_DIR}/../include
#	${PTHREADS_INCLUDE_DIR}
#)

SET(INCLUDE_DIRS
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${PTHREADS_INCLUDE_DIR}
)
find_package(catkin REQUIRED)

# Specify locations of header files .
include_directories(include ${catkin_INCLUDE_DIRS})
catkin_package()
# Make sure the compiler can find include files from our library.
INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

add_library(intelligence_comm SHARED ${SRC_FILES})
add_library(intelligence_comm_static  
   STATIC  ${SRC_FILES})

set_target_properties(intelligence_comm_static  PROPERTIES OUTPUT_NAME "intelligence_comm")

IF(MINGW)
    TARGET_LINK_LIBRARIES(intelligence_comm ${PTHREADS_LIBRARY} "-lpsapi")
ELSEIF(WIN32 OR MSVC)
	FIND_LIBRARY(PSAPI_LIBRARIES NAMES psapi libpsapi.dll.a libpsapi.a libpsapi.lib )
	TARGET_LINK_LIBRARIES(intelligence_comm ${PSAPI_LIBRARIES})
ELSE()
    TARGET_LINK_LIBRARIES(intelligence_comm ${PTHREADS_LIBRARY} )
ENDIF()

SET_TARGET_PROPERTIES( intelligence_comm PROPERTIES VERSION  "1" SOVERSION "1.1" )

INSTALL(TARGETS  intelligence_comm
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})

		
INSTALL(DIRECTORY include/
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h")

#install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../include/ DESTINATION "${INSTALL_INCLUDE_DIR}" COMPONENT devel FILES_MATCHING PATTERN "*.h" PATTERN ".svn" EXCLUDE)

