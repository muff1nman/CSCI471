/*
 * dns_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_consumer_h__
#define __dns_consumer_h__

#include "networkmuncher/dns/config.h"
#include "networkmuncher/dns/domain/dns.h"
#include "networkmuncher/dns/dns.h"

#include "networkmuncher/actors/echo_consumer.h"
#include "networkmuncher/config.h"

#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>

class DNSConsumer: public EchoConsumer {
	public:
		DNSConsumer( DnsMaybePtr& result ) : result(result) { }
		virtual void run(int socket_fd);

	protected:
		DnsMaybePtr& result;

};
#endif /* !__dns_consumer_h__ */

