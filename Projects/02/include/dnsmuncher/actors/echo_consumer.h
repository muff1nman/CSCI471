/*
 * echo_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __echo_consumer_h__
#define __echo_consumer_h__

#include "consumer.h"
#include "dnsmuncher/util/byte_print.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

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
					LOG(INFO) << "Read " << read_status << " bytes from connection" << "\nSTART REQUEST\n" << buffer << "\nPOSSIBLE END REQUEST (more content in next buffer?)";
					LOG(INFO) << std::endl << demaria_util::to_string(buffer, read_status, 4, 12 );
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

