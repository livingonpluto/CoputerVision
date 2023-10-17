cmake_minimum_required(VERSION 3.0.0)
project(CV_Ex VERSION 0.1.0)

#

if(CXX)
  enable_language(CXX)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CXX_FLAGS_RELEASE_TMP  ${CMAKE_CXX_FLAGS_RELEASE})

string(APPEND CXX_FLAGS_RELEASE_TMP " ")
string(APPEND CXX_FLAGS_RELEASE_TMP ${CMAKE_MARCH_FLAG})

set(CMAKE_CXX_FLAGS_RELEASE ${CXX_FLAGS_RELEASE_TMP})

#message(STATUS "CXX_RELEASE_FLAGS: ${CXX_FLAGS_RELEASE_TMP}")

# I put the if(NOT UNIX) here for simplicity but of course if another FindXX.cmake is needed then probably two seperate folders in /CMakeModules are necessary one for Windows and one for Linux
# and then depending on whether we are on Windows or Unix we set CMAKE_MODULE_PATH to either /CMakeModules/Win or /CMakeModules/Unix
#find_package(Qt5 COMPONENTS Core REQUIRED)
#find_package(Qt5 COMPONENTS Gui REQUIRED)
#find_package(Qt5 COMPONENTS Widgets REQUIRED)
#find_package(Qt5 COMPONENTS Test REQUIRED)
#find_package(Qt5 COMPONENTS Concurrent REQUIRED)


find_package( OpenCV REQUIRED )
include_directories("${PROJECT_SOURCE_DIR}/include" ${OpenCV_INCLUDE_DIRS})

#set(CMAKE_CXX_COMPILER mpicxx)
#include_directories(SYSTEM ${MPI_INCLUDE_PATH})

message(STATUS "${OpenCV_INCLUDE_DIRS}")

set(SOURCE_FILES
	Ex1_start.cpp
)

set(HEADER_FILES

)

add_executable(CV_Ex ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE  ${OpenCV_LIBS} )
#target_link_libraries(${PROJECT_NAME} PRIVATE  Qt5::Core)
#target_link_libraries(${PROJECT_NAME} PRIVATE  Qt5::Gui)
#target_link_libraries(${PROJECT_NAME} PRIVATE  Qt5::Widgets)
#target_link_libraries(${PROJECT_NAME} PRIVATE  Qt5::Test)
#target_link_libraries(${PROJECT_NAME} PRIVATE  Qt5::Concurrent)

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
