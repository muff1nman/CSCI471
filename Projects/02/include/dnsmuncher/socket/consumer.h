/*
 * consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __consumer_h__
#define __consumer_h__

#include "dnsmuncher/util/logging.h"

#include <unistd.h>

class Consumer : public Logging {

	public:

		Consumer(int socket_fd) : socket_fd(socket_fd) { }

		virtual void run() {
#ifdef LOGGING
			LOG(INFO) << "Doing operation with open socket";
#endif
		}

		virtual ~Consumer() {
			close_socket();
		}

		virtual void close_socket() {
			int close_status = close(socket_fd);
			if( close_status != SUCCESS ) {
#ifdef LOGGING
				// TODO put error code here
				LOG(ERROR) << "Could not close socket: ";
				// TODO do something better?
#endif
			}
		}

	protected:
		int socket_fd;
};

#endif /* !__consumer_h__ */

