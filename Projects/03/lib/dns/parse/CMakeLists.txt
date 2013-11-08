set(SRCS
	dns.cpp
	parse_context.h
)

add_library(muncher_dns_parse ${SRCS})

set(LINK_LIBRARIES "")

if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

target_link_libraries(muncher_dns_parse ${LINK_LIBRARIES})

