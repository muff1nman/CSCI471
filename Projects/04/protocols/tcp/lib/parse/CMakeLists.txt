set(SRCS
	tcp.cpp
)

add_library(muncher_tcp_parse ${SRCS})

set(LINK_LIBRARIES muncher_logging)

target_link_libraries(muncher_tcp_parse ${LINK_LIBRARIES})

