//
//  resultsC.cc
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "analyzer.h"
#include "networkmuncher/domain/protocol_types.h"
#include <string>


// ***************************************************************************
// * displayResults:
// *  This method will be called once, after all the packets have been
// *  processed.  You should use this to print all the statistics you
// *  collected to stdout.
// ***************************************************************************
void resultsC::displayResults() {
	std::string separator = 
		"================================";
  std::cout << "A total of " << totalPacketCount << " packets processed." << std::endl;

	std::cout << std::endl << "Link Layer Statistics" << std::endl << separator << std::endl;
	std::cout << "Ethernet II packets: " << ethernet_v2_count << std::endl;
	std::cout << "Ethernet 802.3 packets: " << ethernet_8023 << std::endl;

	std::cout << std::endl << "Network Layer Statistics" << std::endl << separator << std::endl;
	std::cout << "Ipv4 packets: " << ipv4_count << std::endl;
	if(ipv4_max_size) {
		std::cout << "Max Ipv4 size: " << *ipv4_max_size << std::endl;
	}
	if(ipv4_min_size) {
		std::cout << "Min Ipv4 size: " << *ipv4_min_size << std::endl;
	}
	std::cout << "Arp packets: " << arp_count << std::endl;

	std::cout << std::endl << "Transport Layer Statistics" << std::endl << separator << std::endl;
	std::cout << "Icmp echo packets: " << icmp_echo_count << std::endl;
	std::cout << "Upd packets: " << udp_count << std::endl;
	std::cout << "Tcp packets: " << tcp_count << std::endl;

	std::cout << std::endl << "Application Layer Statistics" << std::endl << separator << std::endl;
	std::cout << "Dns packets: " << dns_count << std::endl;

	std::cout << "Misc" << std::endl << separator << std::endl;
	std::cout << "Unrecognized link layer packets: " << other_link_count << std::endl;
	std::cout << "Unrecognized network layer packets: " << other_network_count << std::endl;
	std::cout << "Unrecognized transport layer packets: " << other_transport_count << std::endl;
}

template <class C>
void register_size( boost::optional<C>& current_max, boost::optional<C>& current_min, const C& new_val ) {
	if(!current_max || *current_max < new_val) {
		current_max = new_val;
	}

	if(!current_min || *current_min > new_val) { 
		current_min = new_val;
	}
}

ParseHint map_ip_proto_to_hint(size_t proto) {
	switch(proto) {
		case 1:
			return ParseHint(true, PType::Transport::ICMP_ECHO);
		case 17:
			return ParseHint(true, PType::Transport::UDP);
		case 6:
#ifdef LOGGING
			LOG(INFO) << "TCP found on ip";
#endif
			return ParseHint(true, PType::Transport::TCP);
		default:
#ifdef LOGGING
				LOG(WARNING) << "Unknown protocol discovered riding an ip horse";
#endif
			return false;
	}
}

ParseHint resultsC::process_protocol(const Ipv4& ip) {
	ipv4_count++;
	register_size(ipv4_max_size, ipv4_min_size, ip.size());
	ParseHint hint = map_ip_proto_to_hint(ip.protocol.to_ulong());
	if(hint.get_should_parse() == false ) {
		other_transport_count++;
	}
	return hint;
}

ParseHint resultsC::process_protocol(const Ethernetv2& ether) {
	this->ethernet_v2_count++;
	return true;
}

ParseHint resultsC::process_protocol(const Ethernet8023& ether) {
	this->ethernet_8023++;
	return true;
}

ParseHint resultsC::process_protocol(const Echo& echo) {
	this->icmp_echo_count++;
	return false;
}

ParseHint resultsC::process_protocol(const Udp& echo) {
	this->udp_count++;
	return true;
}

ParseHint resultsC::process_protocol(const Tcp& tcp) {
	this->tcp_count++;
	return true;
}

ParseHint resultsC::process_protocol(const DNS& echo) {
	this->dns_count++;
	return false;
}

ParseHint resultsC::process_protocol(const Arp& arp) {
	this->arp_count++;
	return false;
}

ParseHint resultsC::process(const ProtocolPtr proto) {
	switch(proto->what_type()) {

		///////////////////////////////////////////////////////
		// Application Layer
		///////////////////////////////////////////////////////

		case PType::APPLICATION:
#ifdef LOGGING
			LOG(INFO) << "Uknown application protocol";
#endif
			other_application_count++;
			return false;

		case PType::Application::DNS:
#ifdef LOGGING
			LOG(INFO) << "Parsed dns";
#endif
			return process_protocol(*boost::dynamic_pointer_cast<DNS>(proto));

		///////////////////////////////////////////////////////
		// Transport Layer
		///////////////////////////////////////////////////////

		case PType::TRANSPORT:
			other_transport_count++;
#ifdef LOGGING
			LOG(INFO) << "Uknown transport protocol";
#endif
			return false;

		case PType::Transport::ICMP_ECHO:
#ifdef LOGGING
			LOG(INFO) << "Parsed icmp echo";
#endif
			return process_protocol(*boost::dynamic_pointer_cast<Echo>(proto));


		case PType::Transport::UDP:
#ifdef LOGGING
			LOG(INFO) << "Parsed udp";
#endif
			return process_protocol(*boost::dynamic_pointer_cast<Udp>(proto));

		case PType::Transport::TCP:
#ifdef LOGGING
			LOG(INFO) << "Parsed tcp";
#endif
			return process_protocol(*boost::dynamic_pointer_cast<Tcp>(proto));

		///////////////////////////////////////////////////////
		// Network Layer
		///////////////////////////////////////////////////////

		case PType::NETWORK:
#ifdef LOGGING
			LOG(INFO) << "Uknown network protocol";
#endif
			other_network_count++;
			return false;

		case PType::Network::IPV4:
#ifdef LOGGING
			LOG(INFO) << "Ipv4 parsed";
#endif
			return process_protocol(*boost::dynamic_pointer_cast<Ipv4>(proto));

		case PType::Network::ARP:
#ifdef LOGGING
			LOG(INFO) << "Arp parsed";
#endif
			return process_protocol(*boost::dynamic_pointer_cast<Arp>(proto));

		///////////////////////////////////////////////////////
		// Link Layer
		///////////////////////////////////////////////////////

		case PType::LINK:
			other_link_count++;
#ifdef LOGGING
			LOG(INFO) << "Uknown link protocol";
#endif
			return false;

		case PType::Link::ETHERNET_UNKNOWN:
			other_link_count++;
#ifdef LOGGING
			LOG(WARNING) << "Ethernet found, but type unknown: not counted";
#endif
			return false;

		case PType::Link::ETHERNET_8023:
#ifdef LOGGING
			LOG(INFO) << "Ethernet 802.3 protocol parsed";
#endif
			return process_protocol(*boost::dynamic_pointer_cast<Ethernet8023>(proto));

		case PType::Link::ETHERNET_V2:
#ifdef LOGGING
			LOG(INFO) << "Ethernet II protocol parsed";
#endif
			return process_protocol(*boost::dynamic_pointer_cast<Ethernetv2>(proto));

		///////////////////////////////////////////////////////
		// Unknown Layer
		///////////////////////////////////////////////////////

		default:
#ifdef LOGGING
			LOG(FATAL) << "No label for protocol with num: " << proto->what_type();
#endif
			// flow over on purpose here
		case PType::UNKNOWN:
#ifdef LOGGING
			LOG(WARNING) << "Unknown protocol";
#endif
			return false;
	}
}
