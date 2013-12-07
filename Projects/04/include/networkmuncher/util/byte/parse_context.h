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
		ParseContext(const BytesContainer& raw_data) : raw_data(raw_data), start(raw_data.begin()), finish(raw_data.end()) {
			set_to_index();
			//start = raw_data.begin();
			//finish = raw_data.end();
			//current = start;
		}

		ParseContext(
				const BytesContainer& raw_data,
				const ConstIterator& start,
				const ConstIterator& finish,
				const ConstIterator current) :
			raw_data(raw_data), start(start), finish(finish) {
				set_to_index();
		 	}

		const BytesContainer& raw_data;
		const ConstIterator start;
		const ConstIterator finish;
		boost::shared_ptr<ConstIterator> current;

		void set_to_index( size_t offset = 0 ) {
			current = boost::shared_ptr<ConstIterator>( new ConstIterator(raw_data.begin() + offset ));
		}

		size_t get_current_index() const {
			return std::distance( start, *current);
		}

		size_t get_remaining() const {
			return std::distance( *current, finish );
		}

		ConstIterator& get_current() const {
			return *current;
		}

		ParseContext( const ParseContext& other, size_t offset_from_start ) : raw_data(other.raw_data), start(other.start), finish(other.finish) {
			set_to_index(offset_from_start);
		}

	protected:
		ParseContext( const ParseContext& other ) : raw_data(other.raw_data), start(other.start), finish(other.finish), current(other.current) { }

};

typedef boost::shared_ptr<ParseContext> ParseContextPtr;

#endif /* !__util_parse_context_h__ */

