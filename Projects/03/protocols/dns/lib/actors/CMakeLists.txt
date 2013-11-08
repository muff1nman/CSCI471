set(SRCS
	dns_consumer.cpp
	dns_response_consumer.cpp
	dns_producer.cpp
)

add_library(muncher_dns_actors ${SRCS})

set(LINK_LIBRARIES muncher_dns_parse muncher_dns_data)

if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

target_link_libraries(muncher_dns_actors ${LINK_LIBRARIES})

