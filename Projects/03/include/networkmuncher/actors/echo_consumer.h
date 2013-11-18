/*
 * echo_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __echo_consumer_h__
#define __echo_consumer_h__

#include "consumer.h"
#include "networkmuncher/util/byte/print.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#ifndef LOGGING
#include <iostream>
#endif

class EchoConsumer : public Consumer {
	public:

		virtual void run(Socket* socket) {
			boost::optional<BytesContainer> b = socket->recv();
			if(b) {
#ifndef LOGGING
				std::cout << "Recieved bytes:" << std::endl;
				std::cout << demaria_util::to_string(*b) << std::endl;
#else
				LOG(INFO) << "Recieved bytes:" << "\n" << demaria_util::to_string(*b);
#endif
			}
		}

};

#endif /* !__echo_consumer_h__ */

