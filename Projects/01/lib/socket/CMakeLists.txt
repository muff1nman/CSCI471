set(SRCS
	socket.cpp
	header_consumer.cpp
)

add_library(httpmuncher_socket ${SRCS})

set(Boost_USE_MULTITHREADED ON)
include_directories(${Boost_INCLUDE_DIR})
set(BOOSTV "1.31" CACHE STRING "Boost version")
find_package(Boost ${BOOSTV} EXACT COMPONENTS regex thread date_time program_options filesystem system REQUIRED)

find_package(Threads REQUIRED)

set(LINK_LIBRARIES 
	${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES}
	httpmuncher_domain)

if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

target_link_libraries(httpmuncher_socket ${LINK_LIBRARIES})

