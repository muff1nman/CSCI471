/*
 * consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __consumer_h__
#define __consumer_h__

#include "dnsmuncher/util/logging.h"

class Consumer : public Logging {

	public:

		Consumer(int socket_fd) : socket_fd(socket_fd) { }

		virtual void run();

		virtual ~Consumer();

		virtual void close_socket();

	protected:
		int socket_fd;
};

#endif /* !__consumer_h__ */

