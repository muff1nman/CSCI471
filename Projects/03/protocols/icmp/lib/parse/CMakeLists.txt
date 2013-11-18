set(SRCS
	echo.cpp
	ip.cpp
)

add_library(muncher_icmp_parse ${SRCS})

set(LINK_LIBRARIES muncher_logging)

target_link_libraries(muncher_icmp_parse ${LINK_LIBRARIES})

