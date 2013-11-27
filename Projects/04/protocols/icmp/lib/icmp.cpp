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
#include "icmp/actors/raw_consumer.h"
#include "networkmuncher/actors/actors.h"
#include "networkmuncher/socket/socket.h"
#include "networkmuncher/util/time.h"

#include <boost/assign.hpp>
#include <sys/time.h>

void valid_or_clear(const EchoPtr& expected, RawMaybePtr& actual ) {
	if(actual) {
		EchoPtr echo = (*actual)->echo;
		if( echo->identifier != expected->identifier ||
			echo->data != expected->data ||
			echo->sequence_num != expected->sequence_num || 
			false) 
		{
#ifdef LOGGING
			LOG(WARNING) << "Invalid response received";
#endif
			actual = RawMaybePtr();
		}
	}
}

void receive_and_validate( Socket& socket, const EchoPtr& matching_request, int timeout_in_seconds, RawMaybePtr& ret ) {
	bool time_remaining = true;

	struct timeval expected_finish;
	get_current_time(expected_finish);
	expected_finish.tv_sec += timeout_in_seconds;

	struct timeval current_time;
	struct timeval remaining_time;
	remaining_time.tv_sec = timeout_in_seconds;
	remaining_time.tv_usec = 0;

	do {
		boost::shared_ptr<SocketConsumer> receive_icmp( new RawConsumer(ret));
#ifdef LOGGING
		LOG(INFO) << "Set remaining time as: " << convert_to_seconds(remaining_time);;
#endif
		socket.set_timeout(remaining_time.tv_usec,remaining_time.tv_sec);
		socket.accept(receive_icmp);

		valid_or_clear( matching_request, ret );

		get_current_time(current_time);
		int ret_val = timeval_subtract(&remaining_time, &expected_finish, &current_time);
		time_remaining = ret_val == 0;
	} while( !ret && time_remaining );
}

EchoMaybePtr ping_and_pong_once( const std::string& dest_ip, EchoPtr request ) {

	EchoMaybePtr to_return;
	RawMaybePtr raw_ptr;

	Socket socket(SOCK_RAW, IPPROTO_ICMP);

	boost::shared_ptr<SocketConsumer> send_icmp( new SocketDataProducer ( boost::shared_ptr<Convert>( new EchoConvert( request ) )));
	socket.connect(dest_ip.c_str(), 0, send_icmp);

	receive_and_validate(socket, request, TIMEOUT_IN_SECONDS, raw_ptr);

	if( raw_ptr ) {
		to_return = ((*raw_ptr)->echo);
	}

	return to_return;
}

EchoMaybePtr ping_and_pong_once( const std::string& dest_ip ) {
	static int seq_num = 0;

	BytesContainer random_data = boost::assign::list_of
		('\x12') ('\x3f') ('\x97') ('\xf6') ('\xab')
		;

	EchoPtr echo_request = EchoBuilder()
		.set_request_type()
		.set_identifier(IDENTIFER)
		.set_sequence_num(++seq_num)
		.set_data(Echo::Data(random_data))
		.build_ptr();

	return ping_and_pong_once( dest_ip, echo_request );
}


