/*
 * ethernet_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ETHERNET_ACTORS_ECHO_CONSUMER_H
#define ETHERNET_ACTORS_ECHO_CONSUMER_H

#include "networkmuncher/actors/socket_consumer.h"

#include "ethernet/domain/domain.h"
#include "ethernet/parse/raw.h"

#include "networkmuncher/util/byte/parse_context.h"

class EthernetEchoConsumer : public SocketConsumer {
	public:
		EthernetConsumer( EthernetMaybePtr& result ) : result(result) { }

		virtual void consume( ParseContextPtr context ) {
			result = ETHERNET::from_data_as_ptr( *context );
		}

	protected:
		EthernetMaybePtr& result;
};


#endif /* !ETHERNET_ACTORS_ECHO_CONSUMER_H */

