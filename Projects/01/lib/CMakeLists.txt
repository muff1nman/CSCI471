set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.54 COMPONENTS thread date_time program_options filesystem system REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(Threads REQUIRED)

set(LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

add_executable(Main main.cpp)
target_link_libraries(Main ${LINK_LIBRARIES})
