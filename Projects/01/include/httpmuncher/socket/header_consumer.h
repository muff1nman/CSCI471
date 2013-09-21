/*
 * header_consumer.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __header_consumer_h__
#define __header_consumer_h__

#include "httpmuncher/socket/consumer.h"
#include "httpmuncher/domain/http_header.h"

class HeaderConsumer: public Consumer {
	public:
	 	HeaderConsumer( int fd ) : Consumer(fd) { header = NULL; }

		virtual ~HeaderConsumer();

		virtual void run();

		static std::string split_away_raw_header( int fd );

	protected:
		HttpHeader* header;

	private:
		static const int BUFSIZE = 1026;

};

#endif /* !__header_consumer_h__ */

