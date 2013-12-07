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

		boost::optional<size_t> ipv4_max_size;
		boost::optional<size_t> ipv4_min_size;

		ParseHint process_protocol(const Ethernetv2& ether);
		ParseHint process_protocol(const Ethernet8023& ether);
		ParseHint process_protocol(const Ipv4& ip);
		ParseHint process_protocol(const Ipv6& ip);
		ParseHint process_protocol(const Echo& echo);
		ParseHint process_protocol(const Udp& echo);
		ParseHint process_protocol(const DNS& echo);
		ParseHint process_protocol(const Arp& arp);
		ParseHint process_protocol(const Tcp& tcp);

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
	 ParseHint process(const ProtocolPtr proto);
};

#endif
