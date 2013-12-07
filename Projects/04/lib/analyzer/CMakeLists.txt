set(SRCS
	analyzer.cpp
	analyzer.h
	resultsC.cpp
	resultsC.h
)

set(LINK_LIBRARIES 
	muncher_logging
	pcap
	muncher_icmp_parse
	muncher_ethernet_parse
	muncher_udp_parse
	muncher_dns_parse
	muncher_arp_parse
	muncher_tcp_parse
	muncher_ipv4_parse
	muncher_ipv6_parse
	)

add_executable(analyzer ${SRCS})
target_link_libraries(analyzer ${LINK_LIBRARIES})
