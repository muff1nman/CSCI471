/*
 * print.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __print_h__
#define __print_h__

#include "byte.h"

#include <sstream>
#include <string>
#include <iomanip>

#ifdef LOGGING
#include <glog/logging.h>
#endif

namespace demaria_util {

	inline std::string to_string( const Byte* data, size_t length, size_t group_space, size_t group_newline ) {
		std::stringstream ss;
		ss << '|';
		for( size_t i = 0; i < length; ++i ) {
			if( i % group_newline == 0 && i != 0 ) { 
				ss << "|\n" << i  << " |";
			}
			ss << std::hex << std::setfill('0') << std::setw(2) << (unsigned int) (unsigned char) data[i];
			if( i % group_space == 0 ) {
				ss << " ";
			}
		}
		return ss.str();
	}

	inline std::string to_string( const BytesContainer data, size_t group_space = 1, size_t group_newline = 16 ) {
		return to_string( data.data(), data.size(), group_space, group_newline );
	}

}

#endif /* !__print_h__ */

