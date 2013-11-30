/*
 * ip.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "icmp/parse/ip.h"
#include "networkmuncher/util/logging.h"
#include "ip_parse_context.h"

bool parse_internal( IpParseContext& context ) {
	boost::optional<Ip::Version> version = parse_bitset<Ip::VERSION_LENGTH / BITS_PER_BYTE>(context);
	if(version) {
		// ensure version is IPv4
		if(version->to_ulong() == Ip::EXPECTED_VERSION ) {
			context.b->set_version(*version);
		} else {
			return false;
#ifdef LOGGING
			LOG(ERROR) << "Ipv4 version not correctly parsed";
#endif
		}
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse version";
#endif
		return false;
	}

	boost::optional<Ip::HeaderLength> header_length = parse_bitset<Ip::HEADER_LENGTH_LENGTH / BITS_PER_BYTE>(context);
	if(header_length) {
		context.b->set_header_length(*header_length);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse header_length";
#endif
		return false;
	}

	boost::optional<Ip::Tos> tos = parse_bitset<Ip::TOS_LENGTH / BITS_PER_BYTE>(context);
	if(tos) {
		context.b->set_type_of_service(*tos);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse tos";
#endif
		return false;
	}

	boost::optional<Ip::TotalLength> total_length = parse_bitset<Ip::TOTAL_LENGTH_LENGTH / BITS_PER_BYTE>(context);
	if(total_length) {
		context.b->set_total_length(*total_length);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse total_length";
#endif
		return false;
	}

	boost::optional<Ip::Id> id = parse_bitset<Ip::ID_LENGTH / BITS_PER_BYTE>(context);
	if(id) {
		context.b->set_id(*id);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse id";
#endif
		return false;
	}

	boost::optional<Ip::Flags> flags = parse_bitset<Ip::FLAGS_LENGTH / BITS_PER_BYTE>(context);
	if(flags) {
		context.b->set_flags(*flags);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse flags";
#endif
		return false;
	}

	boost::optional<Ip::FragOffset> frag_offset = parse_bitset<Ip::FRAG_OFFSET_LENGTH / BITS_PER_BYTE>(context);
	if(frag_offset) {
		context.b->set_fragment_offset(*frag_offset);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse frag offset";
#endif
		return false;
	}

	boost::optional<Ip::TTL> ttl = parse_bitset<Ip::TTL_LENGTH / BITS_PER_BYTE>(context);
	if(ttl) {
		context.b->set_ttl(*ttl);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse ttl";
#endif
		return false;
	}

	boost::optional<Ip::Protocol> protocol = parse_bitset<Ip::PROTOCOL_LENGTH / BITS_PER_BYTE>(context);
	if(protocol) {
		context.b->set_protocol(*protocol);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse protocol";
#endif
		return false;
	}

	boost::optional<Ip::Checksum> checksum = parse_bitset<Ip::CHECKSUM_LENGTH / BITS_PER_BYTE>(context);
	if(checksum) {
		context.b->set_checksum(*checksum);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse checksum";
#endif
		return false;
	}

	boost::optional<Ip::SourceAddr> source = parse_bitset<Ip::SOURCE_ADDR_LENGTH / BITS_PER_BYTE>(context);
	if(source) {
		context.b->set_source_addr(*source);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse source";
#endif
		return false;
	}

	boost::optional<Ip::DestAddr> dest_addr = parse_bitset<Ip::DEST_ADDR_LENGTH / BITS_PER_BYTE>(context);
	if(dest_addr) {
		context.b->set_dest_addr(*dest_addr);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse dest";
#endif
		return false;
	}

	// anything beyond ip header length we will treat as opionts.. which should be
	// divisible by 32 bit words
	size_t ip_header_length =
		VERSION_LENGTH +
		HEADER_LENGTH_LENGTH +
		TOS_LENGTH +
		TOTAL_LENGTH_LENGTH +
		ID_LENGTH +
		FLAGS_LENGTH +
		FRAG_OFFSET_LENGTH +
		TTL_LENGTH +
		PROTOCOL_LENGTH +
		CHECKSUM_LENGTH +
		SOURCE_ADDR_LENGTH +
		DEST_ADDR_LENGTH +
		0;

	size_t extra = header_length - ip_header_length;
	if( extra != 0 ) {
		if( extra % 32 == 0 ) {
#ifdef LOGGING
			LOG(INFO) << "Ip options present"
#endif
			BytesContainer options = parse_data(context, extra);
			// TODO
			//context.b->set_options(options);
		} else {
#ifdef LOGGING
			LOG(WARNING) << "Optional data not divisible by 32 bits";
#endif
			return false;
		}
#ifdef LOGGING
	} else {
		LOG(INFO) << "No optional data found with ipv4 header";
#endif
	}
	return true;
}

namespace IP {

	/**
	 * Parses the given stream of bytes into an Ip object.  If there was an issue,
	 * the return value will not be instaniated.
	 */
	IpMaybe from_data( ParseContext& parse_context ) {
		/*TODO*/ 
		IpMaybe to_return;
		ParseContext::ConstIterator end_of_ip = next(parse_context.current, 20);

#ifdef LOGGING
		BytesContainer copy(parse_context.current, end_of_ip);
		LOG(INFO) << "Parsing these bytes for ip:\n"
			<< demaria_util::to_string(copy);
#endif

		parse_context.current = end_of_ip;

		to_return = Ip();
		return to_return;
	}

	IpMaybe from_data( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data( parse_context );
	}

	/**
	 * Do the same as #from_data but return a shared_ptr instead
	 */
	NetworkLayerProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context ) {
		/*TODO*/ 
		NetworkLayerProtocolMaybePtr to_return;
		ParseContext::ConstIterator end_of_ip = next(parse_context.current, 20);

#ifdef LOGGING
		BytesContainer copy(parse_context.current, end_of_ip);
		LOG(INFO) << "Parsing these bytes for ip:\n"
			<< demaria_util::to_string(copy);
#endif

		parse_context.current = end_of_ip;

		to_return = NetworkLayerProtocolPtr( new Ip());

		return to_return;
	}


	NetworkLayerProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data_as_ptr( parse_context );
	}

}


