configure_file( file_names.h.cmake 	${CMAKE_CURRENT_BINARY_DIR}/file_names.h )

file(COPY query_a_google DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
