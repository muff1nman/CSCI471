/*
 * ip_parse_context.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IP_PARSE_CONTEXT_H
#define IP_PARSE_CONTEXT_H

#include "icmp/domain/ip_builder.h"
#include "networkmuncher/util/byte/parse_context.h"

class IpParseContext : public ParseContext {
	public:
		IpParseContext( const BytesContainer& raw_data, const
				BytesContainer::const_iterator& start, const
				BytesContainer::const_iterator& finish, const BytesContainer::const_iterator
				current, boost::shared_ptr<IpBuilder> b) : 
			ParseContext(raw_data,start,finish,current), b(b) { }

    IpParseContext( const ParseContext& other, boost::shared_ptr<IpBuilder> b ) : ParseContext(other), b(b) { }

		boost::shared_ptr<IpBuilder> b;

		IpParseContext( const IpParseContext& other, size_t offset_from_start) :
			ParseContext(other), b(other.b) { }

	private:
		IpParseContext( const IpParseContext& other );

};


#endif /* !IP_PARSE_CONTEXT_H */

