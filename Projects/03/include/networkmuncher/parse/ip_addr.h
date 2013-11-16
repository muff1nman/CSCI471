/*
 * ip_addr.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __parse_ip_addr_h__
#define __parse_ip_addr_h__

#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/byte/convert.h"

#include "networkmuncher/domain/ip_addr.h"

#include <string>
#include <sstream>
#include <bitset>

inline IpAddr ip_from_data( const BytesContainer& data ) {
	std::stringstream joined;

	for( size_t i = 0; i < IP_ADDR::BYTE_LENGTH; ++i ) {
		if( ! (i  < data.size()) ) {
			throw "Unexpected end of data while parsing ip";
		}

		joined << (size_t) data.at(i);

		if( i != IP_ADDR::BYTE_LENGTH - 1 ) {
			joined << ".";
		}

	}

	return joined.str();

}

inline IpAddr ip_from_data( const std::bitset<IP_ADDR::BYTE_LENGTH * BITS_PER_BYTE>& data ) {
	return ip_from_data( convert_big_endian<IP_ADDR::BYTE_LENGTH>(data));
}

#endif /* !__ip_h__ */

