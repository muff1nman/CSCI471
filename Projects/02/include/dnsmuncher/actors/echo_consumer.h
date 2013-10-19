/*
 * echo_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __echo_consumer_h__
#define __echo_consumer_h__

#include "consumer.h"
#include "dnsmuncher/util/byte/print.h"
#include "dnsmuncher/socket/helper.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

class EchoConsumer : public Consumer {
	public:

		virtual void run(int socket_fd) {
			BytesContainer b = all_data(socket_fd);
		}

};

#endif /* !__echo_consumer_h__ */

