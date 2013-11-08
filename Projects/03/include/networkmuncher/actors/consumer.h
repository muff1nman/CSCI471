/*
 * consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __consumer_h__
#define __consumer_h__

#include "networkmuncher/util/logging.h"

/**
 * The consumer class of classes are used for doing some action with a given
 * socket.  Typically they have a minimal constructor and the true meat is in
 * the run function that is expected to be called on an open socket. The run
 * function may typically be run more than once with a given instance of
 * Consumer but check the particular subclass to be sure.
 */
class Consumer : public Logging {

	public:

		virtual void run(int socket_fd);

		virtual ~Consumer();

};

#endif /* !__consumer_h__ */

