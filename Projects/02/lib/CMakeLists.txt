add_subdirectory(socket)

set(LINK_LIBRARIES muncher_socket)
if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

add_executable(dnsmuncher main.cpp)
target_link_libraries(dnsmuncher ${LINK_LIBRARIES})
