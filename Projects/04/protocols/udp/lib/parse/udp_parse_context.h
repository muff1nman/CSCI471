/*
 * udp_parse_context.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef UDP_PARSE_CONTEXT_H
#define UDP_PARSE_CONTEXT_H

#include "udp/domain/udp_builder.h"
#include "networkmuncher/util/byte/parse_context.h"

class UdpParseContext : public ParseContext {
	public:
		UdpParseContext( const BytesContainer& raw_data, const
				BytesContainer::const_iterator& start, const
				BytesContainer::const_iterator& finish, const BytesContainer::const_iterator
				current, boost::shared_ptr<UdpBuilder> b) : 
			ParseContext(raw_data,start,finish,current), b(b) { }

    UdpParseContext( const ParseContext& other, boost::shared_ptr<UdpBuilder> b ) : ParseContext(other), b(b) { }

		boost::shared_ptr<UdpBuilder> b;

		UdpParseContext( const UdpParseContext& other, size_t offset_from_start) :
			ParseContext(other), b(other.b) { }

	private:
		UdpParseContext( const UdpParseContext& other );

};


#endif /* !UDP_PARSE_CONTEXT_H */

