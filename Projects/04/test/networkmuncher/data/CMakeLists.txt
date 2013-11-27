set( TESTNAME Data )
set( SRCS
	data_test.cpp
)

#set(LINK_LIBRARIES gtest gtest_main)
set(LINK_LIBRARIES gtest)
if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

add_executable( "Test${TESTNAME}" ${SRCS})
target_link_libraries( "Test${TESTNAME}" ${LINK_LIBRARIES})

add_test( ${TESTNAME} "Test${TESTNAME}" )

