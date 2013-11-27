/*
 * dns_producer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_producer_h__
#define __dns_producer_h__

#include "networkmuncher/actors/socket_consumer.h"

/**
 * Main intent is to be used for the server/daemon feature.  It will parse a
 * given request, fire off a separte series of queries to find the answer and
 * then respond to the first request. Although this class should really have
 * inherited from DnsConsumer, there were some incompatabilities that I hope to
 * resolve in the future \\TODO
 */
class DnsProducer : public SocketConsumer {
	public:
		DnsProducer() { }

		virtual void run(Socket* socket);

		virtual ~DnsProducer() { }
};

#endif /* !__dns_producer_h__ */

