/*
 * dns_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_consumer_h__
#define __dns_consumer_h__


#include "echo_consumer.h"
#include "dnsmuncher/domain/dns.h"

#include <boost/shared_ptr.hpp>

class DNSConsumer: public EchoConsumer {
	public:
		virtual void run() {

		}

	protected:
		boost::shared_ptr<DNS> dns;

};
#endif /* !__dns_consumer_h__ */

