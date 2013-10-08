set( GTEST_DIR util/gtest-1.7.0 )

add_subdirectory( ${GTEST_DIR} )

include_directories( ${GTEST_DIR}/include )

add_subdirectory( random )

