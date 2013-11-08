/*
 * consumer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "networkmuncher/actors/consumer.h"
#include "networkmuncher/config.h"

#ifdef DEBUG
#include <iostream>
#endif

#include <unistd.h>

void Consumer::run(int socket_fd) {
#ifdef LOGGING
	LOG(INFO) << "Doing operation with open socket";
#endif
}


Consumer::~Consumer() {
	// noop, not the consumers responsiblity of closing the socket
}

