set(SRCS
	arp.cpp
)

add_library(muncher_arp_parse ${SRCS})

set(LINK_LIBRARIES muncher_logging)

target_link_libraries(muncher_arp_parse ${LINK_LIBRARIES})

