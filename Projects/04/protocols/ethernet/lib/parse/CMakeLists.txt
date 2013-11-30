set(SRCS
	ethernet.cpp
)

add_library(muncher_ethernet_parse ${SRCS})

set(LINK_LIBRARIES muncher_logging)

target_link_libraries(muncher_ethernet_parse ${LINK_LIBRARIES})

