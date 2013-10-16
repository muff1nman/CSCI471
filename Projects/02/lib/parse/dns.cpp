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
#include <iterator>

using boost::phoenix::ref;
using boost::bind;

namespace qi = boost::spirit::qi;

void set_fields( DNSBuilder* builder, unsigned long num ) {
	std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> fields(num);
#ifdef LOGGING
	LOG(INFO) << "fields: " << fields;
#endif
	builder->is_response(fields[DNS::QR_OFFSET]);
	builder->authoritative_bit(fields[DNS::AA_OFFSET]);
	builder->truncated(fields[DNS::TC_OFFSET]);
	builder->recursion_desired(fields[DNS::RD_OFFSET]);
	builder->recursion_available(fields[DNS::RA_OFFSET]);
	builder->op_code( dissect<DNS::GENERIC_HEADER_FIELD_LENGTH,DNS::OPCODE_FIELD_LENGTH>(fields, DNS::OPCODE_OFFSET) );
	builder->zeros( dissect<DNS::GENERIC_HEADER_FIELD_LENGTH,DNS::Z_FIELD_LENGTH>(fields, DNS::Z_OFFSET) );
	builder->return_code( dissect<DNS::GENERIC_HEADER_FIELD_LENGTH,DNS::RCODE_FIELD_LENGTH>(fields, DNS::RCODE_OFFSET) );
}

void create_name( /*Name* const name,*/ std::vector<std::string > labels ) {
#ifdef LOGGING
	LOG(INFO) << "Creating name!";
#endif
	//*name = Name(labels);
}

void dummy ( ) {
#ifdef LOGGING
	LOG(INFO) << "dummy!";
#endif

}

qi::rule< BytesContainer::const_iterator, std::string() > string_parse(const size_t& label_length) {
	return qi::repeat(ref(label_length))[qi::char_];
}

qi::rule< BytesContainer::const_iterator > create_name_parser( Name& name, size_t& label_length ) {
		qi::rule< BytesContainer::const_iterator > r = 
			(qi::repeat[
			(qi::omit[qi::byte_[ref(label_length) = qi::_1] - qi::byte_(0)] >> 
			string_parse( label_length ))[bind(&dummy)]
		] >>
		qi::omit[qi::byte_(0)])// [bind(&dummy/*, &name*/)]
		;

		return r;
}

void loop_over_and_print( BytesContainer::const_iterator start, BytesContainer::const_iterator end ) {
#ifdef LOGGING
	LOG(INFO) << "Starting print process";
#endif
	for(;start != end; ++start ) {
#ifdef LOGGING
		LOG(INFO) << "Byte: " << *start;
#endif
	}
#ifdef LOGGING
	LOG(INFO) << "Ending print process";
#endif
}

bool context_has_bytes_left( const ParseContext& context, size_t bytes ) {
	return context.finish - context.start >= bytes;
}

boost::optional<std::string> parse_string_part( ParseContext& context ) {
	boost::optional<std::string> to_return;
	if( context_has_bytes_left( context, 1 )) {
		size_t length = (size_t) *(context.current++);
#ifdef LOGGING
		LOG(INFO) << "length of next string: " << length;
#endif
		if( context_has_bytes_left( context, length )) {
			BytesContainer::const_iterator end_of_string = context.current;
			std::advance( end_of_string, length);
			to_return = std::string(context.current, end_of_string);
#ifdef LOGGING
			LOG(INFO) << "Created string: " << *to_return;
#endif
			context.current = end_of_string;
		}
#ifdef LOGGING
		else {
			LOG(WARNING) << "Not enough bytes to parse next piece of label";
		}
#endif
	}
#ifdef LOGGING
	else {
		LOG(WARNING) << "Not enough bytes left to parse next label length";
	}
#endif

	return to_return;
}

bool is_zero_byte( ParseContext& context ) {
	return context_has_bytes_left( context, 1 )  && *(context.current) == (Byte) 0;
}

boost::optional<Name> parse_name( ParseContext& context ) {
	boost::optional<Name> n;

	std::vector<std::string> labels;

	while(!is_zero_byte(context)) {
		boost::optional<std::string> label = parse_string_part( context );
		if( label ) {
			labels.push_back(*label);
		} else {
			break;
		}
	}

	// consume zero length root 
	if( context_has_bytes_left( context, 1 ) ) {
		std::advance( context.current, 1 );
		n = Name(labels);
	}

	return n;

}

template <class ForwardIterator, class Distance>
ForwardIterator next(ForwardIterator it, Distance d) {
	ForwardIterator i = it;
	std::advance(it, d);
	return i;
}

template <class T, size_t N>
qi::rule< BytesContainer::const_iterator, T> number_parser( T& buffer ) {
	switch(N) {
		case 4:
			return qi::big_dword[ref(buffer) = qi::_1];
		case 2:
			return qi::big_word[ref(buffer) = qi::_1];
		case 1:
		default:
			return qi::byte_[ref(buffer) = qi::_1];
	}
}


template <class T, size_t N>
boost::optional<T> parse_number( ParseContext& context ) {
	boost::optional<T> data;
	T buffer;

	if( context_has_bytes_left( context, 2*N ) ) {
#ifdef LOGGING
		LOG(INFO) << "Parsing type at: " << std::distance(context.start, context.current);
		LOG(INFO) << "Byte 0: " << *(context.current);
		BytesContainer::const_iterator copy = context.current;
		std::advance(copy, 1);
		LOG(INFO) << "Byte 1: " << *copy;
#endif
		bool parsed_correctly = qi::parse( context.current, context.finish, 
				number_parser<T,N>(buffer));
		if( parsed_correctly ) {
			data = buffer;
		}
	}

	return data;
}

boost::optional<BytesContainer> parse_data( ParseContext& context, size_t length ) {
	boost::optional<BytesContainer> c;
	if( context_has_bytes_left( context, length ) ) {
		BytesContainer::const_iterator end_of_rdata = next(context.current,length);
		c = BytesContainer(context.current, end_of_rdata);
		context.current = end_of_rdata;
	} 
#ifdef LOGGING
	else {
		LOG(WARNING) << "Not enough bytes left";
	}
#endif

	return c;

}

boost::optional<ResourceRecord> parse_other_record( ParseContext& context ) {
	boost::optional<ResourceRecord> r;
	boost::optional<Name> name = parse_name( context );
	boost::optional<size_t> type = parse_number<size_t, 2>( context );
	boost::optional<size_t> qclass = parse_number<size_t, 2>( context );
	boost::optional<ttl_number> ttl = parse_number<ttl_number, 4>( context );
	boost::optional<rdata_length_number> rdlength = parse_number<rdata_length_number, 2>( context );
	boost::optional<BytesContainer> rdata;
	if( rdlength ) {
		rdata	= parse_data( context, *rdlength );
	}

	if( 
			name &&
			type &&
			qclass &&
			ttl &&
			rdlength &&
			rdata ) {
		r = ResourceRecord( *name, *rdata, *type, *qclass, *ttl, *rdlength );
#ifdef LOGGING
		LOG(INFO) << "Parse record: " << r->to_string();
#endif
	}
#ifdef LOGGING
	else {
		LOG(WARNING) << "Could not parse record";
	}
#endif

	return r;
}

boost::optional<Question> parse_question( ParseContext& context ) {
	boost::optional<Question> q;
	boost::optional<Name> name = parse_name( context );
	boost::optional<size_t> type = parse_number<size_t, 2>( context );
	boost::optional<size_t> qclass = parse_number<size_t, 2>( context );

	if( name && type && qclass ) {
		q = Question(*name, *type, *qclass);
#ifdef LOGGING
		LOG(INFO) << "Parsed question " << q->to_string();
#endif
	} 
#ifdef LOGGING
	else {
		LOG(WARNING) << "Could not parse question";
	}
#endif

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
			);
#ifdef LOGGING
	LOG(INFO) << context.finish - context.current << " bytes remaining after header";
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
#ifdef LOGGING
		if( i > 0 ) {
			LOG(WARNING) << "Multiple questions have very little support in the real world and are not guaranteed to work";
		}
#endif

		boost::optional<Question> q = parse_question(context);
		if ( q ) {
			b->add_question( *q );
		} else {	
			Logging::do_error( "Could not parse questions correctly" );
		} 
	}

	for( size_t i = 0; i < answer_count + ns_count + ar_count; ++i ) {
		boost::optional<ResourceRecord> r = parse_other_record(context);
		if ( r ) {
			b->add_resource( *r );
		} else {
			Logging::do_error( "Could not parse other records correctly" );
		}
	}

	return b->build();
}


