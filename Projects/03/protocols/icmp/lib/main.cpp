/*
 * main.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "icmp/config.h"
#include "networkmuncher/config.h"
#include "networkmuncher/util/logging.h"

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
	if( argc < 2 ) {
		cerr << "Please supply a hostname" << endl;
		exit(ERROR_NO_HOSTNAME);
	}

	init_log(LOG_LEVEL, "Pong");

	string host_name(argv[1]);

	cout << host_name << endl;
}



