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
#include <boost/spirit/include/phoenix.hpp>
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

void print( const std::vector<std::string>& data ) {
#ifdef LOGGING
	if( data.size() == 0 ) {
		LOG(INFO) << "NO DATA";
	}
	for( size_t i = 0; i < data.size(); ++i ) {
		LOG(INFO) << "DATA: " << data.at(i);
	}
#endif
}

void print_s( const std::string& data ) {
#ifdef LOGGING
	LOG(INFO) << "DATA: " << data;
#endif
}

DNS from_data( const BytesContainer raw ) {

	using boost::phoenix::ref;
	using boost::bind;
	DNSBuilder b;

	// data holders
	size_t question_count;
	size_t answer_count;
	size_t ns_count;
	size_t ar_count;

	size_t label_length;

	qi::rule<std::vector<unsigned char>::const_iterator, std::vector<std::string>() > name_parse =
		qi::repeat[
			qi::omit[qi::byte_[ref(label_length) = qi::_1] - qi::byte_(0)] >> 
			qi::repeat(ref(label_length))[qi::char_]
		] >>
		qi::omit[qi::byte_(0)]
		;

	BytesContainer::const_iterator start = raw.begin();
	BytesContainer::const_iterator finish = raw.end() - 4;

	bool parsed_header_correctly = qi::parse( start, finish, 
			qi::big_word[bind(&DNSBuilder::set_id, &b, _1)] >> 
			qi::big_word[bind(&set_fields, &b, _1)] >>
			qi::big_word[ref(question_count) = qi::_1] >>
			qi::big_word[ref(answer_count) = qi::_1] >>
			qi::big_word[ref(ns_count) = qi::_1] >>
			qi::big_word[ref(ar_count) = qi::_1] >>
			//qi::repeat(ref(question_count))[
				name_parse[boost::bind(&print, _1)]
			//]
			);
#ifdef LOGGING
	if ( start == finish ) {
		LOG(INFO) << "Used all bytes";
	} else {
		LOG(WARNING) << "Bytes remaining";
	}
	if (parsed_header_correctly) {
		LOG(INFO) << "Parsed correctly";
	} else {
		LOG(WARNING) << "Parsed incorrectly";
	}
#endif

	return b.build();
}


