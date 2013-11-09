/*
 * echo.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "networkmuncher/socket/socket.h"
#include "networkmuncher/socket/helper.h"
#include "networkmuncher/actors/echo_consumer.h"
#include "networkmuncher/util/logging.h"

#include <iostream>

void echo(int fd) {
	boost::shared_ptr<Consumer> c = boost::shared_ptr<Consumer>(new EchoConsumer());
	socket_thread_runner(fd, c);
}

using namespace std;

int main( int argc, char** argv ) {
	int port = 16318;
	cout << "Listen on port: [" << port << "]" << endl;
	init_log(0, "ECHO");
	while(true) {
		Socket socket(SOCK_DGRAM, port );
		// Here is where the real work gets done.  See the #server function
		socket.accept( &echo );
	}
}

