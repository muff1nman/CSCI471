set(SRCS
	socket.cpp
	consumer.cpp
)

add_library(dnsmuncher_socket ${SRCS})

set(Boost_USE_MULTITHREADED ON)
include_directories(${Boost_INCLUDE_DIR})
find_package(Boost 1.33.1 COMPONENTS regex thread date_time program_options filesystem system REQUIRED)

find_package(Threads REQUIRED)

set(LINK_LIBRARIES 
	${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES}
	dnsmuncher_domain)

if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

target_link_libraries(dnsmuncher_socket ${LINK_LIBRARIES})

