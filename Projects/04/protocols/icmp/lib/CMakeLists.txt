set(SRCS
	icmp.cpp
)

FILE(GLOB_RECURSE INC_ALL ${CMAKE_SOURCE_DIR}/include/*.h)
set(LINK_LIBRARIES_ICMP muncher_logging muncher_icmp_parse)
add_library(muncher_icmp ${SRCS} ${INC_ALL})
target_link_libraries(muncher_icmp ${LINK_LIBRARIES_ICMP})

set(LINK_LIBRARIES muncher_logging muncher_dns muncher_icmp)
include_directories(${PROTOCOL_INCLUDE_DIR}/dns/include)
message( STATUS "including: " ${PROTOCOL_INCLUDE_DIR}/dns/include)

add_executable(pong main.cpp)
target_link_libraries(pong ${LINK_LIBRARIES})

add_subdirectory(parse)
