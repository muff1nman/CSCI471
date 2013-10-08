set( GTEST_DIR test-lib/gtest-1.7.0 )

add_subdirectory( ${GTEST_DIR} )

include_directories( ${GTEST_DIR}/include )

add_subdirectory( random )

