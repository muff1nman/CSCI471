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
#include "dnsmuncher/dns.h"
#include <iostream>

void DNSResponseConsumer::run(int socket_fd) {
	DNSConsumer::run(socket_fd);
	std::vector<std::string> records;
#ifdef LOGGING
	LOG(INFO) << "Consuming response of type: " << this->t;
#endif
	switch( this->t ) {
		case Type::CNAME:
			records	= filter_cnames( this->result );
			break;
		case Type::SOA:
		case Type::NS:
			records = filter_nameservers( this->result);
			break;
		case Type::A:
		default:
			records = filter_ips( this->result );
			break;
	}
	if( !records.empty() ) {
		for( std::vector<std::string>::const_iterator i = records.begin(); i != records.end(); ++i ) {
			std::cout << *i << std::endl;
		}
	} else {
		std::cerr << "No record available" << std::endl;
	}
}



