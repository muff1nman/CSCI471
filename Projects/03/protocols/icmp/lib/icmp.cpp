/*
 * icmp.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "icmp/icmp.h"

#include "icmp/domain/domain.h"

boost::optional<Echo> ping_and_pong_once( const std::string& dest_ip, EchoPtr request ) {
	boost::optional<Echo> to_return;

	// TODO

	//EchoPtr echo_request = EchoBuilder()
		//.set_request_type()
		//.set_identifier(IDENTIFER)
		//.set_sequence_num(1)
		//.set_data(Echo::Data(RANDOM_DATA))
		//.build_ptr();

	return to_return;
}


