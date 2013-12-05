/*
 * dns_response_consumer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dns/actors/dns_response_consumer.h"
#include "dns/domain/ns_resource_record.h"
#include "dns/domain/cname_resource_record.h"
#include "dns/dns.h"

#include <iostream>

void DNSResponseConsumer::run(Socket* socket) {
	DNSConsumer::run(socket);
	if( this->result ) {
		std::vector<std::string> records;
#ifdef LOGGING
		LOG(INFO) << "Consuming response of type: " << this->t;
#endif
		switch( this->t ) {
			case Type::CNAME:
				std::cout << "CNAME records" << std::endl;
				records	= filter_cnames( *(this->result) );
				break;
			case Type::SOA:
			case Type::NS:
				std::cout << "NS records:" << std::endl;
				records = filter_nameservers( *(this->result) );
				break;
			case Type::A:
			default:
				std::cout << "A records:" << std::endl;
				records = filter_ips( *(this->result) );
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
}



