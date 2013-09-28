/*
 * main.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/config.h"
#include "dnsmuncher/socket/connect.h"
#include "dnsmuncher/socket/consumer.h"

#include <iostream>
#include <string>
#include <boost/optional.hpp>

#ifdef LOGGING
#include <glog/logging.h>
#endif

using namespace std;

// Runs a consumer and deletes it after completion.
void thread_runner(int fd) {

	Consumer* c = new Consumer(fd);
	c->run();
#ifdef LOGGING
	LOG(INFO) << "Thread finalizing";
#endif
	delete c;
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

	LOG(INFO) << "Connecting in new thread";
	connect_in_new_thread( "8.8.8.8", 53, &thread_runner );

	sleep(12312);

	return 0;
}


