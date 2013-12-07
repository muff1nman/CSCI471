//
//  resultsC.cc
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "analyzer.h"
#include "networkmuncher/domain/protocol_types.h"
#include "networkmuncher/util/math.h"
#include <string>
#include <algorithm>

void display_size_stats(const char* name, std::vector<size_t> sizes) {
	if(sizes.size() > 0 ) {
		std::cout << "Max " << name << " size: " << *std::max_element(sizes.begin(), sizes.end()) << std::endl;
		std::cout << "Min " << name << " size: " << *std::min_element(sizes.begin(), sizes.end()) << std::endl;
		std::cout << "Average " << name << " size: " << average(sizes) << std::endl;
	} 
}


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
	display_size_stats("Ipv4",ipv4_sizes);
	std::cout << "Number of fragmented packets: " << number_of_fragmented << std::endl;
	std::cout << "Unique ipv4 addresses: " << ipv4_addresses.size() << std::endl;
	std::cout << "Ipv6 packets: " << ipv6_count << std::endl;
	display_size_stats("Ipv6",ipv6_sizes);
	std::cout << "Unique ipv6 addresses: " << ipv6_addresses.size() << std::endl;
	std::cout << "Arp packets: " << arp_count << std::endl;
	display_size_stats("Arp",arp_sizes);

	std::cout << std::endl << "Transport Layer Statistics" << std::endl << separator << std::endl;
	std::cout << "Icmp echo packets: " << icmp_echo_count << std::endl;
	display_size_stats("Icmp",icmp_sizes);
	std::cout << "Upd packets: " << udp_count << std::endl;
	display_size_stats("Udp",udp_sizes);
	std::cout << "Unique udp ports: " << udp_ports.size() << std::endl;
	std::cout << "Tcp packets: " << tcp_count << std::endl;
	display_size_stats("Tcp",tcp_sizes);
	std::cout << "Unique tcp ports: " << tcp_ports.size() << std::endl;
	std::cout << "Number of tcp packets with syn: " << number_of_syns << std::endl;
	std::cout << "Number of tcp packets with ack: " << number_of_acks << std::endl;

	std::cout << std::endl << "Application Layer Statistics" << std::endl << separator << std::endl;
	std::cout << "Dns packets: " << dns_count << std::endl;
	std::cout << "Number of queries: " << number_of_queries << std::endl;
	std::cout << "Number of questions found in queries: " << number_of_questions << std::endl;
	std::cout << "Number of resursion desired queries: " << number_of_recursive_queries << std::endl;
	std::cout << "Number of responses: " << number_of_responses << std::endl;
	std::cout << "Number of authoritative responses: " << number_of_authoritative << std::endl;
	std::cout << "Number of resource records found in responses: " << number_of_resource_records << std::endl;
	std::cout << "Unique labels: " << labels.size() << std::endl;

	std::cout << std::endl << "Misc" << std::endl << separator << std::endl;
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

ParseHint resultsC::process_protocol(const Ipv4& ip, size_t size) {
	ipv4_count++;
	ipv4_sizes.push_back(size);
	ipv4_addresses.insert(ip.source_addr);
	ipv4_addresses.insert(ip.dest_addr);
	if(ip.is_fragmented()) {
		number_of_fragmented++;
	}
	ParseHint hint = map_ip_proto_to_hint(ip.protocol.to_ulong());
	if(hint.get_should_parse() == false ) {
		other_transport_count++;
	}
	return hint;
}

ParseHint resultsC::process_protocol(const Ipv6& ip,size_t size) {
	ipv6_count++;
	ipv6_sizes.push_back(size);
	ipv6_addresses.insert(ip.source_addr);
	ipv6_addresses.insert(ip.dest_addr);
	ParseHint hint = map_ip_proto_to_hint(ip.next_header.to_ulong());
	if(hint.get_should_parse() == false ) {
		other_transport_count++;
	}
	return hint;
}

ParseHint resultsC::process_protocol(const Ethernetv2& ether,size_t size) {
	this->ethernet_v2_count++;
	return true;
}

ParseHint resultsC::process_protocol(const Ethernet8023& ether,size_t size) {
	this->ethernet_8023++;
	return true;
}

ParseHint resultsC::process_protocol(const Echo& echo,size_t size) {
	icmp_sizes.push_back(size);
	this->icmp_echo_count++;
	return false;
}

ParseHint resultsC::process_protocol(const Udp& udp, size_t size) {
	udp_sizes.push_back(size);
	udp_ports.insert(udp.dest);
	udp_ports.insert(udp.src);
	this->udp_count++;
	return true;
}

ParseHint resultsC::process_protocol(const Tcp& tcp, size_t size) {
	tcp_sizes.push_back(size);
	tcp_ports.insert(tcp.source_port);
	tcp_ports.insert(tcp.dest_port);
	if(tcp.is_syn()) {
		number_of_syns++;
	}
	if(tcp.is_ack()) {
		number_of_acks++;
	}
	this->tcp_count++;
	return true;
}

ParseHint resultsC::process_protocol(const DNS& dns, size_t size) {

	DNS::ResourceList resources = dns.get_resource_records();
	DNS::ResourceList::const_iterator i = resources.begin();
	for(;i != resources.end(); ++i ) {
		labels.insert((*i)->get_label_name().to_string());
	}
	DNS::QuestionList questions = dns.get_questions();
	DNS::QuestionList::const_iterator j = questions.begin();
	for(;j != questions.end(); ++j ) {
		labels.insert((*j)->get_name().to_string());
	}

	if(dns.is_response()) {
		++number_of_responses;
		number_of_resource_records += dns.get_resource_record_count();
		if(dns.is_authoritative()) {
			number_of_authoritative++;
		}
	} else {
		if(dns.is_recursion_desired()) {
			number_of_recursive_queries++;
		}
		++number_of_queries;
		number_of_questions += dns.get_question_count();

	}

	this->dns_count++;
	return false;
}

ParseHint resultsC::process_protocol(const Arp& arp,size_t size) {
	arp_sizes.push_back(size);
	this->arp_count++;
	return false;
}

ParseHint resultsC::process(const ProtocolPtr proto, size_t size) {
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
			return process_protocol(*boost::dynamic_pointer_cast<DNS>(proto), size);

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
			return process_protocol(*boost::dynamic_pointer_cast<Echo>(proto),size);


		case PType::Transport::UDP:
#ifdef LOGGING
			LOG(INFO) << "Parsed udp";
#endif
			return process_protocol(*boost::dynamic_pointer_cast<Udp>(proto),size);

		case PType::Transport::TCP:
#ifdef LOGGING
			LOG(INFO) << "Parsed tcp";
#endif
			return process_protocol(*boost::dynamic_pointer_cast<Tcp>(proto),size);

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
			return process_protocol(*boost::dynamic_pointer_cast<Ipv4>(proto),size);

		case PType::Network::IPV6:
#ifdef LOGGING
			LOG(INFO) << "Ipv6 parsed";
#endif
			return process_protocol(*boost::dynamic_pointer_cast<Ipv6>(proto),size);

		case PType::Network::ARP:
#ifdef LOGGING
			LOG(INFO) << "Arp parsed";
#endif
			return process_protocol(*boost::dynamic_pointer_cast<Arp>(proto),size);

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
			return process_protocol(*boost::dynamic_pointer_cast<Ethernet8023>(proto),size);

		case PType::Link::ETHERNET_V2:
#ifdef LOGGING
			LOG(INFO) << "Ethernet II protocol parsed";
#endif
			return process_protocol(*boost::dynamic_pointer_cast<Ethernetv2>(proto),size);

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
