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

}

template <size_t n>
BytesContainer convert_little_endian( const std::bitset<8 * n>& bits ) {

}


#endif /* !__byte_h__ */

