/*
 * icmp.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "icmp/icmp.h"
#include "icmp/config.h"
#include "icmp/domain/domain.h"
#include "icmp/data/data.h"
#include "icmp/actors/echo_consumer.h"
#include "networkmuncher/actors/actors.h"
#include "networkmuncher/socket/socket.h"

#include <boost/assign.hpp>

EchoMaybePtr ping_and_pong_once( const std::string& dest_ip, EchoPtr request ) {
	EchoMaybePtr to_return;
	
	Socket socket(SOCK_RAW, IPPROTO_ICMP);

	boost::shared_ptr<Consumer> send_icmp( new DataProducer ( boost::shared_ptr<Convert>( new EchoConvert( request ) )));
	socket.connect(dest_ip.c_str(), 0, send_icmp);

	// TODO filter other raw stuffs
	boost::shared_ptr<Consumer> receive_icmp( new IcmpEchoConsumer(to_return));
	socket.accept(receive_icmp);
	
	return to_return;
}

EchoMaybePtr ping_and_pong_once( const std::string& dest_ip ) {

	BytesContainer random_data = boost::assign::list_of
		('\x12') ('\x3f') ('\x97') ('\xf6') ('\xab')
		;

	EchoPtr echo_request = EchoBuilder()
		.set_request_type()
		.set_identifier(IDENTIFER)
		.set_sequence_num(1)
		.set_data(Echo::Data(random_data))
		.build_ptr();

	return ping_and_pong_once( dest_ip, echo_request );
}


