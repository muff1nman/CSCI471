set( SRCS
	random_test.cpp
)

set(LINK_LIBRARIES gtest gtest_main)

add_executable(TestRandom ${SRCS})
target_link_libraries(TestRandom ${LINK_LIBRARIES})

add_test( random TestRandom )

