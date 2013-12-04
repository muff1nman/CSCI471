/*
 * arp_parse_context.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ARP_PARSE_CONTEXT_H
#define ARP_PARSE_CONTEXT_H

#include "arp/domain/arp_builder.h"
#include "networkmuncher/util/byte/parse_context.h"

class ArpParseContext : public ParseContext {
	public:
		ArpParseContext( const BytesContainer& raw_data, const
				BytesContainer::const_iterator& start, const
				BytesContainer::const_iterator& finish, const BytesContainer::const_iterator
				current, boost::shared_ptr<ArpBuilder> b) : 
			ParseContext(raw_data,start,finish,current), b(b) { }

    ArpParseContext( const ParseContext& other, boost::shared_ptr<ArpBuilder> b ) : ParseContext(other), b(b) { }

		boost::shared_ptr<ArpBuilder> b;

		ArpParseContext( const ArpParseContext& other, size_t offset_from_start) :
			ParseContext(other), b(other.b) { }

	private:
		ArpParseContext( const ArpParseContext& other );

};


#endif /* !ARP_PARSE_CONTEXT_H */

