/*
 * copy.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __copy_h__
#define __copy_h__

#include "dnsmuncher/util/byte/byte.h"

#include <bitset>

// TODO test
template <size_t M, size_t N>
void copy_into( std::bitset<M> dst, std::bitset<N> src, size_t dst_offset_from_right = 0, size_t src_offset_from_right = 0 ) {

}

// TODO test
template <size_t M, size_t N>
std::bitset<N> dissect( std::bitset<M> src, size_t src_offset_from_right = 0 ) {
	return std::bitset<N>(0);
}

// TODO test
BytesContainer join( BytesContainer first, BytesContainer second ) {
	BytesContainer joined;
	joined.reserve(first.size() + second.size());
	joined.insert( joined.end(), first.begin(), first.end() );
	joined.insert( joined.end(), second.begin(), second.end() );
	return joined;
}

#endif /* !__copy_h__ */

