/*
 * consumer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/socket/consumer.h"
#include "socket_config.h"

#include <unistd.h>

void Consumer::run() {
#ifdef LOGGING
	LOG(INFO) << "Doing operation with open socket";
#endif
}


Consumer::~Consumer() {
	close_socket();
}

void Consumer::close_socket() {
	int close_status = close(socket_fd);
	if( close_status != SUCCESS ) {
#ifdef LOGGING
		// TODO put error code here
		LOG(ERROR) << "Could not close socket: ";
		// TODO do something better?
#endif
	}
}
