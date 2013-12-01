/*
 * tcp_parse_context.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef TCP_PARSE_CONTEXT_H
#define TCP_PARSE_CONTEXT_H

#include "tcp/domain/tcp_builder.h"
#include "networkmuncher/util/byte/parse_context.h"

class TcpParseContext : public ParseContext {
	public:
		TcpParseContext( const BytesContainer& raw_data, const
				BytesContainer::const_iterator& start, const
				BytesContainer::const_iterator& finish, const BytesContainer::const_iterator
				current, boost::shared_ptr<TcpBuilder> b) : 
			ParseContext(raw_data,start,finish,current), b(b) { }

    TcpParseContext( const ParseContext& other, boost::shared_ptr<TcpBuilder> b ) : ParseContext(other), b(b) { }

		boost::shared_ptr<TcpBuilder> b;

		TcpParseContext( const TcpParseContext& other, size_t offset_from_start) :
			ParseContext(other), b(other.b) { }

	private:
		TcpParseContext( const TcpParseContext& other );

};


#endif /* !TCP_PARSE_CONTEXT_H */

