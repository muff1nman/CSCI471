set(SRCS
	consumer.cpp
	dns_consumer.cpp
)

add_library(muncher_actors ${SRCS})

set(LINK_LIBRARIES muncher_parse)

if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

target_link_libraries(muncher_actors ${LINK_LIBRARIES})

