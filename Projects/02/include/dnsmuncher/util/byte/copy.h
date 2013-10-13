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
template <size_t N, size_t M>
void copy_into( std::bitset<N> dst, std::bitset<M> src, size_t dst_offset_from_right = 0, size_t src_offset_from_right = 0 ) {

}

// TODO test
BytesContainer join( BytesContainer first, BytesContainer second ) {
	BytesContainer joined;
	joined.reserve(first.size() + second.size());
	joined.insert( joined.end(), first.start(), first.end() );
	joined.insert( joined.end(), second.start(), second.end() );
	return joined;
}

#endif /* !__copy_h__ */

