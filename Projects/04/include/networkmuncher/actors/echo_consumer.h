/*
 * echo_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __echo_consumer_h__
#define __echo_consumer_h__

#include "socket_consumer.h"
#include "networkmuncher/util/byte/print.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#ifndef LOGGING
#include <iostream>
#endif

class EchoConsumer : public SocketConsumer {
	public:
		
		virtual void consumer(ParseContextPtr parse) {
#ifndef LOGGING
			std::cout << "Recieved bytes:" << std::endl;
			std::cout << demaria_util::to_string(*parse) << std::endl;
#else
			LOG(INFO) << "Recieved bytes:" << "\n" << demaria_util::to_string(*parse);
#endif
		}

};

#endif /* !__echo_consumer_h__ */

