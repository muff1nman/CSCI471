/*
 * dns_parse_context.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_parse_context_h__
#define __dns_parse_context_h__

#include "dns/domain/dns_builder.h"
#include "networkmuncher/util/byte/parse_context.h"

class DNSParseContext : public ParseContext {
	public:
		DNSParseContext( const BytesContainer& raw_data, const
				BytesContainer::const_iterator& start, const
				BytesContainer::const_iterator& finish, const BytesContainer::const_iterator
				current, boost::shared_ptr<DNSBuilder> b) :
			ParseContext(raw_data,start,finish,current), b(b) { }

		boost::shared_ptr<DNSBuilder> b;

		DNSParseContext( const DNSParseContext& other, size_t offset_from_start) :
			ParseContext(other), b(other.b) { }

	private:
		DNSParseContext( const DNSParseContext& other );

};

#endif /* !__dns__parse_context_h__ */

