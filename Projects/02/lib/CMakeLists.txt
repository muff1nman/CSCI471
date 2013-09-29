add_subdirectory(socket)
add_subdirectory(actors)

set(LINK_LIBRARIES muncher_socket muncher_actors)
if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

add_executable(dnsmuncher main.cpp)
target_link_libraries(dnsmuncher ${LINK_LIBRARIES})
