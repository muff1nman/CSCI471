/*
 * udp.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "udp/domain/domain.h"
#include "udp/parse/udp.h"
#include "networkmuncher/util/logging.h"
#include "udp_parse_context.h"
#include "networkmuncher/util/byte/parse_extra.h"

bool parse_internal( UdpParseContext& context ) {
	boost::optional<Udp::Port> dest = parse_bitset<Udp::PORT_LENGTH / BITS_PER_BYTE>(context);
	if(dest) {
		context.b->set_dest(*dest);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse dest";
#endif
		return false;
	}

	boost::optional<Udp::Port> src = parse_bitset<Udp::PORT_LENGTH / BITS_PER_BYTE>(context);
	if(src) {
		context.b->set_src(*src);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse src";
#endif
		return false;
	}

	boost::optional<Udp::Length> length = parse_bitset<Udp::LENGTH_LENGTH / BITS_PER_BYTE>(context);
	if(length) {
		context.b->set_length(*length);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse length";
#endif
		return false;
	}

	boost::optional<Udp::Checksum> checksum = parse_bitset<Udp::CHECKSUM_LENGTH / BITS_PER_BYTE>(context);
	if(checksum) {
		context.b->set_checksum(*checksum);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse checksum";
#endif
		return false;
	}
	return true;
}

namespace UDP {

	UdpMaybe from_data( ParseContext& parse_context ) {
		UdpMaybe to_return;
		boost::shared_ptr<UdpBuilder> b( new UdpBuilder());
		UdpParseContext context(parse_context,b);

		if(parse_internal(context)) {
			to_return = context.b->build();
#ifdef LOGGING
		} else {
			LOG(WARNING) << "Could not parse a udp packet";
#endif
		}

		return to_return;
	}

	UdpMaybe from_data( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data( parse_context );
	}

	Udp::InheritedProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context ) {
		Udp::InheritedProtocolMaybePtr to_return;
		boost::shared_ptr<UdpBuilder> b( new UdpBuilder());
		UdpParseContext context(parse_context,b);

		if(parse_internal(context)) {
			to_return = boost::dynamic_pointer_cast<Udp::InheritedProtocol>(context.b->build_ptr());
#ifdef LOGGING
		} else {
			LOG(WARNING) << "Could not parse a udp packet";
#endif
		}

		return to_return;
	}


	Udp::InheritedProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data_as_ptr( parse_context );
	}

}

