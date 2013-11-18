/*
 * split.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __split_h__
#define __split_h__

#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include "networkmuncher/util/logging.h"
#include <algorithm>
#include <boost/lexical_cast.hpp>

/**
 * Split a given string on the delimiter. If a delimiter is found on the end of
 * the string, drop it instead of adding an empty string to the list.  This may
 * not be the case for a delimiter found at the beginning of the string. In
 * addition, delimiters cannot be adjacent. On error return an empty list.
 */
inline std::vector<std::string> split_name( std::string name, std::string delimiter = "." ) {
#ifdef LOGGING
	LOG(INFO) << "Spliting: " << name;
#endif
	if( name.empty() ) {
		Logging::do_error("You gave me an empty domain name");
		return std::vector<std::string>();
	}
	
	if( name.substr( name.size() - delimiter.size() ) == delimiter) {
		name.erase( name.end() - delimiter.size(), name.end() );
	}

	if( name.empty() ) { // search for implicit root domain
#ifdef LOGGING
		LOG(WARNING) << "Are you sure you want labels to be empty?";
#endif
		return std::vector<std::string>();
	}

	std::vector<std::string> cut_up;
	boost::split(cut_up, name, boost::is_any_of(delimiter));

	if( std::find(cut_up.begin(), cut_up.end(), std::string("")) != cut_up.end() ) {
		Logging::do_error("I will not accept duplicate periods");
		return std::vector<std::string>();
	}

	return cut_up;
}

inline std::vector<std::string> split_name( const char* c_str ) {
	return split_name( std::string(c_str) );
}

/**
 * A specialization of split_name designed for spliting groups of numerics.  If
 * conversion fails, return an empty list
 */
template <class Numeric>
inline std::vector<Numeric> split_numerics( std::string str, std::string delimiter ) {
	std::vector<std::string> raw_numbers = split_name(str, delimiter);
	std::vector<Numeric> numbers;

	for(size_t i = 0; i < raw_numbers.size(); ++i ) {
		std::string raw_number = raw_numbers.at(i);
		// TODO try catch here?
		Numeric number = boost::lexical_cast<Numeric>(raw_number);
		numbers.push_back(number);
	}

	return numbers;
}

#endif /* !__split_h__ */

