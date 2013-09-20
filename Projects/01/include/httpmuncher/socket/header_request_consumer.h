/*
 * header_request_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __header_request_consumer_h__
#define __header_request_consumer_h__


#include "httpmuncher/domain/http_request_header.h"
#include "httpmuncher/socket/header_consumer.h"

class HeaderRequestConsumer : public HeaderConsumer {
	public:
		HeaderRequestConsumer( int fd ) : HeaderConsumer(fd) {
			request_header = NULL;
		}

		virtual void run();

		virtual ~HeaderRequestConsumer();

	protected:
		HttpRequestHeader* request_header;

};
#endif /* !__header_request_consumer_h__ */

