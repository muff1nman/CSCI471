set( TESTNAME IPV4Parse )
set( SRCS
	parse_test.cpp
)

#set(LINK_LIBRARIES gtest gtest_main)
set(LINK_LIBRARIES gtest muncher_ipv4_parse)

add_executable( "Test${TESTNAME}" ${SRCS})
target_link_libraries( "Test${TESTNAME}" ${LINK_LIBRARIES})

add_test( ${TESTNAME} "Test${TESTNAME}" )

