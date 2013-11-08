cmake_minimum_required( VERSION 2.6 )
project( NetworkMuncher_DNS )

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

set( PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

# for a vim plugin and not necessary for project
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Configuration Stuff
# TODO
option(CACHING "Enable DNS caching" ON)
option(DEBUG "Turn debuggin on or off" ON)
option(LOGGING "Turn loggin on or off" OFF)
option(TEST "Turn testing on or off" OFF)
option(DAEMON_DEBUG "Turn debug on while in daemon mode" OFF)

if(DEBUG)
	set( CMAKE_BUILD_TYPE debug)
else()
	set( CMAKE_BUILD_TYPE release)
endif(DEBUG)

# for boost lexical cast 
find_package(Boost 1.33.1)
if( NOT(Boost_MAJOR_VERSION EQUAL "1") )
	message(FATAL_ERROR "Boost major version not supported")
endif()
if( Boost_MINOR_VERSION LESS "54" )
	message(STATUS "Setting to old boost")
	set( OLDBOOST 1 )
endif()

# profiling stuff
if(CMAKE_COMPILER_IS_GNUCXX)
	#message(STATUS "enabling c++ 11")
	#add_definitions(-std=gnu++0x)
	if(DEBUG)
		message(STATUS "warnings on")
		add_definitions(-Wall -Wextra -pedantic -ansi -Wno-unused-variable
			-Wno-unused-parameter)
		message(STATUS "enabling gprof")
		add_definitions(-pg)
		set( CMAKE_EXE_LINKER_FLAGS -pg )
	endif(DEBUG)
endif()

#ensure this is after we find the boost version
configure_file( 
	${PROJECT_INCLUDE_DIR}/dns/config.h.cmake
	${CMAKE_CURRENT_BINARY_DIR}/include/dns/config.h )

# Project includes 
include_directories( ${PROJECT_INCLUDE_DIR} 
	${CMAKE_CURRENT_BINARY_DIR}/include )

# for qt creator
FILE(GLOB_RECURSE INC_ALL ${CMAKE_SOURCE_DIR}/include/*.h)

# Go do work CMake!
add_subdirectory( lib )

# if testing do some tests!
if( ${TEST} STREQUAL "ON" )
	enable_testing()
	add_subdirectory( test )
endif()
