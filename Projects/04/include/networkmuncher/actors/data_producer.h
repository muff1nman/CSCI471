/*
 * data_producer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __socket_data_producer_h__
#define __socket_data_producer_h__

#include "socket_consumer.h"
#include "networkmuncher/data/convert.h"
#include "networkmuncher/util/byte/byte.h"

#include <unistd.h>
#ifdef LOGGING
#include <glog/logging.h>
#include <cstring>
#endif

#include <sys/socket.h>
#include <sys/types.h>
#include <boost/shared_ptr.hpp>

class SocketDataProducer : public SocketConsumer {
	public:
		SocketDataProducer( boost::shared_ptr<Convert> obj_ptr) : convertable(obj_ptr) { }

		virtual void run(Socket* socket) {
			BytesContainer bytes = convertable->to_data();
			// TODO check ret value?
			socket->send(bytes);
		}

	private:
		boost::shared_ptr<Convert> convertable;

};

#endif /* !__data_producer_h__ */
