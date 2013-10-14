/*
 * dns.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/parse/dns.h"

#include "dnsmuncher/util/logging.h"
#include "dnsmuncher/domain/dns_builder.h"
#include "dnsmuncher/util/byte/copy.h"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_binary.hpp>
#include <boost/bind.hpp>


namespace qi = boost::spirit::qi;

void set_fields( DNSBuilder* builder, unsigned long num ) {
	std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> fields(num);
#ifdef LOGGING
	LOG(INFO) << "fields: " << fields;
#endif
	builder->is_query(fields[DNS::QR_OFFSET]);
	builder->authoritative_bit(fields[DNS::AA_OFFSET]);
	builder->truncated(fields[DNS::TC_OFFSET]);
	builder->recursion_desired(fields[DNS::RD_OFFSET]);
	builder->recursion_available(fields[DNS::RA_OFFSET]);
	builder->op_code( dissect<DNS::GENERIC_HEADER_FIELD_LENGTH,DNS::OPCODE_FIELD_LENGTH>(fields, DNS::OPCODE_OFFSET) );
	builder->zeros( dissect<DNS::GENERIC_HEADER_FIELD_LENGTH,DNS::Z_FIELD_LENGTH>(fields, DNS::Z_OFFSET) );
	builder->return_code( dissect<DNS::GENERIC_HEADER_FIELD_LENGTH,DNS::RCODE_FIELD_LENGTH>(fields, DNS::RCODE_OFFSET) );
}

DNS from_data( const BytesContainer raw ) {
	DNSBuilder b;
	bool parsed_correctly = qi::parse( raw.data(), raw.data() + raw.size(), 
			qi::big_word[boost::bind(&DNSBuilder::set_id, &b, _1)] >> 
			qi::big_word[boost::bind(&set_fields, &b, _1)]
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


