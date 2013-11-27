/*
 * echo_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_ACTORS_ECHO_CONSUMER_H
#define ICMP_ACTORS_ECHO_CONSUMER_H

#include "networkmuncher/actors/socket_consumer.h"

#include "icmp/domain/domain.h"
#include "icmp/parse/raw.h"

#include "networkmuncher/util/byte/parse_context.h"

class IcmpEchoConsumer : public SocketConsumer {
	public:
		IcmpEchoConsumer( EchoMaybePtr& result ) : result(result) { }

		virtual void consume( ParseContextPtr context ) {
			result = ECHO::from_data_as_ptr( *context );
		}

	protected:
		EchoMaybePtr& result;
};


#endif /* !ICMP_ACTORS_ECHO_CONSUMER_H */

