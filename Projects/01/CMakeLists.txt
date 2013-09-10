cmake_minimum_required( VERSION 2.6 )
project( HttpMuncher )

set( HTTPM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )

# for a vim plugin and not necessary for project
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

# Project includes 
include_directories( ${HTTPM_INCLUDE_DIR} 
	${CMAKE_CURRENT_BINARY_DIR}/include )

# Go do work CMake!
add_subdirectory( lib )
