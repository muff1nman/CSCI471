
set( SRCS
	util_test.cpp
)

#set(LINK_LIBRARIES gtest gtest_main)
set(LINK_LIBRARIES gtest)
if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

add_executable(TestUtil ${SRCS})
target_link_libraries(TestUtil ${LINK_LIBRARIES})

add_test( util TestUtil )

