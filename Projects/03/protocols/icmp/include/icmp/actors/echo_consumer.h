/*
 * echo_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_ACTORS_ECHO_CONSUMER_H
#define ICMP_ACTORS_ECHO_CONSUMER_H

#include "networkmuncher/actors/echo_consumer.h"

#include "icmp/domain/domain.h"
#include "icmp/parse/echo.h"

class IcmpEchoConsumer : public Consumer {
	public:
		IcmpEchoConsumer( EchoMaybePtr& result ) : result(result) { }
		virtual void run(Socket* socket) {
			BytesContainer raw_data = socket->recv();
			result = ECHO::from_data_as_ptr( raw_data );
		}

	protected:
		EchoMaybePtr& result;
};


#endif /* !ICMP_ACTORS_ECHO_CONSUMER_H */

