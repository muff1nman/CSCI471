/*
 * dns_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_consumer_h__
#define __dns_consumer_h__

#include "dnsmuncher/config.h"
#include "echo_consumer.h"
#include "dnsmuncher/domain/dns.h"

class DNSConsumer: public EchoConsumer {
	public:
		DNSConsumer( boost::shared_ptr<DNS>& result ) : result(result) { }
		virtual void run(int socket_fd);

	protected:
		boost::shared_ptr<DNS>& result;

};
#endif /* !__dns_consumer_h__ */

