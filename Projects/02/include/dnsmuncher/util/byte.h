/*
 * byte.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __byte_h__
#define __byte_h__

#include <boost/shared_ptr.hpp>
#include <bitset>
#include <string>

#include "dnsmuncher/util/logging.h"

typedef unsigned char Byte;
typedef boost::shared_ptr<Byte> Bytes;

class BytesContainer {
	public:
		size_t size;
		Bytes data;
};

//http://stackoverflow.com/questions/3061721/concatenate-boostdynamic-bitset-or-stdbitset
template <size_t N1, size_t N2 >
std::bitset<N1 + N2> concat( const std::bitset<N1> & b1, const std::bitset<N2> & b2 ) {
    std::string s1 = b1.to_string();
    std::string s2 = b2.to_string();
	return std::bitset <N1 + N2>( s1 + s2 );
}

template <size_t n>
BytesContainer convert_big_endian( const std::bitset<8 * n>& bits ) {
	BytesContainer toReturn;
	toReturn.data = Bytes( new Byte[n] );
	toReturn.size = n;

	for( size_t i = 0; i < n; ++i ) {
		toReturn.data.get()[i] = convert_to_char_big_endian( bits, i );
	}

	return toReturn;
}

template <size_t n>
BytesContainer convert_little_endian( const std::bitset<8 * n>& bits ) {
	BytesContainer toReturn;
	toReturn.data = Bytes( new Byte[n] );
	toReturn.size = n;

	for( size_t i = 0; i < n; ++i ) {
		toReturn.data.get()[i] = convert_to_char_little_endian( bits, i );
	}

	return toReturn;
}

template <size_t width, size_t n>
BytesContainer convert_to_char_big_endian( const std::bitset<8 * n>& bits, size_t index = 0 ) {
	// TODO refactor common code
	if ( n < width ) {
		Logging::do_error("Width too large");
	}

	if ( n/width <= index ) {
		Logging::do_error("Out of Bounds");
	}
	//  TODO
	//return convert_to_char_little_endian<w>( bits, n / width - index );
}

/**
 * For example with the following call
 * convert_to_char_little_endian<3,6>( std::string("110100"), 1 );
 *
 * index would count starting at the far right (index zero) and land at the 3rd
 * zero from the right to point at  "110"
 *
 * and 6 would be returned (in char form)
 *
 */
template <size_t width, size_t n>
unsigned char convert_to_char_little_endian( const std::bitset<n>& bits, size_t index = 0 ) {

	if ( n < width ) {
		Logging::do_error("Width too large");
	}

	if ( n/width <= index ) {
		Logging::do_error("Out of Bounds");
	}

	return (unsigned char) ((bits << ( n/width - (index + 1) ) * width) >> ((n/width-1)*width)).to_ulong();
}


#endif /* !__byte_h__ */

