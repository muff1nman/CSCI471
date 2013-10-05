/*
 * main.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/config.h"
#include "dnsmuncher/socket/connect.h"
#include "dnsmuncher/socket/helper.h"
#include "dnsmuncher/actors/consumer.h"
#include "dnsmuncher/actors/data_producer.h"
#include "dnsmuncher/data/dns_convert.h"

#include <iostream>
#include <string>
#include <boost/optional.hpp>
#include <boost/bind.hpp>

#ifdef LOGGING
#include <glog/logging.h>
#endif

using namespace std;


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
	close_socket(fd);
#ifdef LOGGING
	LOG(INFO) << "Thread released";
#endif
}


string print_usage( int argc, char** argv ) {
	string use = 
		"Usage: ./dnsmuncher [Host] [Nameserver]\n"
		"\n"
		"Host:        Name to query for\n"
		"Nameserver:  IP address of DNS server\n";
	return use;
}

boost::optional<string> parse_internal( int argc, char** argv, size_t position ) {
	boost::optional<string> ret_val;
	if( argc > position ) {
		ret_val = string(argv[position]);
	}
	return ret_val;
}

boost::optional<string> parse_host( int argc, char** argv ) {
	return parse_internal(argc, argv, HOST_POSITION);
}

boost::optional<string> parse_server( int argc, char** argv ) {
	return parse_internal(argc, argv, SERVER_POSITION);
}

string print_info( int argc, char** argv ) {
	string info = std::string("info:\n");
#ifdef DEBUG
	info += "DEBUG ON\n";
#endif
#ifdef LOGGING
	info += "LOGGING ON\n";
	info += string("LOG LEVEL: ") + (char) ((int) '0' + LOG_LEVEL) + "\n";
#endif
	return info;
}

void init_log() {
#ifdef LOGGING
	google::InitGoogleLogging("DNSMuncher");
	FLAGS_minloglevel = LOG_LEVEL;
	FLAGS_alsologtostderr = 1;
	FLAGS_colorlogtostderr = 1;
#endif
}

int main( int argc, char** argv ) {
	init_log();
	cout << print_usage(argc, argv) << endl;
	cout << print_info(argc, argv) << endl;
	boost::optional<string> host, ip;

	host = parse_host( argc, argv );
	ip = parse_server( argc, argv );

	if( !host || !ip ) {
		cout << "Invalid options" << endl;
		return 1;
	} 

#ifdef DEBUG
	cout << "Host: " << *host << endl;
	cout << "Server ip: " << *ip << endl;
#endif

#ifdef LOGGING
	LOG(INFO) << "Connecting in new thread";
#endif

	boost::shared_ptr<Convert> convert( new DNSConvert() );
	boost::shared_ptr<Consumer> c(new DataProducer(convert));
	boost::function<void(int)> func = boost::bind(&socket_thread_runner, _1, c);
	//connect_in_new_thread( "8.8.8.8", 53, func );
	connect_in_new_thread( "127.0.0.1", 16318, func );

#ifdef LOGGING
	LOG(INFO) << "Done with connection";
#endif

	sleep(12312);

	return 0;
}


