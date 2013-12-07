set(SRCS
	echo.cpp
)

add_library(muncher_icmp_parse ${SRCS})

set(LINK_LIBRARIES muncher_logging muncher_ipv4_parse)

target_link_libraries(muncher_icmp_parse ${LINK_LIBRARIES})

