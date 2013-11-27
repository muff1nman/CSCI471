/*
 * echo.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "networkmuncher/socket/socket.h"
#include "networkmuncher/actors/echo_consumer.h"
#include "networkmuncher/util/logging.h"

#include <iostream>

boost::shared_ptr<SocketConsumer> gen_consumer() {
	return boost::shared_ptr<SocketConsumer>(new EchoConsumer());
}

using namespace std;

int main( int argc, char** argv ) {
	int port = 16318;
	cout << "Listen on port: [" << port << "]" << endl;
	init_log(0, "ECHO");
	while(true) {
		Socket socket(SOCK_RAW,IPPROTO_ICMP);
		//Socket socket(SOCK_DGRAM, IPPROTO_UDP, port );
		// Here is where the real work gets done.  See the #server function
		socket.accept( &gen_consumer, true );
	}
}

