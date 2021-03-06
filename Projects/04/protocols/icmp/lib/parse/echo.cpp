/*
 * echo.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "icmp/parse/echo.h"
#include "icmp/domain/domain.h"
#include "echo_parse_context.h"
#include "networkmuncher/util/byte/parse_extra.h"
#include "networkmuncher/util/logging.h"

bool from_data_internal( EchoParseContext& context ) {

	boost::optional<Echo::Type> type = parse_bitset<Echo::TYPE_LENGTH / BITS_PER_BYTE>(context);
	if(type) {
		context.b->set_type(*type);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse type";
#endif
		return false;
	}

	boost::optional<Echo::Code> code = parse_bitset<Echo::CODE_LENGTH / BITS_PER_BYTE>(context);
	if(code) {
		context.b->set_code(*code);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse code";
#endif
		return false;
	}

	boost::optional<Echo::Checksum> checksum = parse_bitset<Echo::CHECKSUM_LENGTH / BITS_PER_BYTE>(context);
	if(checksum) {
		context.b->set_checksum(*checksum);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse checksum";
#endif
		return false;
	}

	boost::optional<Echo::Identifier> ident = parse_bitset<Echo::IDENTIFIER_LENGTH / BITS_PER_BYTE>(context);
	if(ident) {
		context.b->set_identifier(*ident);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse identifier";
#endif
		return false;
	}

	boost::optional<Echo::SequenceNum> seq_num = parse_bitset<Echo::SEQUENCE_NUM_LENGTH / BITS_PER_BYTE>(context);
	if(seq_num) {
		context.b->set_sequence_num(*seq_num);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse sequence number";
#endif
		return false;
	}

	BytesContainer data = parse_remaining_data(context);

	context.b->set_data(data);

	return true;
}

EchoMaybe ECHO::from_data( ParseContext& parse_context ) {
	boost::shared_ptr<EchoBuilder> b( new EchoBuilder() );
	EchoMaybe to_return;
	EchoParseContext context( parse_context, b );

	bool valid = from_data_internal( context );
	if( valid ) {
		to_return = b->build();
	}

	return to_return;
}

EchoMaybe ECHO::from_data( const BytesContainer& bytes ) {
	ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
	return ECHO::from_data(parse_context);
}

TransportLayerProtocolMaybePtr ECHO::from_data_as_ptr( ParseContext& parse_context ) {
	boost::shared_ptr<EchoBuilder> b( new EchoBuilder() );
	TransportLayerProtocolMaybePtr to_return;
	EchoParseContext context( parse_context, b );

	bool valid = from_data_internal( context );
	if( valid ) {
		to_return = boost::dynamic_pointer_cast<TransportLayerProtocol>(b->build_ptr());
	}

	return to_return;
}

TransportLayerProtocolMaybePtr ECHO::from_data_as_ptr( const BytesContainer& bytes ) {
	ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
	return ECHO::from_data_as_ptr(parse_context);
}
