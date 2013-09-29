/*
 * echo_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __echo_consumer_h__
#define __echo_consumer_h__

#include "consumer.h"

#include <stdio.h>

class EchoConsumer : public Consumer {
	public:

		EchoConsumer(int fd) : Consumer(fd) {
#ifdef LOGGING
			LOG(INFO) << "Echo Consumer created with fd: " << fd;
#endif
		}

		virtual void run() {
			while(true) {
#ifdef LOGGING
				LOG(INFO) << "Reading from socket...";
#endif
				int read_status = read(socket_fd, buffer, BUFSIZE - 1);

				if( read_status > 0 ) {
#ifdef LOGGING
					LOG(INFO) << "Content read from connection" << "\nSTART REQUEST\n" << buffer << "\nPOSSIBLE END REQUEST (more content in next buffer?)";
#endif
				} else if(read_status == 0 ) {
#ifdef LOGGING
					LOG(INFO) << "No more bytes";
#endif
					break; // natural end of stream?
				} else {
#ifdef LOGGING
					LOG(ERROR) << "read status: " << read_status;
#endif
					break;
				}
			}
		}

	private:
		static const int BUFSIZE = 1026;
		char buffer[BUFSIZE];

};

#endif /* !__echo_consumer_h__ */

