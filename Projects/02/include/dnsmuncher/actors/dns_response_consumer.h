/*
 * dns_response_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_response_consumer_h__
#define __dns_response_consumer_h__

#include "dnsmuncher/config.h"
#include "dns_consumer.h"
#include "dnsmuncher/domain/dns.h"

class DNSResponseConsumer: public DNSConsumer {
	public:
		DNSResponseConsumer( boost::shared_ptr<DNS>& result ) : DNSConsumer(result) { }
		virtual void run(int socket_fd);

};

#endif /* !__dns_response_consumer_h__ */

