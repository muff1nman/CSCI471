/*
 * parse_context.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __util_parse_context_h__
#define __util_parse_context_h__

#include "byte.h"

#include <boost/shared_ptr.hpp>

class ParseContext {
	public:
		typedef BytesContainer::const_iterator ConstIterator;
		ParseContext(const BytesContainer& raw_data) : raw_data(raw_data), start(raw_data.begin()), finish(raw_data.end()), current(raw_data.begin()) {
			//start = raw_data.begin();
			//finish = raw_data.end();
			//current = start;
		}

		ParseContext(
				const BytesContainer& raw_data,
				const ConstIterator& start,
				const ConstIterator& finish,
				const ConstIterator current) :
			raw_data(raw_data), start(start), finish(finish), current(current) { }

		const BytesContainer& raw_data;
		const ConstIterator start;
		const ConstIterator finish;
		ConstIterator current;

		ParseContext( const ParseContext& other, size_t offset_from_start ) : raw_data(other.raw_data), start(other.start), finish(other.finish) {
			current = other.raw_data.begin() + offset_from_start;
		}

};

typedef boost::shared_ptr<ParseContext> ParseContextPtr;

#endif /* !__util_parse_context_h__ */

