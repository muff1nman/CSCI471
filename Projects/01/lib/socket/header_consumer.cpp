/*
 * header_consumer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "httpmuncher/socket/header_consumer.h"

void HeaderConsumer::run() {
	header = HttpHeader( split_away_raw_header( socket_fd ));
}

const char* HeaderConsumer::split_away_raw_header( int fd ) {
	// TODO
}



