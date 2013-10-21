set(SRCS
	consumer.cpp
	dns_consumer.cpp
	dns_response_consumer.cpp
	dns_producer.cpp
)

add_library(muncher_actors ${SRCS})

set(LINK_LIBRARIES muncher_parse muncher_data)

if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

target_link_libraries(muncher_actors ${LINK_LIBRARIES})

