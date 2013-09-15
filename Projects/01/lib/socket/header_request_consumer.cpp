/*
 * header_request_consumer.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "httpmuncher/socket/header_request_consumer.h"

void HeaderRequestConsumer::run() {
#ifdef LOGGING
	LOG(INFO) << "How about here?";
#endif
	this->header = new HttpRequestHeader(split_away_raw_header( socket_fd ));
#ifdef LOGGING
	LOG(INFO) << "request header is: " << this->header->to_string();
#endif
}



