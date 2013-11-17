/*
 * operations.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef UTIL_BYTE_OPERATIONS_H
#define UTIL_BYTE_OPERATIONS_H

#include "byte.h"
#include "parse_extra.h"
#include <cmath>
#include "networkmuncher/util/logging.h"

template <size_t bytes>

void add_to_sum(std::bitset<bytes * BITS_PER_BYTE>& sum, const std::bitset<bytes * BITS_PER_BYTE>& to_add) {
	unsigned long result = sum.to_ulong() + to_add.to_ulong();
	unsigned long carry = pow(2, bytes * BITS_PER_BYTE);
	if( result >= carry ) {
		result += (1 - carry);
	}
	sum = std::bitset<bytes * BITS_PER_BYTE>(result);
}

template <size_t bytes>
std::bitset<bytes * BITS_PER_BYTE> ones_complement_sum( const BytesContainer& list_of_bytes ) {
	typedef std::bitset<bytes*BITS_PER_BYTE> RowOfBytes;
	boost::optional< RowOfBytes > current_row;

	RowOfBytes result(0);

	BytesContainer::const_iterator current = list_of_bytes.begin();
	BytesContainer::const_iterator end = list_of_bytes.end();


	while( current_row = parse_bitset<BytesContainer::const_iterator, bytes>(current, end) ) {
#ifdef LOGGING
		LOG(INFO) << "current bytes to be added: " << current_row->to_string();
#endif
		add_to_sum<bytes>(result, *current_row );
	}

	// check iterators match up
	if( current != end ) {
		// read extra bytes, padded with zeros to fill the rest of the bitset
		current_row = parse_bitset_with_missing_as_zeros<BytesContainer::const_iterator, bytes>(current,end);
		add_to_sum<bytes>(result, *current_row);

	}

	return result;

}

#endif /* !UTIL_BYTE_OPERATIONS_H */

