/*
 * raw_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_ACTORS_RAW_CONSUMER_H
#define ICMP_ACTORS_RAW_CONSUMER_H

#include "networkmuncher/actors/consumer.h"

#include "icmp/domain/domain.h"
#include "icmp/parse/raw.h"

#include "networkmuncher/util/byte/parse_context.h"

class RawConsumer : public Consumer {
	public:
		RawConsumer( RawMaybePtr& result ) : result(result) { }
		virtual void run(Socket* socket) {
			boost::optional<BytesContainer> raw_data = socket->recv();
			if(raw_data) {
				ParseContext context( *raw_data, raw_data->begin(), raw_data->end(), raw_data->begin());
				result = RAW::from_data_as_ptr( context );
			}
		}

	protected:
		RawMaybePtr& result;
};



#endif /* !ICMP_ACTORS_RAW_CONSUMER_H */

