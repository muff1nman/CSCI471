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

/**
 * Does some additional logging in addition to what DNSConsumer provides
 */
class DNSResponseConsumer: public DNSConsumer {
	public:
		DNSResponseConsumer( DnsMaybePtr& result, Type t = Type::A ) : DNSConsumer(result), t(t) { }
		virtual void run(int socket_fd);

	protected:
		Type t;

};

#endif /* !__dns_response_consumer_h__ */

