add_subdirectory(socket)

set(LINK_LIBRARIES muncher_socket)

if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES_DNS ${LINK_LIBRARIES_DNS} glog)
endif()

add_executable(echo echo.cpp)

target_link_libraries(echo ${LINK_LIBRARIES})
