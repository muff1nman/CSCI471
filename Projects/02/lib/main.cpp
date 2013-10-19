/*
 * main.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/config.h"
#include "dnsmuncher/actors/consumer.h"
#include "dnsmuncher/actors/data_producer.h"
#include "dnsmuncher/data/dns_convert.h"
#include "dnsmuncher/domain/dns_builder.h"
#include "dnsmuncher/actors/dns_consumer.h"
#include "dnsmuncher/actors/dns_response_consumer.h"
#include "dnsmuncher/socket/socket.h"
#include "main_helper.h"

#include <iostream>
#include <boost/bind.hpp>

#ifdef LOGGING
#include <glog/logging.h>
#endif

using namespace std;
namespace po = boost::program_options;


// Runs a consumer and deletes it after completion.
void socket_thread_runner(int fd, boost::shared_ptr<Consumer> c) {
	c->run(fd);
#ifdef LOGGING
	LOG(INFO) << "Thread finalizing";
#endif

#ifdef LOGGING
	LOG(INFO) << "Releasing resources";
#endif
	c.reset();

#ifdef LOGGING
	LOG(INFO) << "Closing spawned socket(not the listening one)";
#endif
	// No need to close socket with new Socket class
	//close_socket(fd);
#ifdef LOGGING
	LOG(INFO) << "Thread released";
#endif
}

void send_and_receive( boost::shared_ptr<DNS> query ) {	
	Socket socket(SOCK_DGRAM, 16318);
	boost::shared_ptr<Convert> dns_data( new DNSConvert(query) );
	boost::shared_ptr<Consumer> gen(new DataProducer(dns_data));
	boost::function<void(int)> sfunc = boost::bind(&socket_thread_runner, _1, gen);
	socket.connect("8.8.8.8", 53, sfunc);

	boost::shared_ptr<DNS> result;
	boost::shared_ptr<Consumer> parse( new DNSResponseConsumer(result) );
	boost::function<void(int)> rfunc = boost::bind(&socket_thread_runner, _1, parse);
	socket.accept( rfunc );

#ifdef LOGGING
	LOG(INFO) << "Received dns result: " << result->to_string();
#endif

}

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
			.add_question( Question(configs[NAME_OPTION].as< string >(), Type::A, NetClass::IN) )
			.question_count(1)
			.recursion_desired(true);
		boost::shared_ptr<DNS> to_send = b.build_ptr();
		send_and_receive( to_send );
	}

	return 0;
}


