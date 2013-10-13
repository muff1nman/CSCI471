/*
 * dns.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/parse/dns.h"

#include "dnsmuncher/util/logging.h"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_binary.hpp>

namespace qi = boost::spirit::qi;

DNS from_data( const BytesContainer raw ) {
	bool parsed_correctly = qi::parse( raw.data.get(), raw.data.get() + raw.size, 
			qi::word
			);
#ifdef LOGGING
	if (parsed_correctly) {
		LOG(INFO) << "Parsed correctly";
	} else {
		LOG(WARNING) << "Parsed incorrectly";
	}
#endif

	return DNS();
}


