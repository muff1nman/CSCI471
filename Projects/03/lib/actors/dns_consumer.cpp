/*
 * dns_consumer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "networkmuncher/actors/dns_consumer.h"
#include "networkmuncher/socket/helper.h"
#include "networkmuncher/parse/dns.h"

void DNSConsumer::run(int socket_fd) {
	BytesContainer raw_data = all_data(socket_fd);
	result = from_data_as_ptr( raw_data );
}



