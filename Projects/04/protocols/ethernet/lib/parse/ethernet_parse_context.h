/*
 * ethernet_parse_context.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ETHERNET_PARSE_CONTEXT_H
#define ETHERNET_PARSE_CONTEXT_H

#include "ethernet/domain/ethernet_builder.h"
#include "networkmuncher/util/byte/parse_context.h"

class EthernetParseContext : public ParseContext {
	public:
		EthernetParseContext( const BytesContainer& raw_data, const
				BytesContainer::const_iterator& start, const
				BytesContainer::const_iterator& finish, const BytesContainer::const_iterator
				current, boost::shared_ptr<EthernetBuilder> b) : 
			ParseContext(raw_data,start,finish,current), b(b) { }

    EthernetParseContext( const ParseContext& other, boost::shared_ptr<EthernetBuilder> b ) : ParseContext(other), b(b) { }

		boost::shared_ptr<EthernetBuilder> b;

		EthernetParseContext( const EthernetParseContext& other, size_t offset_from_start) :
			ParseContext(other), b(other.b) { }

	private:
		EthernetParseContext( const EthernetParseContext& other );

};


#endif /* !ETHERNET_PARSE_CONTEXT_H */

