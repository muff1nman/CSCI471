/*
 * dns_producer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_producer_h__
#define __dns_producer_h__

#include "consumer.h"

class DnsProducer : public Consumer {
	public:
		DnsProducer() { }

		virtual void run(int socket_fd);

		virtual ~DnsProducer() { }
};

#endif /* !__dns_producer_h__ */

