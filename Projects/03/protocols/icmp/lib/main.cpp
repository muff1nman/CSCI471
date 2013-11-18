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
#include <sys/time.h>


#include <boost/optional.hpp>
#include <boost/regex.hpp>

using namespace std;

void ms_ping_time( const string& host_ip, EchoMaybePtr& response, boost::optional<double>& elaspsed ) {

	struct timeval initial_time;
	struct timeval current_time;
	int time_ret_val;

	time_ret_val = gettimeofday(&initial_time, NULL);
	if(time_ret_val != 0 ) {
		perror("Could not get time");
		exit(1);
	}

	cout << "Pinging [" << host_ip << "]" << endl;

	response = ping_and_pong_once( host_ip );
	if(response) {
		time_ret_val = gettimeofday(&current_time, NULL);
		if(time_ret_val != 0 ) {
			perror("Could not get time");
			exit(1);
		}
		elaspsed = (double)(current_time.tv_sec - initial_time.tv_sec) * (1000) + (double)(current_time.tv_usec - initial_time.tv_usec) / (1000);
	}

}

bool is_ip(const string& str) {
	boost::regex ip_addr_regex("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}");
	if(boost::regex_match(str, ip_addr_regex)) {
		return true;
	}
	return false;
}

double average(const std::vector<double>& nums) {
	double sum = std::accumulate(nums.begin(), nums.end(), 0.0);
	return sum / (double) nums.size();
}

int main(int argc, char** argv) {
	if( argc < 2 ) {
		cerr << "Please supply a hostname" << endl;
		exit(ERROR_NO_HOSTNAME);
	}

	init_log(LOG_LEVEL, "Pong");

	string host_name(argv[1]);

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


	size_t i(ATTEMPTS);
	std::vector<double> times;

	for(;i > 0; --i) {
		boost::optional<double> elaspsed;
		EchoMaybePtr echo;
		ms_ping_time(*host_ip, echo, elaspsed);
		if(elaspsed) {
			times.push_back(*elaspsed);
		} else {
			cout << "No response" << endl;
		}
	}

	if( !times.empty() ) {
		cout << "Average: " << average(times) << " ms" << endl;
		cout << "Min:     " << *min_element(times.begin(), times.end()) << " ms" << endl;
		cout << "Max:     " << *max_element(times.begin(), times.end()) << " ms" << endl;
	} else {
		cout << "No respones" << endl;
	}

}



