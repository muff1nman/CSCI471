/*
 * status_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __status_consumer_h__
#define __status_consumer_h__

#include "httpmuncher/socket/consumer.h"
#include "httpmuncher/response/status.h"

#include <cstring>

class StatusConsumer: public Consumer {

	public:
		StatusConsumer( int fd, unsigned int status ) : Consumer(fd), status(status) { }

		virtual void run() {
			const char* to_write = response(status);
#ifdef LOGGING
			LOG(INFO) << "returning the following response:\n" << to_write;
#endif
			write(socket_fd, to_write, std::strlen(to_write));
		}

		static const char* response( unsigned int status ) {
			return HTTP::generic_response.at(status);
		}

	protected:
		unsigned int status;

	private:
		static const int BUFSIZE = 1026;
		char buffer[BUFSIZE];

};

#endif /* !__status_consumer_h__ */

