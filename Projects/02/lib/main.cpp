/*
 * main.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/config.h"
#include "main_helper.h"
#include "dnsmuncher/actors/consumer.h"
#include "dnsmuncher/actors/data_producer.h"
#include "dnsmuncher/data/dns_convert.h"
#include "dnsmuncher/domain/dns_builder.h"
#include "dnsmuncher/actors/dns_consumer.h"
#include "dnsmuncher/actors/dns_response_consumer.h"
#include "dnsmuncher/socket/socket.h"
#include "dnsmuncher/dns.h"

#include <iostream>
#include <boost/bind.hpp>

#ifdef LOGGING
#include <glog/logging.h>
#endif

using namespace std;
namespace po = boost::program_options;

int main( int argc, char** argv ) {

	po::variables_map configs = parse_args( argc, argv );

	if( !check_args(configs) ) {
		cout << "Invalid options" << endl;
	}

	init_log(configs[LOG_LEVEL_OPTION].as< size_t>());

	if( configs.count(QUERY_OPTION) == 1 ) {
		DNSBuilder b;
		b.set_id( 234 )
			.is_query()
			.add_question( Question(configs[NAME_OPTION].as< string >(), configs[TYPE_OPTION].as< size_t>(), NetClass::IN) )
			.question_count(1)
			.recursion_desired(false);
		boost::shared_ptr<DNS> to_send = b.build_ptr();
		DnsMaybePtr result = query_once_and_then_try_recursive( configs[QUERY_OPTION].as< string >(), to_send );
		if( result && (*result)->response_code() == DNS::NO_ERROR ) {
			MaybeNameOrIp ip = filter_first_ip( *result );
			if( ip ) { 
				if( (*result)->is_authoritative() ) {
					cout << "Authoritative answer: ";
				} else {
					cout << "Non-Authoritative answer: ";
				}
				cout << *ip << endl;
				return 0;
			}
		}

	}
	cout << "No domain" << endl;
	return 1;
}


