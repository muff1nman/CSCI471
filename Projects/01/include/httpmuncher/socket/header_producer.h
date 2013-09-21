/*
 * header_producer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __header_producer_h__
#define __header_producer_h__

#include "httpmuncher/socket/header_request_consumer.h"
#include "httpmuncher/config.h"

class HeaderProducer: public HeaderRequestConsumer {

	public:
		HeaderProducer( int fd ) : HeaderRequestConsumer(fd) { }

		virtual void run();

		virtual std::string get_path();

		virtual bool file_exists();

		virtual std::string body_contents();

		virtual std::string error_contents();

		virtual std::string send_back();

		virtual ~HeaderProducer() { /*noop*/ }

};

#endif /* !__header_producer_h__ */

