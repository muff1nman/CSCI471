set(SRCS
	ipv6.cpp
)

add_library(muncher_ipv6_parse ${SRCS})

set(LINK_LIBRARIES muncher_logging)

target_link_libraries(muncher_ipv6_parse ${LINK_LIBRARIES})

