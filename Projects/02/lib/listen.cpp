/*
 * main.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/config.h"
#include "main_helper.h"
#include "dnsmuncher/socket/helper.h"
#include "dnsmuncher/socket/socket.h"
#include "dnsmuncher/actors/consumer.h"
#include "dnsmuncher/actors/echo_consumer.h"
#include "dnsmuncher/actors/data_producer.h"
#include "dnsmuncher/data/dns_convert.h"
#include "dnsmuncher/actors/dns_consumer.h"

#include <iostream>
#include <string>
#include <boost/optional.hpp>

#ifdef LOGGING
#include <glog/logging.h>
#endif

using namespace std;
namespace po = boost::program_options;

// Runs a consumer and deletes it after completion.
void thread_runner(int fd) {
	boost::shared_ptr<DNS> result;
	boost::shared_ptr<Consumer> c(new DNSConsumer(result));
	c->run(fd);
#ifdef LOGGING
	LOG(INFO) << "Runner finalizing";
#endif
}

int main( int argc, char** argv ) {
	po::variables_map configs = parse_args( argc, argv );

	if( !check_args(configs) ) {
		cout << "Invalid options" << endl;
	}

	init_log(configs[LOG_LEVEL_OPTION].as< size_t>());

#ifdef LOGGING
	LOG(INFO) << "Connecting in new thread";
#endif
	Socket s(SOCK_DGRAM, 16318);
	s.accept(&thread_runner);

	return 0;
}


