set(SRCS
	udp.cpp
)

add_library(muncher_udp_parse ${SRCS})

set(LINK_LIBRARIES muncher_logging)

target_link_libraries(muncher_udp_parse ${LINK_LIBRARIES})

