/*
 * parse_context.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __parse_context_h__
#define __parse_context_h__


#include "dnsmuncher/util/byte/byte.h"
#include <boost/shared_ptr.hpp>

class ParseContext {
	public:
		ParseContext( const BytesContainer& raw_data, const
				BytesContainer::const_iterator& start, const
				BytesContainer::const_iterator& finish, BytesContainer::const_iterator
				current, boost::shared_ptr<DNSBuilder> b) : 
			raw_data(raw_data), start(start), finish(finish), current(current), b(b) { }

		const BytesContainer& raw_data;
		const BytesContainer::const_iterator& start;
		const BytesContainer::const_iterator& finish;
		BytesContainer::const_iterator current;
		boost::shared_ptr<DNSBuilder> b;

};

#endif /* !__parse_context_h__ */

