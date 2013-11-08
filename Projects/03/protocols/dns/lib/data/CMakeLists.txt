set(SRCS
	dns_convert.cpp
)

add_library(muncher_dns_data ${SRCS})

set(LINK_LIBRARIES "")

if(${LOGGING} STREQUAL "ON")
	set(LINK_LIBRARIES ${LINK_LIBRARIES} glog)
endif()

target_link_libraries(muncher_dns_data ${LINK_LIBRARIES})

