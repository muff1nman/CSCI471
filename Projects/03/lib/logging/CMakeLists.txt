set(SRCS
	logging.cpp
)

add_library(muncher_logging ${SRCS})

if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

target_link_libraries(muncher_logging ${LINK_LIBRARIES})

