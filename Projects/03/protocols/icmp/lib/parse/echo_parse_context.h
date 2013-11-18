/*
 * echo_parse_context.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ECHO_PARSE_CONTEXT_H
#define ECHO_PARSE_CONTEXT_H

#include "icmp/domain/echo_builder.h"
#include "networkmuncher/util/byte/parse_context.h"

class EchoParseContext : public ParseContext {
	public:
		EchoParseContext( const BytesContainer& raw_data, const
				BytesContainer::const_iterator& start, const
				BytesContainer::const_iterator& finish, const BytesContainer::const_iterator
				current, boost::shared_ptr<EchoBuilder> b) : 
			ParseContext(raw_data,start,finish,current), b(b) { }

    EchoParseContext( const ParseContext& other, boost::shared_ptr<EchoBuilder> b ) : ParseContext(other), b(b) { }

		boost::shared_ptr<EchoBuilder> b;

		EchoParseContext( const EchoParseContext& other, size_t offset_from_start) :
			ParseContext(other), b(other.b) { }

	private:
		EchoParseContext( const EchoParseContext& other );

};


#endif /* !ECHO_PARSE_CONTEXT_H */

