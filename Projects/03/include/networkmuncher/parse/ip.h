/*
 * ip.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __ip_h__
#define __ip_h__

#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/byte/convert.h"

#include <string>
#include <sstream>
#include <bitset>

const size_t BYTE_LENGTH = 4;

std::string ip_from_data( const BytesContainer& data ) {
	std::stringstream joined;

	for( size_t i = 0; i < BYTE_LENGTH; ++i ) {
		if( ! (i  < data.size()) ) {
			throw "Unexpected end of data while parsing ip";
		}

		joined << (size_t) data.at(i);

		if( i != BYTE_LENGTH - 1 ) {
			joined << ".";
		}

	}

	return joined.str();

}

std::string ip_from_data( const std::bitset<BYTE_LENGTH * BITS_PER_BYTE>& data ) {
	return ip_from_data( convert_big_endian<BYTE_LENGTH>(data));
}

#endif /* !__ip_h__ */

