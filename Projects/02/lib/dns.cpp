/*
 * dns.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/config.h"
#include "dnsmuncher/dns.h"
#include "dnsmuncher/actors/data_producer.h"
#include "dnsmuncher/data/dns_convert.h"
#include "dnsmuncher/actors/dns_response_consumer.h"
#include "dnsmuncher/socket/socket.h"
#include <boost/bind.hpp>
#include <string>

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

//boost::optional<std::string> filter_first_ip( boost::shared_ptr<DNS> query ) {

//}

//boost::optional<std::string> filter_first_ns( boost::shared_ptr<DNS> query ) {

//}

//boost::optional<std::string> filter_first_cname( boost::shared_ptr<DNS> query ) {

//}

void send_and_receive( const std::string& server, boost::shared_ptr<DNS> query ) {	
	Socket socket(SOCK_DGRAM, 16318);
	boost::shared_ptr<Convert> dns_data( new DNSConvert(query) );
	boost::shared_ptr<Consumer> gen(new DataProducer(dns_data));
	boost::function<void(int)> sfunc = boost::bind(&socket_thread_runner, _1, gen);
	socket.connect(server.c_str(), 53, sfunc);

	boost::shared_ptr<DNS> result;
	boost::shared_ptr<Consumer> parse( new DNSResponseConsumer(result) );
	boost::function<void(int)> rfunc = boost::bind(&socket_thread_runner, _1, parse);
	socket.accept( rfunc );

#ifdef LOGGING
	LOG(INFO) << "Received dns result: " << result->to_string();
#endif

}


