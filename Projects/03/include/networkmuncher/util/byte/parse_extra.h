/*
 * parse_extra.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef UTIL_PARSE_EXTRA_H
#define UTIL_PARSE_EXTRA_H

#include <boost/optional.hpp>
#include "copy.h"
#include "parse_context.h"
#include "networkmuncher/util/logging.h"
#include "networkmuncher/util/iterator.h"

inline size_t current_index( ParseContext& context ) {
	return std::distance( context.start, context.current );
}

inline bool context_has_bytes_left( const ParseContext& context, size_t bytes ) {
	return std::distance(context.current, context.finish) >= (int) bytes;
}

template <size_t bytes>
inline boost::optional<std::bitset<bytes * BITS_PER_BYTE> > parse_bitset( ParseContext& context ) {
	boost::optional<std::bitset<bytes * BITS_PER_BYTE> > bytes_to_return;
	if( context_has_bytes_left( context, bytes ) ) {
		std::bitset<BITS_PER_BYTE> cache;
		std::bitset<bytes * BITS_PER_BYTE> temp;
		for( size_t i = 0; i < bytes; ++i ) {
			cache = *(context.current);
			temp =  temp << BITS_PER_BYTE;
			copy_into(temp, cache);
			std::advance( context.current, 1);
		}

		bytes_to_return = temp;
	}
#ifdef LOGGING
	else {
		LOG(INFO) << "cannot parse bitset";
	}
#endif

	return bytes_to_return;

}

// N is the number of bytes
template <class T, size_t N>
inline boost::optional<T> parse_number( ParseContext& context ) {
	boost::optional<T> data;
	boost::optional< std::bitset<N * BITS_PER_BYTE> > parsed_bitset = parse_bitset<N>(context);
	if(parsed_bitset) {
		data = parsed_bitset->to_ulong();
	}

	return data;
}

inline bool is_zero_byte( ParseContext& context ) {
	return context_has_bytes_left( context, 1 )  && *(context.current) == (Byte) 0;
}

inline bool parse_zero_byte( ParseContext& context ) {
	if( is_zero_byte( context ) ) {
		std::advance( context.current, 1 );
		return true;
	}
	return false;
}

inline boost::optional<BytesContainer> parse_data( ParseContext& context, size_t length ) {
#ifdef LOGGING
	LOG(INFO) << "#parse_data called with length " << length;
#endif
	boost::optional<BytesContainer> c;
	if( context_has_bytes_left( context, length ) ) {
		BytesContainer::const_iterator end_of_rdata = next(context.current,length);
		c = BytesContainer(context.current, end_of_rdata);
		context.current = end_of_rdata;
	}
#ifdef LOGGING
	else {
		LOG(WARNING) << "Not enough bytes left";
	}
#endif

	return c;

}

// possibly no data left, in which case this will return an empty bytescontainer
inline BytesContainer parse_remaining_data( ParseContext& context ) {
	size_t bytes_left = std::distance(context.current, context.finish);
	return *parse_data(context,bytes_left);
}



#endif /* !UTIL_PARSE_EXTRA_H */

