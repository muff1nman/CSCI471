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
#include <vector>
#include <numeric>
#include <algorithm>

#include <boost/optional.hpp>
#include <boost/regex.hpp>
#include <boost/timer.hpp>

using namespace std;

bool is_ip(const string& str) {
	boost::regex ip_addr_regex("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");
	if(boost::regex_match(str, ip_addr_regex)) {
		return true;
	}
	return false;
}

double average(const std::vector<double>& nums) {
	return std::accumulate(nums.begin(), nums.end(), 0.0) / (double) nums.size();
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

	size_t i(ATTEMPTS);
	std::vector<double> times;

	boost::timer stopwatch;
	for(;i > 0; --i) {
		stopwatch.restart();
		EchoMaybePtr echo = ping_and_pong_once( *host_ip );
		if(echo) {
			times.push_back(stopwatch.elapsed());
			cout << (*echo)->to_string() << endl;
		} else {
			cout << "No response" << endl;
		}
	}

	if( !times.empty() ) {
		cout << "Average: " << average(times) << endl;
		cout << "Min:     " << *min_element(times.begin(), times.end()) << endl;
		cout << "Max:     " << *max_element(times.begin(), times.end()) << endl;
	}

}



