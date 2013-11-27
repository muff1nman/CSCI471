/*
 * dns_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_consumer_h__
#define __dns_consumer_h__

#include "dns/config.h"
#include "dns/domain/dns.h"
#include "dns/dns.h"

#include "networkmuncher/actors/echo_consumer.h"
#include "networkmuncher/config.h"

#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>

class DNSConsumer: public EchoConsumer {
	public:
		DNSConsumer( DnsMaybePtr& result ) : result(result) { }
		virtual void run(Socket* socket);

	protected:
		DnsMaybePtr& result;

};
#endif /* !__dns_consumer_h__ */

