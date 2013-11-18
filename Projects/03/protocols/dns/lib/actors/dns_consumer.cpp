/*
 * dns_consumer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dns/actors/dns_consumer.h"
#include "dns/parse/dns.h"

void DNSConsumer::run(Socket* socket) {
	boost::optional<BytesContainer> raw_data = socket->recv();
	if( raw_data ) {
		result = from_data_as_ptr( *raw_data );
	}
}



