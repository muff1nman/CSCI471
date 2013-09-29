/*
 * helper.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __helper_h__
#define __helper_h__

#include "dnsmuncher/util/logging.h"

void close_socket(int socket_fd) {
	int close_status = close(socket_fd);
	if( close_status < 0 ) {
#ifdef LOGGING
		// TODO put error code here
		LOG(ERROR) << "Could not close socket: ";
		// TODO do something better?
#endif
	}
}

#endif /* !__helper_h__ */

