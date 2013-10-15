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
#include <boost/optional.hpp>
#include "parse_context.h"

using boost::phoenix::ref;
using boost::bind;

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

boost::optional<ResourceRecord> parse_other_record( ParseContext& context ) {
	boost::optional<ResourceRecord> r;
	// TODO
	return r;
}

boost::optional<Question> parse_question( ParseContext& context ) {
	boost::optional<Question> q;
	// TODO	
	return q;
}

bool parse_header( ParseContext& context, size_t& question_count, size_t& answer_count, size_t& ns_count, size_t& ar_count) {

	DNSBuilder g;

	bool parsed_header_correctly = qi::parse( context.current, context.finish, 
			qi::big_word[bind(&DNSBuilder::set_id, context.b.get(), _1)] >> 
			qi::big_word[bind(&set_fields, context.b.get(), _1)] >>
			qi::big_word[ref(question_count) = qi::_1] >>
			qi::big_word[ref(answer_count) = qi::_1] >>
			qi::big_word[ref(ns_count) = qi::_1] >>
			qi::big_word[ref(ar_count) = qi::_1]
			//qi::repeat(ref(question_count))[
			//(
				//name_parse[boost::bind(&print, _1)] >>
				//qi::big_word >>
				//qi::big_word)[&multiple]
			//]
			);
#ifdef LOGGING
	if ( context.current == context.finish ) {
		LOG(INFO) << "Used all header bytes";
	} else {
		LOG(WARNING) << context.finish - context.current << " bytes in header remaining";
	}
#endif

	if (parsed_header_correctly) {
#ifdef LOGGING
		LOG(INFO) << "Parsed correctly";
#endif
		return true;
	} else {
#ifdef LOGGING
		LOG(WARNING) << "Parsed incorrectly";
#endif
		return false;
	}

}

qi::rule< BytesContainer::const_iterator, std::vector<std::string>() > create_name_parser( size_t& label_length ) {
		return qi::repeat[
			qi::omit[qi::byte_[ref(label_length) = qi::_1] - qi::byte_(0)] >> 
			qi::repeat(ref(label_length))[qi::char_]
		] >>
		qi::omit[qi::byte_(0)]
		;
}

DNS from_data( const BytesContainer raw ) {

	const size_t HEADER_SIZE_IN_BYTES = 16;

	boost::shared_ptr<DNSBuilder> b( new DNSBuilder() );

	// data holders
	size_t question_count;
	size_t answer_count;
	size_t ns_count;
	size_t ar_count;

	BytesContainer::const_iterator start = raw.begin();
	BytesContainer::const_iterator finish = raw.end();
	ParseContext context(raw, raw.begin(), raw.end(), raw.begin(), b);

	parse_header( context, question_count, answer_count, ns_count, ar_count );

	b->question_count( question_count );
	b->answer_count( answer_count );
	b->nameserver_count( ns_count );
	b->additional_count( ar_count );

	for( size_t i = 0; i < question_count; ++i ) {
		boost::optional<Question> q; // = parse_question();
		if ( !q ) {
			//Logging::do_error( "Could not parse questions correctly" );
		} 

		// TODO do something with q
	}

	for( size_t i = 0; i < answer_count + ns_count + ar_count; ++i ) {
		boost::optional<ResourceRecord> r;// = parse_other_record();
		if ( !r ) {
			//Logging::do_error( "Could not parse other records correctly" );
		}

		// TODO do something with r
	}

	return b->build();
}


