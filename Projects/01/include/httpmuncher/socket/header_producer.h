/*
 * header_producer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __header_producer_h__
#define __header_producer_h__

#include "httpmuncher/response/status.h"
#include "httpmuncher/socket/header_request_consumer.h"
#include "httpmuncher/domain/http_response_header.h"

class HeaderProducer: public HeaderRequestConsumer {

	public:
		HeaderProducer( int fd ) : HeaderRequestConsumer(fd) { }

		virtual void run() {
			HeaderRequestConsumer::run();
			std::string to_write = send_back();
			write(socket_fd, to_write.c_str(), to_write.size());
		}

		virtual std::string send_back() {
			HttpResponseHeader h;
			h.set("Content-Length", "91");
			h.set("Content-Type", "text/html");
			return h.as_socket_data() + HTTP::debug_404_html;
		}

		virtual ~HeaderProducer() { /*noop*/ }

};

#endif /* !__header_producer_h__ */

