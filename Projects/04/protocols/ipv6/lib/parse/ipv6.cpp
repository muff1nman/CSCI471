/*
 * ipv6.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "ipv6/parse/ipv6.h"
#include "networkmuncher/util/logging.h"
#include "ipv6_parse_context.h"

bool parse_internal( Ipv6ParseContext& context ) {

#define VHF_LEN (Ipv6::VERSION_LENGTH + Ipv6::TOS_LENGTH + Ipv6::FLOW_LENGTH)

	boost::optional< std::bitset<VHF_LEN> > vhf;
	vhf = parse_bitset<VHF_LEN / BITS_PER_BYTE>(context);

	Ipv6::Version version;
	Ipv6::Tos tos;
	Ipv6::Flow flow;
	if(vhf) {
		version = dissect<VHF_LEN,Ipv6::VERSION_LENGTH>(*vhf, VHF_LEN - Ipv6::VERSION_LENGTH);
		tos = dissect<VHF_LEN,Ipv6::TOS_LENGTH>(*vhf, Ipv6::FLOW_LENGTH);
		flow = dissect<VHF_LEN,Ipv6::FLOW_LENGTH>(*vhf,0);
		// ensure version is IPV6v4
		if(version.to_ulong() == Ipv6::EXPECTED_VERSION ) {
			context.b->set_version(version);
		} else {
#ifdef LOGGING
			LOG(ERROR) << "Unexpected ipv6 version, found: " << version.to_ulong();
#endif
			return false;
		}
		context.b->set_type_of_service(tos);
		context.b->set_flow(flow);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse version and header";
#endif
		return false;
	}

	boost::optional<Ipv6::TotalLength> total_length = parse_bitset<Ipv6::TOTAL_LENGTH_LENGTH / BITS_PER_BYTE>(context);
	if(total_length) {
		context.b->set_total_length(*total_length);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse total_length";
#endif
		return false;
	}

	boost::optional<Ipv6::NextHeader> next_header = parse_bitset<Ipv6::NEXT_HEADER_LENGTH / BITS_PER_BYTE>(context);
	if(next_header) {
		context.b->set_next_header(*next_header);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse next header";
#endif
		return false;
	}

	boost::optional<Ipv6::HopLimit> hop_limit = parse_bitset<Ipv6::HOP_LIMIT_LENGTH / BITS_PER_BYTE>(context);
	if(hop_limit) {
		context.b->set_hop_limit(*hop_limit);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse hop limit";
#endif
		return false;
	}

	boost::optional<Ipv6::Addr> source = parse_bitset<Ipv6::ADDR_LENGTH / BITS_PER_BYTE>(context);
	if(source) {
		context.b->set_source_addr(*source);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse source";
#endif
		return false;
	}

	boost::optional<Ipv6::Addr> dest_addr = parse_bitset<Ipv6::ADDR_LENGTH / BITS_PER_BYTE>(context);
	if(dest_addr) {
		context.b->set_dest_addr(*dest_addr);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse dest";
#endif
		return false;
	}

	return true;
}

namespace IPV6 {

	/**
	 * Parses the given stream of bytes into an Ipv6 object.  If there was an issue,
	 * the return value will not be instaniated.
	 */
	Ipv6Maybe from_data( ParseContext& parse_context ) {
		Ipv6Maybe to_return;
		boost::shared_ptr<Ipv6Builder> ipv6_b(new Ipv6Builder());
		Ipv6ParseContext context(parse_context, ipv6_b);
		if(parse_internal(context)) {
			to_return = context.b->build();
		}
		return to_return;
	}

	Ipv6Maybe from_data( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data( parse_context );
	}

	/**
	 * Do the same as #from_data but return a shared_ptr instead
	 */
	NetworkLayerProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context ) {
		NetworkLayerProtocolMaybePtr to_return;
		boost::shared_ptr<Ipv6Builder> ipv6_b( new Ipv6Builder());
		Ipv6ParseContext context(parse_context, ipv6_b);
		if(parse_internal(context)) {
			to_return = boost::dynamic_pointer_cast<NetworkLayerProtocol>(context.b->build_ptr());
		}

		return to_return;
	}


	NetworkLayerProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data_as_ptr( parse_context );
	}

}


