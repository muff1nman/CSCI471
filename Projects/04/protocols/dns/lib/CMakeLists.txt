add_subdirectory(actors)
add_subdirectory(data)
add_subdirectory(parse)

set(SRCS
	dns.cpp
)

FILE(GLOB_RECURSE INC_ALL ${CMAKE_SOURCE_DIR}/include/*.h)

add_library(muncher_dns ${SRCS} ${INC_ALL})

set(LINK_LIBRARIES_DNS
	${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} muncher_socket muncher_dns_actors
	muncher_dns_data muncher_logging)

target_link_libraries(muncher_dns ${LINK_LIBRARIES_DNS})

set(LINK_LIBRARIES muncher_socket muncher_dns_actors muncher_dns_data
	muncher_dns muncher_logging)

add_executable(dug main.cpp)
target_link_libraries(dug ${LINK_LIBRARIES})

