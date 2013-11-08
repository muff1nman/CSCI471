/*
 * dns.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "networkmuncher/parse/dns.h"

#include "networkmuncher/util/logging.h"
#include "networkmuncher/domain/dns_builder.h"
#include "networkmuncher/domain/ns_resource_record.h"
#include "networkmuncher/domain/cname_resource_record.h"
#include "networkmuncher/util/byte/copy.h"
#include "networkmuncher/util/join.h"

#ifdef LOGGING
#include "networkmuncher/util/byte/print.h"
#endif

#include <boost/bind.hpp>
#include <boost/optional.hpp>
#include "parse_context.h"
#include <iterator>

void set_fields( DNSBuilder* builder, unsigned long num ) {
	std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> fields(num);
#ifdef LOGGING
	LOG(INFO) << "fields: " << fields.to_string();
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

size_t current_index( ParseContext& context ) {
	return std::distance( context.start, context.current );
}

bool context_has_bytes_left( const ParseContext& context, size_t bytes ) {
#ifdef LOGGING
	LOG(INFO) << std::distance( context.current, context.finish ) << " bytes left";
#endif
	return std::distance(context.current, context.finish) >= (int) bytes;
}

template <class ForwardIterator, class Distance>
ForwardIterator next(ForwardIterator it, Distance d) {
	ForwardIterator i = it;
	std::advance(i, d);
	return i;
}

template <class T, size_t N>
boost::optional<T> parse_number( ParseContext& context ) {
	boost::optional<T> data;
#ifdef LOGGING
	LOG(INFO) << "Parsing number of " << N << " bytes";
#endif

	if( context_has_bytes_left( context, N ) ) {
		std::bitset<N * BITS_PER_BYTE> bytes;
		std::bitset<BITS_PER_BYTE> cache;
		for( size_t i = 0; i < N; ++i ) {
			cache = std::bitset<BITS_PER_BYTE>( *context.current );
			bytes = bytes << BITS_PER_BYTE;
			copy_into(bytes, cache);
			std::advance( context.current, 1);
		}
		data = bytes.to_ulong();
	}

	return data;
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


boost::optional<std::string> parse_string_part( ParseContext& context ) {
	boost::optional<std::string> to_return;
	if( context_has_bytes_left( context, 1 )) {
		size_t length = (size_t) *(context.current++);
#ifdef LOGGING
		LOG(INFO) << "length of next string: " << length;
#endif
		if( length > DNS::MAX_LABEL_SIZE ) {
			return to_return;
		}
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

bool is_pointer( ParseContext& context ) {
	if( !context_has_bytes_left( context, 2 ) ) {
		return false;
	}

	Byte first_byte = *(context.current);
	std::bitset<BITS_PER_BYTE> pointer = std::bitset<BITS_PER_BYTE>( first_byte );
	return pointer.test(BITS_PER_BYTE - 1) && pointer.test(BITS_PER_BYTE - 2);
}


bool parse_zero_byte( ParseContext& context ) {
	if( is_zero_byte( context ) ) {
		std::advance( context.current, 1 );
		return true;
	}
	return false;
}

boost::optional<std::vector<std::string> > parse_labels( ParseContext& context, bool& pointer_next ) {
	boost::optional<std::vector<std::string> > n;
	std::vector<std::string> labels;

#ifdef LOGGING
	LOG(INFO) << "Starting to look for labels at: " << current_index(context);
#endif

	while( (!is_pointer(context)) && (!is_zero_byte(context))) {		

		boost::optional<std::string> label = parse_string_part( context );
		if( label ) {
			labels.push_back(*label);
		} else {
			break;
		}
	}

	bool parsed_zero = parse_zero_byte(context);
	if( parsed_zero ) {
		n = labels;
	} else {
		pointer_next = is_pointer(context);
		if( pointer_next ) {
			n = labels;
		} else {
#ifdef LOGGING
			LOG(WARNING) << "Could not parse zero byte or a pointer";
#endif
		}
	}
	return n;

}
boost::optional<std::vector<std::string> > parse_label_pointer( ParseContext& context );

boost::optional<std::vector<std::string> > parse_name_recursive( ParseContext& context ) {
	boost::optional<std::vector<std::string> > maybe_pointer_labels;
	boost::optional<std::vector<std::string> > maybe_labels;
	bool should_parse_pointer = false;
	maybe_labels = parse_labels( context, should_parse_pointer );
#ifdef LOGGING
	if( maybe_labels ) {
		LOG(INFO) << "Labels found";
	} else { 
		LOG(INFO) << "Labels not found";
	}
	LOG(INFO) << "Index at: " << current_index( context );
#endif

	if( should_parse_pointer ) {
		maybe_pointer_labels = parse_label_pointer( context );
#ifdef LOGGING
		if( maybe_pointer_labels ) {
			LOG(INFO) << "Pointer Labels found";
		} else { 
			LOG(INFO) << "Pointer Labels not found";
		}
#endif
	}

	boost::optional<std::vector<std::string> > combined = maybe_join( maybe_labels, maybe_pointer_labels );
	return combined;
}

boost::optional<std::vector<std::string> > parse_label_pointer( ParseContext& context ) {
#ifdef LOGGING
	LOG(INFO) << "Starting pare of label pointer at: " << current_index( context);
#endif
	if( is_pointer(context) ) {
		boost::optional<size_t> bytes = parse_number<size_t,DNS::POINTER_LENGTH / BITS_PER_BYTE>( context );
		if( bytes ) {
#ifdef LOGGING
			LOG(INFO) << "Consumed ptr, now at: " << current_index(context);
#endif
			std::bitset<DNS::POINTER_LENGTH> pointer = std::bitset<DNS::POINTER_LENGTH>(*bytes);
			pointer.set(DNS::POINTER_LENGTH - 1, 0);
			pointer.set(DNS::POINTER_LENGTH - 2, 0);
			size_t index = pointer.to_ulong();
			ParseContext temporary(context, index);
			return parse_name_recursive( temporary );
		}
	}
	return boost::optional<std::vector<std::string> >();
}

boost::optional<Name> parse_name( ParseContext& context ) {
	boost::optional<Name> n;
	boost::optional<std::vector<std::string> > name_parts = parse_name_recursive( context );
	if( name_parts ) {
		n = Name(*name_parts);
	}
	return n;
}

boost::optional<BytesContainer> parse_data( ParseContext& context, size_t length ) {
#ifdef LOGGING
	LOG(INFO) << "#parse_data called with length " << length;
#endif
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

DNS::ResourcePtr create_specific_resource( const DNS::ResourcePtr& resource, ParseContext& context ) {
	switch( resource->get_type()) {
		case Type::NS: 
		case Type::SOA: {
#ifdef LOGGING
											LOG(INFO) << "Parsing name for NS";
#endif
											boost::optional<Name> name = parse_name(context);
											if( name ) {
#ifdef LOGGING
												LOG(INFO) << "Successfully parsed name for NS record: " << name->to_string();
#endif
												return DNS::ResourcePtr( new NsResourceRecord(*resource, *name));
											} else {
#ifdef LOGGING
												LOG(WARNING) << "Could not parse name in rdata for Type: " << Type::NS;
#endif
												return resource;
											}
											break;
										}
		case Type::CNAME: {
												boost::optional<Name> name = parse_name(context);
												if( name ) {
													return DNS::ResourcePtr( new CNameResourceRecord(*resource, *name));
												} else {
#ifdef LOGGING
													LOG(WARNING) << "Could not parse name in rdata for Type: " << Type::CNAME;
#endif
													return resource;
												}
												break;

											}
		default:		{
									return resource;
								}
	}
	return resource;  // compiler gives warning without this
}

boost::optional<DNS::ResourcePtr> parse_other_record( ParseContext& context ) {
#ifdef LOGGING
	LOG(INFO) << "Starting to parse resource record at: " << current_index( context );
#endif
	boost::optional<DNS::ResourcePtr> r;
	boost::optional<Name> name = parse_name( context );
#ifdef LOGGING
	LOG(INFO) << "Finished parsing name and now we are at: " << current_index( context );
#endif
	boost::optional<size_t> type = parse_number<size_t, 2>( context );
	// Check type
	if( type && (*type != (size_t)Type::A && *type != (size_t)Type::NS && *type != (size_t)Type::CNAME)) {
#ifdef LOGGING
		LOG(WARNING) << "Parsing unsupported type [" << *type << "], the information in this record may not be printed accurately";
#endif
	}
#ifdef LOGGING
	LOG(INFO) << "Finished parsing type and now we are at: " << current_index( context );
#endif
	boost::optional<size_t> qclass = parse_number<size_t, 2>( context );
#ifdef LOGGING
	LOG(INFO) << "Finished parsing qclass and now we are at: " << current_index( context );
#endif
	boost::optional<ttl_number> ttl = parse_number<ttl_number, 4>( context );
#ifdef LOGGING
	LOG(INFO) << "Finished parsing ttl and now we are at: " << current_index( context );
#endif
	boost::optional<rdata_length_number> rdlength = parse_number<rdata_length_number, 2>( context );
#ifdef LOGGING
	LOG(INFO) << "Finished parsing rdlength and now we are at: " << current_index( context );
#endif
	ParseContext duplicate_before_rdata_parse(context, current_index(context));
	boost::optional<BytesContainer> rdata;
if( rdlength ) {
		rdata	= parse_data( context, *rdlength );
#ifdef LOGGING
		if(rdata) {
			LOG(INFO) << "Resource record has data: " << demaria_util::to_string( *rdata );
		}
#endif
	}
#ifdef LOGGING
	else {
		LOG(WARNING) << "Could not parse data";
	}
#endif

	if( 
			name &&
			type &&
			qclass &&
			ttl &&
			rdlength &&
		 	rdata 
			) {
		r = DNS::ResourcePtr( new ResourceRecord( *name, *rdata, *type, *qclass, *ttl, *rdlength ));
#ifdef LOGGING
		LOG(INFO) << "Parse record: " << (*r)->to_string();
#endif
		r = create_specific_resource(*r, duplicate_before_rdata_parse);
	}
#ifdef LOGGING
	else {
		LOG(WARNING) << "Could not parse record";
	}

	if( duplicate_before_rdata_parse.current > context.current ) {
		LOG(WARNING) << "Parsing contexts do not match after parsing specific type rdata";
		LOG(INFO) << "Duplicate at: " << current_index(duplicate_before_rdata_parse) << " and context at: " << current_index( context );
	} else if ( duplicate_before_rdata_parse.current != context.current ) {
		LOG(INFO) << "Duplicate at: " << current_index(duplicate_before_rdata_parse) << " and context at: " << current_index( context );
	}
#endif

	return r;
}

boost::optional<DNS::QuestionPtr> parse_question( ParseContext& context ) {
	boost::optional<DNS::QuestionPtr> q;
	boost::optional<Name> name = parse_name( context );
	boost::optional<size_t> type = parse_number<size_t, 2>( context );
	boost::optional<size_t> qclass = parse_number<size_t, 2>( context );

	if( name && type && qclass ) {
		q = DNS::QuestionPtr( new Question(*name, *type, *qclass));
#ifdef LOGGING
		LOG(INFO) << "Parsed question " << (*q)->to_string();
#endif
	} 
#ifdef LOGGING
	else {
		LOG(WARNING) << "Could not parse question because name: " << (bool) name << " type: " << (bool) type << " or qclass: " << (bool) qclass;
	}
#endif

	return q;
}

bool parse_header( ParseContext& context, size_t& question_count, size_t& answer_count, size_t& ns_count, size_t& ar_count) {

	// TODO check dereferences on optionals
	typedef boost::optional<size_t>	maybe_num;

	maybe_num id = parse_number<size_t,2>( context );
	maybe_num fields = parse_number<size_t,2>( context );
	maybe_num q_count = parse_number<size_t,2>( context );
	maybe_num an_count = parse_number<size_t,2>( context );
	maybe_num nss_count = parse_number<size_t,2>( context );
	maybe_num arr_count = parse_number<size_t,2>( context );

	if(
			id &&
			fields &&
			q_count &&
			an_count &&
			nss_count &&
			arr_count ) {

		context.b->set_id( *id);
		set_fields( context.b.get(), *fields);
		question_count = *q_count;
		answer_count = *an_count;
		// TODO change rhs names
		ns_count = *nss_count;
		ar_count = *arr_count;
#ifdef LOGGING
		LOG(INFO) << context.finish - context.current << " bytes remaining after header";
		LOG(INFO) << "Current build: " << context.b->to_string();
#endif
		return true;

	}  else {

#ifdef LOGGING
		LOG(WARNING) << "Could not parse header";
#endif
		return false;
	}

}

bool from_data_interntal( const BytesContainer raw, boost::shared_ptr<DNSBuilder> b ) {
	// data holders
	size_t question_count;
	size_t answer_count;
	size_t ns_count;
	size_t ar_count;

#ifdef LOGGING
	LOG(INFO) << "Bytes" << std::endl << demaria_util::to_string( raw );
#endif

	BytesContainer::const_iterator start = raw.begin();
	BytesContainer::const_iterator finish = raw.end();

	ParseContext context(raw, raw.begin(), raw.end(), raw.begin(), b);
#ifdef LOGGING
	LOG(INFO) << "Context at: " << current_index(context);
	LOG(INFO) << "Bytes remaining?" << context_has_bytes_left(context, 3);
#endif

	bool good_header = parse_header( context, question_count, answer_count, ns_count, ar_count );
	if( !good_header ) {
		return false;
	}
#ifdef LOGGING
	LOG(INFO) << "Context at: " << current_index(context);
#endif

	b->question_count( question_count );
	b->answer_count( answer_count );
	b->nameserver_count( ns_count );
	b->additional_count( ar_count );

	for( size_t i = 0; i < question_count; ++i ) {
#ifdef LOGGING
		if( i > 0 ) {
			LOG(WARNING) << "Multiple questions have very little support in the real world and are not guaranteed to work";
		}
		LOG(INFO) << "Attempt to parse question " << i << " out of " << question_count;
#endif

		boost::optional<DNS::QuestionPtr> q = parse_question(context);
		if ( q ) {
			b->add_question( *q );
		} else {	
			return false;
		} 
	}

	for( size_t i = 0; i < answer_count + ns_count + ar_count; ++i ) {
#ifdef LOGGING
		LOG(INFO) << "Attempt to parse record " << i << " out of " << answer_count;
#endif
		boost::optional<DNS::ResourcePtr> r = parse_other_record(context);
		if ( r ) {
			b->add_resource( *r );
		} else {
			return false;
		}
	}
	return true;
}

boost::optional<DNS> from_data( const BytesContainer raw ) {

	boost::shared_ptr<DNSBuilder> b( new DNSBuilder() );
	boost::optional<DNS> to_return;

	bool valid = from_data_interntal( raw, b );
	if( valid ) { 
		to_return = b->build();
	}

	return to_return;
}

DnsMaybePtr from_data_as_ptr( const BytesContainer raw ) {

	boost::shared_ptr<DNSBuilder> b( new DNSBuilder() );
	DnsMaybePtr to_return;

	bool valid = from_data_interntal( raw, b );
	if( valid ) { 
		to_return = b->build_ptr();
	}

	return to_return;

}


