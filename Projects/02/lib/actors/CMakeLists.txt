set(SRCS
	consumer.cpp
)

add_library(muncher_actors ${SRCS})

set(LINK_LIBRARIES "")

if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

target_link_libraries(muncher_actors ${LINK_LIBRARIES})

