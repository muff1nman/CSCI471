set(SRCS
	analyzer.cpp
	analyzer.h
	resultsC.cpp
	resultsC.h
)

set(LINK_LIBRARIES muncher_logging pcap)

add_executable(analyzer ${SRCS})
target_link_libraries(analyzer ${LINK_LIBRARIES})
