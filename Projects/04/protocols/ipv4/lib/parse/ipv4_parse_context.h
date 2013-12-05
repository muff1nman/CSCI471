/*
 * ipv4_parse_context.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IPV4_PARSE_CONTEXT_H
#define IPV4_PARSE_CONTEXT_H

#include "ipv4/domain/ipv4_builder.h"
#include "networkmuncher/util/byte/parse_context.h"

class Ipv4ParseContext : public ParseContext {
	public:
		Ipv4ParseContext( const BytesContainer& raw_data, const
				BytesContainer::const_iterator& start, const
				BytesContainer::const_iterator& finish, const BytesContainer::const_iterator
				current, boost::shared_ptr<Ipv4Builder> b) : 
			ParseContext(raw_data,start,finish,current), b(b) { }

    Ipv4ParseContext( const ParseContext& other, boost::shared_ptr<Ipv4Builder> b ) : ParseContext(other), b(b) { }

		boost::shared_ptr<Ipv4Builder> b;

		Ipv4ParseContext( const Ipv4ParseContext& other, size_t offset_from_start) :
			ParseContext(other), b(other.b) { }

	private:
		Ipv4ParseContext( const Ipv4ParseContext& other );

};


#endif /* !IPV4_PARSE_CONTEXT_H */

