cmake_minimum_required( VERSION 2.6 )
project( HttpMuncher )

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

set( HTTPM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

# for a vim plugin and not necessary for project
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Configuration Stuff
option(DEBUG "Turn debuggin on or off" ON)
option(LOGGING "Turn loggin on or off" ON)
option(BOOSTV "Change the boost version" 1.54)
if(${BOOSTV} STREQUAL "1.31")
       set( OLDBOOST 1 )
endif()
set( LOG_LEVEL 1 )
if(DEBUG)
	set( LOG_LEVEL 0 )
endif(DEBUG)

configure_file( 
	${HTTPM_INCLUDE_DIR}/httpmuncher/config.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/include/httpmuncher/config.h )

# for boost lexical cast 
find_package(Boost 1.54)
include_directories(${Boost_INCLUDE_DIR})

# Project includes 
include_directories( ${HTTPM_INCLUDE_DIR} 
	${CMAKE_CURRENT_BINARY_DIR}/include )

# Go do work CMake!
add_subdirectory( lib )
