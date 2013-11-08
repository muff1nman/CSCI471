/*
 * main_helper.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __main_helper_h__
#define __main_helper_h__

#include "networkmuncher/config.h"
#include "networkmuncher/dns/config.h"
#include "networkmuncher/dns/domain/type.h"
#include "networkmuncher/dns/domain/qtype.h"

#ifdef LOGGING
#include <glog/logging.h>
#endif

#include <boost/program_options.hpp>
#include <string>
#include <iostream>
#include <cstdio>

namespace po = boost::program_options;

void init_log(size_t log_level) {
#ifdef LOGGING
	google::InitGoogleLogging(PROJECT_NAME);
	FLAGS_minloglevel = log_level;
	FLAGS_alsologtostderr = 1;
	FLAGS_colorlogtostderr = 1;
#endif
}

bool check_query_optionals( po::variables_map configs ) {
	// TODO need to have these as implicit values in order to check this
	// return configs.count( TYPE_OPTION ) == 1;
	return false;
}

bool check_server_optionals( po::variables_map configs ) {
	// TODO need to have these as implicit values in order to check this
	// return configs.count( PORT_OPTION ) == 1;
	return false;
}

bool check_query( po::variables_map configs ) {
	return configs.count( QUERY_OPTION ) == 1 
		&& configs.count( NAME_OPTION ) == 1 
		&& !check_server_optionals( configs );
}

bool check_server( po::variables_map configs ) {
	return configs.count( DAEMON_OPTION ) == 1 
		&& !check_query_optionals( configs );
}

bool check_args( po::variables_map configs ) {
	// Just a simple XOR op
	return check_query( configs ) != check_server( configs );
}

po::variables_map parse_args( int argc, char** argv ) {

	po::options_description dns_options(
			"Welcome to the DNS Muncher! (the original name before I changed it to dug)\n"
			"The program can be either run interactively or as a daemon. "
			"To run interactively you can use the query and the name option and optionally with the type option. "
			"Also, the program will automatically interpret two arguments as the name and query if you do not use the switches. \n"
			"i.e. networkmuncher [name] [server_to_query] ~ networkmuncher www.google.com 8.8.8.8\n"
			"Here is a description of each option\n");
	dns_options.add_options()

		/**
		 * Standard options
		 */
		(HELP_OPTION_LS,
		 "Show help\n")

		(QUERY_OPTION_LS, po::value< std::string >(),
		 "Send a query to the given server.  Currenlty server must be an ip address as I will not resolve your server names for you\n"
		 "  i.e. 8.8.8.8\n")

		(NAME_OPTION_LS, po::value< std::string >(),
		 "Use the given domain name. Acceptable domain names are in the form of:\n"
		 "  some.name.com.\n"
		 "  some.name.com\n"
		 "Empty strings are not allowed\n")

		(TYPE_OPTION_LS, po::value< size_t >()->default_value(1),
		 "Query for the given type. Defaults to 1 (A)\n")

		(DAEMON_OPTION_LS, 
		 "Daemonize the program so as to receive dns udp queries on the specifice port (see --port).\n")

		(PORT_OPTION_LS, po::value< size_t >()->default_value(42345),
		 "When using the daemon option, you can change the default listening port\n")

		/**
		 * Debugging options
		 */
		(LOG_LEVEL_OPTION_LS, po::value< size_t >()->default_value(1),
		 "If you have compiled networkmuncher with LOGGING enabled, you can change the log level. Levels are as follows:\n"
		 "  0: INFO\n"
		 "  1: WARNING\n"
		 "  2: ERROR\n"
		 "  3: FATAL\n")

		(DEBUG_OPTION_LS,
		 "Debug should be compiled in by default. Use this option to enable its output. Does not work for daemon mode.\n")

		// Semi colon marks end of options (DONT REMOVE)
		;


	po::positional_options_description positions;
	positions.add(NAME_OPTION, 1);
	positions.add(QUERY_OPTION, 1);

	po::variables_map configs;

	try {
		po::store(po::command_line_parser(argc, argv).options(dns_options).positional(positions).run(), configs);
		// TODO call this in main?
		po::notify(configs);
	} catch(...) {
		std::cerr << "Invalid options" << std::endl;
		exit(1);
	}

	if (configs.count(HELP_OPTION)) {
		std::cout << dns_options << std::endl;
		exit(0);
	}

	return configs;
}

#endif /* !__main_helper_h__ */

