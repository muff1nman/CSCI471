add_subdirectory(socket)
add_subdirectory(logging)
add_subdirectory(analyzer)

set(LINK_LIBRARIES muncher_socket muncher_logging)

add_executable(echo echo.cpp)

target_link_libraries(echo ${LINK_LIBRARIES})
