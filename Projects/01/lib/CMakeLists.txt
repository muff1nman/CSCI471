add_subdirectory(socket)
add_subdirectory(domain)

set(LINK_LIBRARIES httpmuncher_socket)
if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

add_executable(Main main.cpp)
target_link_libraries(Main ${LINK_LIBRARIES})
