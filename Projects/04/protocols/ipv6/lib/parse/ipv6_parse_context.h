/*
 * ipv6_parse_context.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IPV6_PARSE_CONTEXT_H
#define IPV6_PARSE_CONTEXT_H

#include "ipv6/domain/ipv6_builder.h"
#include "networkmuncher/util/byte/parse_context.h"

class Ipv6ParseContext : public ParseContext {
	public:
		Ipv6ParseContext( const BytesContainer& raw_data, const
				BytesContainer::const_iterator& start, const
				BytesContainer::const_iterator& finish, const BytesContainer::const_iterator
				current, boost::shared_ptr<Ipv6Builder> b) : 
			ParseContext(raw_data,start,finish,current), b(b) { }

    Ipv6ParseContext( const ParseContext& other, boost::shared_ptr<Ipv6Builder> b ) : ParseContext(other), b(b) { }

		boost::shared_ptr<Ipv6Builder> b;

		Ipv6ParseContext( const Ipv6ParseContext& other, size_t offset_from_start) :
			ParseContext(other), b(other.b) { }

	private:
		Ipv6ParseContext( const Ipv6ParseContext& other );

};


#endif /* !IPV6_PARSE_CONTEXT_H */

