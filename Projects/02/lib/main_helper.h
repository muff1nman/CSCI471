/*
 * main_helper.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __main_helper_h__
#define __main_helper_h__

#include "dnsmuncher/config.h"

#ifdef LOGGING
#include <glog/logging.h>
#endif

#include <boost/program_options.hpp>
#include <string>
#include <iostream>

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

	po::options_description dns_options("Welcome to the DNS Muncher!" "\n" "Here are your options");
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
		 "  . (For the root server)\n"
		 "Empty strings are not allowed")

		/**
		 * Debugging options
		 */
		(LOG_LEVEL_OPTION, po::value< size_t >()->default_value(1),
		 "If you have compiled dnsmuncher with LOGGING enabled, you can change the log level. Levels are as follows:\n"
		 "  0: INFO\n"
		 "  1: WARNING\n"
		 "  2: ERROR\n"
		 "  3: FATAL\n")

		// Semi colon marks end of options (DONT REMOVE)
		;


	po::positional_options_description positions;
	positions.
		add(QUERY_OPTION, 1).
		add(NAME_OPTION, 1);

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

