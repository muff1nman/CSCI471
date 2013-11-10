set(LINK_LIBRARIES muncher_socket muncher_logging muncher_dns)
include_directories(${PROTOCOL_INCLUDE_DIR}/dns/include)
message( STATUS "including: " ${PROTOCOL_INCLUDE_DIR}/dns/include)

add_executable(pong main.cpp)
target_link_libraries(pong ${LINK_LIBRARIES})

