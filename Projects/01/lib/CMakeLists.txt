set(LINK_LIBRARIES )
if(${LOGGING})
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif(${LOGGING})

add_executable(Main main.cpp)
target_link_libraries(Main ${LINK_LIBRARIES})
