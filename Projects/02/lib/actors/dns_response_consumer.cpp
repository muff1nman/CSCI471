/*
 * dns_response_consumer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/actors/dns_response_consumer.h"
#include "dnsmuncher/parse/ip.h"
#include "dnsmuncher/domain/ns_resource_record.h"
#include "dnsmuncher/domain/cname_resource_record.h"
#include <iostream>

void DNSResponseConsumer::run(int socket_fd) {
	DNSConsumer::run(socket_fd);
	if( result->response_code() == DNS::NO_ERROR ) {
		DNS::ResourceList answers = result->get_answers();
		if( answers.empty()) {
			std::cerr << "There were no answers" << std::endl;
		}
		for( size_t i = 0; i < answers.size(); ++i ) {
			boost::shared_ptr<CNameResourceRecord> casted = boost::dynamic_pointer_cast<CNameResourceRecord>(answers.at(i));
			if( casted ) {
				std::string cname = casted->get_name().to_string();
				std::cout << cname << std::endl;
			} else { 
				std::string ip_address = ip_from_data( answers.at(i)->get_data() );
				std::cout << ip_address << std::endl;
			}
		}
		DNS::ResourceList nameservers = result->get_nameservers();
		if( nameservers.empty()) {
			std::cerr << "There were no nameservers" << std::endl;
		}
		for( size_t i = 0; i < nameservers.size(); ++i ) {
			boost::shared_ptr<NsResourceRecord> casted = boost::dynamic_pointer_cast<NsResourceRecord>(nameservers.at(i));
			if( casted ) {
				std::string name = casted->get_name().to_string();
				std::cout << name << std::endl;
			} else {
#ifdef LOGGING
				LOG(WARNING) << "Could not interpret as NS record, but here are the bytes:\n" << demaria_util::to_string(nameservers.at(i)->get_data());
#endif
			}
		}
	} else {
		std::cerr << "There was an error" << std::endl;
	}
}



