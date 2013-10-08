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
#ifdef LOGGING
#include <glog/logging.h>
#include <cstring>
#endif

#include <sys/socket.h>
#include <sys/types.h>

class DataProducer : public Consumer {
	public:
		DataProducer( boost::shared_ptr<Convert> obj_ptr) : convertable(obj_ptr) { }

		virtual void run(int socket_fd) {
			BytesContainer bytes = convertable->to_data();
#ifdef LOGGING
			LOG(INFO) << "Writing to socket [" << socket_fd << "]";
#endif
			//int result = write(socket_fd, bytes.data.get(), bytes.size);
			int result = send(socket_fd, bytes.data.get(), bytes.size, 0);
#ifdef LOGGING
			if( result < 0 ) {
				LOG(INFO) << "Could not write to socket: " << strerror(errno);
			} else {
				LOG(INFO) << "[" << result << "] bytes written";
			}
#endif
			// TODO need to call sync?
		}

	private:
		boost::shared_ptr<Convert> convertable;

};

#endif /* !__data_producer_h__ */

