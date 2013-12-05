set(SRCS
	ipv4.cpp
)

add_library(muncher_ipv4_parse ${SRCS})

set(LINK_LIBRARIES muncher_logging)

target_link_libraries(muncher_ipv4_parse ${LINK_LIBRARIES})

