/*
 * main.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "httpmuncher/config.h"
#include "httpmuncher/socket/socket.h"
#include "httpmuncher/util/number.h"

#ifdef LOGGING
#include <glog/logging.h>
#endif

#include <iostream>
#include <string>


using namespace std;

string print_usage( int argc, char** argv ) {
	string usage = std::string(argv[0]) + " usage";
	usage += "\n";
	return usage;
}

string print_info( int argc, char** argv ) {
	string info = std::string("info:\n");
    info += "PORT " + NumberToString(LISTEN_PORT) + string("\n");
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
	google::InitGoogleLogging("HttpMuncher");
	FLAGS_minloglevel = LOG_LEVEL;
	FLAGS_alsologtostderr = 1;
	FLAGS_colorlogtostderr = 1;
#endif
}

int main( int argc, char** argv ) {
	init_log();
	cout << print_usage(argc, argv) << endl;
	cout << print_info(argc, argv) << endl;

	accept_in_new_threads(LISTEN_PORT);

	return 0;
}


