set(LINK_LIBRARIES muncher_socket muncher_logging)

add_executable(pong main.cpp)
target_link_libraries(pong ${LINK_LIBRARIES})

