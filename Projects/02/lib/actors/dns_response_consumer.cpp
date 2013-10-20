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
	std::vector<std::string> records = filter_cnames( this->result );
	if( !records.empty() ) {
		for( std::vector<std::string>::const_iterator i = records.begin(); i != records.end(); ++i ) {
			std::cout << *i << std::endl;
		}
	} else {
		std::cerr << "No record available" << std::endl;
	}
}



