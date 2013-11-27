/*
 * socket_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef SOCKET_CONSUMER_H
#define SOCKET_CONSUMER_H

#include "consumer.h"

class SocketConsumer : public Consumer {
	public:
		virtual void run(Socket* socket) {
#ifdef LOGGING
			LOG(INFO) << "Consuming socket";
#endif
			boost::optional<BytesContainer> raw_data = socket->recv();
			if(raw_data) {
				ParseContextPtr context( new ParseContext( *raw_data, raw_data->begin(), raw_data->end(), raw_data->begin()));
				consume( context );
#ifdef LOGGING
			} else {
			LOG(WARNING) << "Could not retrieve data from socket";
#endif
			}
		}
};

#endif /* !SOCKET_CONSUMER_H */

