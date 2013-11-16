/*
 * operations.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef UTIL_BYTE_OPERATIONS_H
#define UTIL_BYTE_OPERATIONS_H

#include "byte.h"

template <size_t bytes>
std::bitset<bytes * BITS_PER_BYTE> ones_complement_sum( const BytesContainer& list_of_bytes ) {
	// TODO
}

// This sucks and really should use iterators instead, but to avoid premature
// optimization it is what it is for now.
template <size_t bytes>
std::bitset<bytes * BITS_PER_BYTE> ones_complement_sum( const std::vector<std::bitset<bytes * BITS_PER_BYTE> >& list_of_segments ) {
	// TODO
}

#endif /* !UTIL_BYTE_OPERATIONS_H */

