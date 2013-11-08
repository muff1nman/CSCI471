/*
 * copy.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __copy_h__
#define __copy_h__

#include "networkmuncher/util/byte/byte.h"

#include <bitset>
#include <vector>

template <size_t M, size_t N>
std::bitset<M> copy_into( std::bitset<M>& dst, const std::bitset<N>& src, size_t dst_offset_from_right = 0 ) {
	size_t i = dst_offset_from_right;
	size_t j = 0;
	while( i < M && j < N ) {
		dst[i] = src[j];
		++i;
		++j;
	}

	return dst;
}

template <size_t M, size_t N>
std::bitset<N> dissect( std::bitset<M> src, size_t src_offset_from_right = 0 ) {
	std::bitset<N> to_return;
	size_t i = 0;
	size_t j = src_offset_from_right;
	while( i < N && j < M ) {
		to_return[i] = src[j];
		++i;
		++j;
	}

	return to_return;
}

#endif /* !__copy_h__ */

