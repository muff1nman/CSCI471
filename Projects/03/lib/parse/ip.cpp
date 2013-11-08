/*
 * ip.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "networkmuncher/parse/ip.h"
#include <sstream>

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



