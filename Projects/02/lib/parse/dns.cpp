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
#include <boost/bind.hpp>

#include "dns_builder.h"

namespace qi = boost::spirit::qi;

DNS from_data( const BytesContainer raw ) {
	DNSBuilder b;
	b.set_id(4);
	bool parsed_correctly = qi::parse( raw.data.get(), raw.data.get() + raw.size, 
			qi::big_word[boost::bind(&DNSBuilder::set_id, &b, _1)]
			);
#ifdef LOGGING
	if (parsed_correctly) {
		LOG(INFO) << "Parsed correctly";
	} else {
		LOG(WARNING) << "Parsed incorrectly";
	}
#endif

	return b.build();
}


