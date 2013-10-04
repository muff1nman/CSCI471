/*
 * byte_print.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __byte_print_h__
#define __byte_print_h__

#include "byte.h"

#include <sstream>
#include <string>
#include <iomanip>

#ifdef LOGGING
#include <glog/logging.h>
#endif

namespace demaria_util {

std::string to_string( const char* data, size_t length, size_t group_space, size_t group_newline ) {
	std::stringstream ss;
	ss << '|';
	for( size_t i = 0; i < length; ++i ) {
		if( i % group_newline == 0 && i != 0 ) { 
			ss << '|' << '\n' << '|';
		}
		ss << std::hex << std::setfill('0') << std::setw(2) << (short) data[i];
		ss << " ";
	}
	return ss.str();
}

}

#endif /* !__byte_print_h__ */

