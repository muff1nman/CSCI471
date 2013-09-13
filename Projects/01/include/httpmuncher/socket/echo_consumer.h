/*
 * echo_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __echo_consumer_h__
#define __echo_consumer_h__

#include "httpmuncher/socket/consumer.h"

#include <stdio.h>

class EchoConsumer : public Consumer {
	public:

		EchoConsumer(int fd) : Consumer(fd) { }

		virtual void operator()() {
			while(true) {
				int read_status = read(socket_fd, buffer, BUFSIZE - 1);

				if( read_status > 0 ) {
					puts(buffer);
				} else {
					break;
				}
			}
		}

	private:
		static const int BUFSIZE = 1026;
		char buffer[BUFSIZE];

};

#endif /* !__echo_consumer_h__ */

