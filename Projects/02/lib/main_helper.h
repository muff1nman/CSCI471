/*
 * main_helper.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __main_helper_h__
#define __main_helper_h__

#include "dnsmuncher/config.h"
#include "dnsmuncher/domain/type.h"
#include "dnsmuncher/domain/qtype.h"

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

bool check_args( po::variables_map configs ) {
	// TODO
	return true;
}

po::variables_map parse_args( int argc, char** argv ) {

	po::options_description dns_options(
			"Welcome to the DNS Muncher!\n"
			"The program can be either run interactively or as a daemon. "
			"To run interactively you can use the query and the name option and optionally with the type option. "
			"Also, the program will automatically interpret two arguments as the name and query if you do not use the switches. \n"
			"i.e. dnsmuncher [name] [server_to_query] ~ dnsmuncher www.google.com 8.8.8.8\n"
			"Here is a description of each option");
	dns_options.add_options()

		/**
		 * Standard options
		 */
		(HELP_OPTION,
		 "Show help")

		(QUERY_OPTION, po::value< std::string >(),
		 "Send a query to the given server.  Currenlty server must be an ip address as I will not resolve your server names for you\n"
		 "  i.e. 8.8.8.8")

		(NAME_OPTION, po::value< std::string >(),
		 "Use the given domain name. Acceptable domain names are in the form of:\n"
		 "  some.name.com.\n"
		 "  some.name.com\n"
		 "Empty strings are not allowed")

		(TYPE_OPTION, po::value< size_t >()->default_value(1),
		 "Query for the given type. Defaults to 1 (A)")

		(DAEMON_OPTION, po::value< bool >()->implicit_value(true),
		 "Daemonize the program so as to receive dns udp queries on the specifice port (see --port).")

		(PORT_OPTION, po::value< size_t >()->default_value(42345),
		 "When using the daemon option, you can change the default listening port")

		/**
		 * Debugging options
		 */
		(LOG_LEVEL_OPTION, po::value< size_t >()->default_value(1),
		 "If you have compiled dnsmuncher with LOGGING enabled, you can change the log level. Levels are as follows:\n"
		 "  0: INFO\n"
		 "  1: WARNING\n"
		 "  2: ERROR\n"
		 "  3: FATAL\n")

		(DEBUG_OPTION,
		 "Debug should be compiled in by default. Use this option to enable its output. Does not work for daemon mode.")

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
		perror("Invalid options");
	}

	if (configs.count(HELP_OPTION)) {
		std::cout << dns_options << std::endl;
	}

	return configs;
}

#endif /* !__main_helper_h__ */

