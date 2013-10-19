/*
 * dns_response_consumer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/actors/dns_response_consumer.h"
#include "dnsmuncher/parse/ip.h"
#include <iostream>

void DNSResponseConsumer::run(int socket_fd) {
	DNSConsumer::run(socket_fd);
	for( size_t i = 0; i < result->get_resource_records().size(); ++i ) {
		std::string ip_address = ip_from_data( result->get_resource_records().at(i).get_data() );
		std::cout << ip_address << std::endl;
	}
}



