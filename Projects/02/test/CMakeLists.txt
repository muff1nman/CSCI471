set( GTEST_DIR test-lib/gtest-1.7.0 )
set( TEST_INCLUDE "include" )
set( RESOURCES_DIR "resources" )
set( RESOURCES_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/${RESOURCES_DIR}" )
set( TEST_INCLUDE_CONFIGURED "${CMAKE_CURRENT_BINARY_DIR}/include" )

add_subdirectory( ${GTEST_DIR} )

configure_file( ${TEST_INCLUDE}/file_names.h.cmake ${TEST_INCLUDE_CONFIGURED}/file_names.h )

include_directories( 
	${GTEST_DIR}/include 
	${TEST_INCLUDE}
	${TEST_INCLUDE_CONFIGURED})

add_subdirectory( dnsmuncher )

file(COPY ${RESOURCES_DIR}/query_a_google DESTINATION ${RESOURCES_OUTPUT_DIR})
