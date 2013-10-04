/*
 * data_producer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __data_producer_h__
#define __data_producer_h__

#include "consumer.h"
#include "dnsmuncher/data/convert.h"
#include "dnsmuncher/util/byte.h"
#include <unistd.h>

class DataProducer : public Consumer {
	public:
		DataProducer(int socket_fd, boost::shared_ptr<Convert> obj_ptr) : Consumer(socket_fd), convertable(obj_ptr) { }

		virtual void run() {
			BytesContainer bytes = convertable->to_data();
			write(socket_fd, bytes.data.get(), bytes.size);
			// TODO need to call sync?
		}

	private:
		boost::shared_ptr<Convert> convertable;

};

#endif /* !__data_producer_h__ */

