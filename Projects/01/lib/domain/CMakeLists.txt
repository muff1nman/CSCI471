set( SRCS 
	http_header.cpp
	http_request_header.cpp
	http_response_header.cpp
)

add_library(httpmuncher_domain ${SRCS})
