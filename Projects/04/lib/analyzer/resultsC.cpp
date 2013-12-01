//
//  resultsC.cc
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "analyzer.h"
#include "networkmuncher/domain/protocol_types.h"


// ***************************************************************************
// * displayResults:
// *  This method will be called once, after all the packets have been
// *  processed.  You should use this to print all the statistics you
// *  collected to stdout.
// ***************************************************************************
void resultsC::displayResults() {
  std::cout << "A total of " << totalPacketCount << " packets processed." << std::endl;
	std::cout << "Ethernet II packets: " << ethernet_v2_count << std::endl;
	std::cout << "Ethernet 802.3 packets: " << ethernet_8023 << std::endl;
	std::cout << "Ip packets: " << ip_count << std::endl;
	if(ip_max_size) {
		std::cout << "Max Ip size: " << *ip_max_size << std::endl;
	}
	if(ip_min_size) {
		std::cout << "Min Ip size: " << *ip_min_size << std::endl;
	}
}

template <class C>
void register_size( boost::optional<C>& current_max, boost::optional<C>& current_min, const C& new_val ) {
	if(!current_max || current_max < new_val) {
		current_max = new_val;
	}

	if(!current_min || current_min > new_val) { 
		current_min = new_val;
	}
}

void resultsC::count_protocol(const Ip& ip) {
	ip_count++;
	register_size(ip_max_size, ip_min_size, ip.size());
}

void resultsC::count_protocol(const Ethernetv2& ether) {
	this->ethernet_v2_count++;
}

void resultsC::count_protocol(const Ethernet8023& ether) {
	this->ethernet_8023++;
}

void resultsC::count(const ProtocolPtr proto) {
	switch(proto->what_type()) {

		///////////////////////////////////////////////////////
		// Application Layer
		///////////////////////////////////////////////////////

		case PType::APPLICATION:
#ifdef LOGGING
			LOG(INFO) << "Uknown application protocol";
#endif
			break;

		///////////////////////////////////////////////////////
		// Transport Layer
		///////////////////////////////////////////////////////

		case PType::TRANSPORT:
#ifdef LOGGING
			LOG(INFO) << "Uknown transport protocol";
#endif
			break;

		///////////////////////////////////////////////////////
		// Network Layer
		///////////////////////////////////////////////////////

		case PType::NETWORK:
#ifdef LOGGING
			LOG(INFO) << "Uknown network protocol";
#endif
			break;

		case PType::Network::IPV4:
			count_protocol(*boost::dynamic_pointer_cast<Ip>(proto));
#ifdef LOGGING
			LOG(INFO) << "Ipv4 parsed";
#endif
			break;

		///////////////////////////////////////////////////////
		// Link Layer
		///////////////////////////////////////////////////////

		case PType::LINK:
#ifdef LOGGING
			LOG(INFO) << "Uknown link protocol";
#endif
			break;

		case PType::Link::ETHERNET_UNKNOWN:
#ifdef LOGGING
			LOG(WARNING) << "Ethernet found, but type unknown: not counted";
#endif
			break;

		case PType::Link::ETHERNET_8023:
			count_protocol(*boost::dynamic_pointer_cast<Ethernet8023>(proto));
#ifdef LOGGING
			LOG(INFO) << "Ethernet 802.3 protocol parsed";
#endif
			break;

		case PType::Link::ETHERNET_V2:
			count_protocol(*boost::dynamic_pointer_cast<Ethernetv2>(proto));
#ifdef LOGGING
			LOG(INFO) << "Ethernet II protocol parsed";
#endif
			break;

		///////////////////////////////////////////////////////
		// Unknown Layer
		///////////////////////////////////////////////////////

		default:
#ifdef LOGGING
			LOG(FATAL) << "No label for protocol with num: " << proto->what_type();
#endif
		case PType::UNKNOWN:
#ifdef LOGGING
			LOG(WARNING) << "Unknown protocol";
#endif
			break;
	}
}
