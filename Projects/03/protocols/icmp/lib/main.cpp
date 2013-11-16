/*
 * main.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "icmp/config.h"

#include "dns/dns.h"

#include "networkmuncher/config.h"
#include "networkmuncher/util/logging.h"

#include "icmp/icmp.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <boost/optional.hpp>

using namespace std;

bool is_ip(const string& str) {
	// TODO
	return false;
}

int main(int argc, char** argv) {
	if( argc < 2 ) {
		cerr << "Please supply a hostname" << endl;
		exit(ERROR_NO_HOSTNAME);
	}

	init_log(LOG_LEVEL, "Pong");

	string host_name(argv[1]);

	cout << host_name << endl;

	boost::optional<string> host_ip;
	if( is_ip(host_name) ) {
		host_ip = host_name;
	} else {
		host_ip = dns_give_me_one_answer("8.8.8.8", host_name);
	}
	
	if(!host_ip) {
		cerr << "Could not resolve hostname" << endl;
		exit(ERROR_RESOLVE_HOSTNAME);
	} 

	cout << "Pinging [" << *host_ip << "]" << endl;

	ping_and_pong_once( *host_ip );
}



