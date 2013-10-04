add_subdirectory(socket)
add_subdirectory(actors)
add_subdirectory(data)

set(LINK_LIBRARIES muncher_socket muncher_actors muncher_data)
if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

add_executable(dnsmuncher main.cpp)
target_link_libraries(dnsmuncher ${LINK_LIBRARIES})

add_executable(udplisten listen.cpp)
target_link_libraries(udplisten ${LINK_LIBRARIES})
