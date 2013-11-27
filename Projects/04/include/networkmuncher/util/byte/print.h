/*
 * print.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __print_h__
#define __print_h__

#include "byte.h"
#include "parse_context.h"

#include <sstream>
#include <string>
#include <iomanip>

#ifdef LOGGING
#include <glog/logging.h>
#endif

namespace demaria_util {

	const size_t GROUP_SPACE_DEFAULT = 1;
	const size_t GROUP_NEWLINE_DEFAULT = 16;
	const size_t PADDING_FRONT_DEFAULT = 0;

	inline std::string to_string( const Byte* data, size_t length, size_t group_space = GROUP_SPACE_DEFAULT, size_t group_newline = GROUP_NEWLINE_DEFAULT, size_t padding_front = PADDING_FRONT_DEFAULT ) {
		std::stringstream ss;
		for( size_t i = 0; i < length; ++i ) {
			if( i % group_newline == 0 ) { 
				if( i == 0 ) {
					ss << " ";
				} else {
					ss << "|\n";
				}
				ss << std::string(padding_front, ' ') <<  i  << " |";
			}
			ss << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) (unsigned char) data[i];
			if( i % group_space == 0 ) {
				ss << " ";
			}
		}
		return ss.str();
	}

	inline std::string to_string( const BytesContainer data, size_t group_space = GROUP_SPACE_DEFAULT, size_t group_newline = GROUP_NEWLINE_DEFAULT, size_t padding_front = PADDING_FRONT_DEFAULT) {
		return to_string( data.data(), data.size(), group_space, group_newline, padding_front );
	}

	inline std::string to_string( const ParseContext parse, size_t group_space = GROUP_SPACE_DEFAULT, size_t group_newline = GROUP_NEWLINE_DEFAULT, size_t padding_front = PADDING_FRONT_DEFAULT ) {
		return to_string( parse.raw_data.data() + std::distance( parse.start, parse.current ), std::distance( parse.current, parse.finish ), group_space, group_newline, padding_front );
	}

}

#endif /* !__print_h__ */

