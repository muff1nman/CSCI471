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

#include "parse_hint.h"
#include "networkmuncher/util/byte/operations.h"
#include <boost/optional.hpp>
#include <set>

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

		std::set<MacAddr> mac_addresses;
		std::set<Ipv4::Addr, bool(*)(const Ipv4::Addr&, const Ipv4::Addr&)> ipv4_addresses;
		std::set<Ipv6::Addr, bool(*)(const Ipv6::Addr&, const Ipv6::Addr&)> ipv6_addresses;
		std::set<Udp::Port, bool(*)(const Udp::Port&, const Udp::Port&)> udp_ports;
		std::set<Tcp::Port, bool(*)(const Tcp::Port&, const Tcp::Port&)> tcp_ports;

		size_t number_of_syns;
		size_t number_of_acks;

		size_t number_of_fragmented;

		size_t number_of_authoritative;
		size_t number_of_questions;
		size_t number_of_queries;
		size_t number_of_responses;
		size_t number_of_recursive_queries;
		size_t number_of_resource_records;
		std::set<std::string> labels;

		ParseHint process_protocol(const Ethernetv2& ether,size_t size);
		ParseHint process_protocol(const Ethernet8023& ether,size_t size);
		ParseHint process_protocol(const Ipv4& ip,size_t size);
		ParseHint process_protocol(const Ipv6& ip,size_t size);
		ParseHint process_protocol(const Echo& echo,size_t size);
		ParseHint process_protocol(const Udp& echo,size_t size);
		ParseHint process_protocol(const DNS& echo,size_t size);
		ParseHint process_protocol(const Arp& arp,size_t size);
		ParseHint process_protocol(const Tcp& tcp,size_t size);

		//bool ipv4_less_than(const Ipv4::Addr& f, const Ipv4::Addr& s) {
			//return less_than<Ipv4::ADDR_LENGTH>(f,s);
		//}

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
			other_application_count(0),
			ipv4_addresses(less_than),
			ipv6_addresses(less_than),
			udp_ports(less_than),
			tcp_ports(less_than),
			number_of_syns(0),
			number_of_acks(0),
			number_of_fragmented(0),
			number_of_authoritative(0),
			number_of_questions(0),
			number_of_queries(0),
			number_of_responses(0),
			number_of_recursive_queries(0),
			number_of_resource_records(0)
 	{}

   void incrementPacketCount() { totalPacketCount++; };
   void displayResults();
	 // returns true if we should continue parsing
	 ParseHint process(const ProtocolPtr proto,size_t size);
};

#endif
