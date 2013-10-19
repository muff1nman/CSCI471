/*
 * consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __consumer_h__
#define __consumer_h__

#include "dnsmuncher/util/logging.h"

class Consumer : public Logging {

	public:

		virtual void run(int socket_fd);

		virtual ~Consumer();

};

#endif /* !__consumer_h__ */

