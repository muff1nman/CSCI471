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
	if( result->response_code() != DNS::NO_ERROR ) {
		DNS::ResourceList answers = result->get_answers();
		if( answers.empty()) {
			std::cerr << "There were no answers" << std::endl;
		}
		for( size_t i = 0; i < answers.size(); ++i ) {
			std::string ip_address = ip_from_data( answers.at(i)->get_data() );
			std::cout << ip_address << std::endl;
		}
	} else {
		std::cerr << "There was an error" << std::endl;
	}
}



