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
		ParseContext(
				const BytesContainer& raw_data,
				const BytesContainer::const_iterator& start,
				const BytesContainer::const_iterator& finish,
				const BytesContainer::const_iterator current) :
			raw_data(raw_data), start(start), finish(finish), current(current) { }

		const BytesContainer& raw_data;
		const BytesContainer::const_iterator& start;
		const BytesContainer::const_iterator& finish;
		BytesContainer::const_iterator current;

		ParseContext( const ParseContext& other, size_t offset_from_start ) : raw_data(other.raw_data), start(other.start), finish(other.finish) {
			current = other.raw_data.begin() + offset_from_start;
		}

	protected:
		ParseContext( const ParseContext& other );

};

#endif /* !__util_parse_context_h__ */

