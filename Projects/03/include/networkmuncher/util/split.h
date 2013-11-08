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

#endif /* !__split_h__ */

