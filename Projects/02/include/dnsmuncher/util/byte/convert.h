/*
 * convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __byte_convert_h__
#define __byte_convert_h__

#include "byte.h"

//http://stackoverflow.com/questions/3061721/concatenate-boostdynamic-bitset-or-stdbitset
template <size_t N1, size_t N2 >
std::bitset<N1 + N2> concat( const std::bitset<N1> & b1, const std::bitset<N2> & b2 ) {
    std::string s1 = b1.to_string();
    std::string s2 = b2.to_string();
	return std::bitset <N1 + N2>( s1 + s2 );
}

/**
 * Given an ordered stream of bits, returns the byte at a given offset.  
 *
 * For Little Endian, this offset starts at least significant set of bits (the
 * right most bit on a bit stream)
 *
 * For example with the following call
 * convert_to_char_little_endian<3,6>( std::string("110100"), 1 );
 *
 * index would count starting at the far right (index zero) and land at the 3rd
 * zero from the right to point at  "110"
 *
 * and 6 would be returned (in Byte form)
 *
 */
template <size_t width, size_t n>
Byte convert_to_char_little_endian( const std::bitset<n>& bits, size_t index = 0 ) {

	if ( n < width ) {
		Logging::do_error("Width too large");
	}

	if ( n/width <= index ) {
		Logging::do_error("Out of Bounds");
	}

	return (unsigned char) ((bits << ( n/width - (index + 1) ) * width) >> ((n/width-1)*width)).to_ulong();
}


/**
 * Given an ordered stream of bits, returns the byte at a given offset.  
 *
 * For Big Endian, this offset starts at most significant set of bits (the left
 * most bit on a bit stream)
 *
 * For example with the following call
 * convert_to_char_big_endia<3,6>( std::string("110100"), 1);
 *
 * index would count starting at the far left (index zero) and land at the 3rd
 * one from the left to point at "100"
 *
 * and would return 4 (in Byte form)
 */
template <size_t width, size_t n>
Byte convert_to_char_big_endian( const std::bitset<n>& bits, size_t index = 0 ) {
	// TODO refactor common code
	if ( n < width ) {
		Logging::do_error("Width too large");
	}

	if ( n/width <= index ) {
		Logging::do_error("Out of Bounds");
	}
	return convert_to_char_little_endian<width>( bits, n / width - index - 1 );
}

/**
 * Given an ordered set of bits, return a set of Bytes to resemble those bits.
 * The size of the bit stream must be evenly divisible into groups of
 * BITS_PER_BYTE. For the big endian version, the first byte in the returned
 * data corresponds to the most significant (leftmost) byte in the given bit stream.
 */
template <size_t n>
BytesContainer convert_big_endian( const std::bitset<BITS_PER_BYTE * n>& bits ) {
	BytesContainer toReturn( Bytes( new Byte[n]), n);

	for( size_t i = 0; i < n; ++i ) {
		toReturn.data()[i] = convert_to_char_big_endian<BITS_PER_BYTE>( bits, i );
	}

	return toReturn;
}

/**
 * Given an ordered set of bits, return a set of Bytes to resemble those bits.
 * The size of the bit stream must be evenly divisible into groups of
 * BITS_PER_BYTE. For the little endian version, the first byte in the returned
 * data corresponds to the least significant (rightmost) byte in the given bit stream.
 */
template <size_t n>
BytesContainer convert_little_endian( const std::bitset<BITS_PER_BYTE * n>& bits ) {
	BytesContainer toReturn( Bytes( new Byte[n]), n);

	for( size_t i = 0; i < n; ++i ) {
		toReturn.data()[i] = convert_to_char_little_endian<BITS_PER_BYTE>( bits, i );
	}

	return toReturn;
}

#endif /* !__byte_convert_h__ */

