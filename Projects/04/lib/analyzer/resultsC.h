//
//  resultsC.h
//  Project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#ifndef analyzer_resultsC_h
#define analyzer_resultsC_h

#include "networkmuncher/domain/all.h"
#include "ethernet/domain/domain.h"
#include "icmp/domain/domain.h"
#include "udp/domain/domain.h"
#include "dns/domain/domain.h"
#include "arp/domain/domain.h"
#include "tcp/domain/domain.h"
#include "ipv4/domain/domain.h"
#include "ipv6/domain/domain.h"
#include <boost/optional.hpp>
#include "parse_hint.h"

class resultsC {
  protected:
		size_t totalPacketCount;
		size_t ethernet_v2_count;
		size_t ethernet_8023;
		size_t other_link_count;

		size_t ipv4_count;
		size_t ipv6_count;
		size_t arp_count;
		size_t other_network_count;

		size_t udp_count;
		size_t tcp_count;
		size_t icmp_echo_count;
		size_t other_transport_count;

		size_t dns_count;
		size_t other_application_count;

		std::vector<size_t> ipv4_sizes;
		std::vector<size_t> ipv6_sizes;
		std::vector<size_t> arp_sizes;

		std::vector<size_t> udp_sizes;
		std::vector<size_t> tcp_sizes;
		std::vector<size_t> icmp_sizes;

		ParseHint process_protocol(const Ethernetv2& ether,size_t size);
		ParseHint process_protocol(const Ethernet8023& ether,size_t size);
		ParseHint process_protocol(const Ipv4& ip,size_t size);
		ParseHint process_protocol(const Ipv6& ip,size_t size);
		ParseHint process_protocol(const Echo& echo,size_t size);
		ParseHint process_protocol(const Udp& echo,size_t size);
		ParseHint process_protocol(const DNS& echo,size_t size);
		ParseHint process_protocol(const Arp& arp,size_t size);
		ParseHint process_protocol(const Tcp& tcp,size_t size);

  public:
		resultsC() : 
			totalPacketCount(0),
			ethernet_v2_count(0),
			ethernet_8023(0),
			other_link_count(0),
			ipv4_count(0),
			ipv6_count(0),
			arp_count(0),
			other_network_count(0),
			udp_count(0),
			tcp_count(0),
			icmp_echo_count(0),
			other_transport_count(0),
			dns_count(0),
			other_application_count(0) {}

   void incrementPacketCount() { totalPacketCount++; };
   void displayResults();
	 // returns true if we should continue parsing
	 ParseHint process(const ProtocolPtr proto,size_t size);
};

#endif
