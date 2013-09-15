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
	this->request_header = new HttpRequestHeader(split_away_raw_header( socket_fd ));
#ifdef LOGGING
	LOG(INFO) << "request header is: " << this->request_header->to_string();
#endif
}

HeaderRequestConsumer::~HeaderRequestConsumer(){ 
	if( this->request_header != NULL ) {
		delete this->request_header;
		this->request_header = NULL;
	}
}


