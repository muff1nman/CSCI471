/*
 * main.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "httpmuncher/config.h"

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
#ifdef DEBUG
	info += "DEBUG ON\n";
#endif
#ifdef LOGGING
	info += "LOGGING ON\n";
	info += string("LOG LEVEL: ") + (char) ((int) '0' + LOG_LEVEL) + "\n";
#endif
	return info;
}

int main( int argc, char** argv ) {
	cout << print_usage(argc, argv) << endl;
	cout << print_info(argc, argv) << endl;

	return 0;
}


