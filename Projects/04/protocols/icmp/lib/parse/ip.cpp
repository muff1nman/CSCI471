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

#define VH_LEN (Ip::VERSION_LENGTH + Ip::HEADER_LENGTH_LENGTH)

	boost::optional< std::bitset<VH_LEN> > v_and_h;
	v_and_h = parse_bitset<VH_LEN / BITS_PER_BYTE>(context);

	Ip::HeaderLength header_length;
	Ip::Version version;
	if(v_and_h) {
#ifdef LOGGING
		LOG(INFO) << "Parsing: " << v_and_h->to_string() << " " << v_and_h->to_ulong();
#endif
		version = dissect<VH_LEN,Ip::VERSION_LENGTH>(*v_and_h, Ip::HEADER_LENGTH_LENGTH);
		header_length = dissect<VH_LEN,Ip::HEADER_LENGTH_LENGTH>(*v_and_h);
		// ensure version is IPv4
		if(version.to_ulong() == Ip::EXPECTED_VERSION ) {
			context.b->set_version(version);
		} else {
#ifdef LOGGING
			LOG(ERROR) << "Unexpected ipv4 version, found: " << version.to_ulong();
#endif
			return false;
		}
		context.b->set_header_length(header_length);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse version and header";
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

#define FF_LEN (Ip::FLAGS_LENGTH + Ip::FRAG_OFFSET_LENGTH)

	boost::optional< std::bitset<FF_LEN> > f_and_f;
	f_and_f = parse_bitset<FF_LEN / BITS_PER_BYTE>(context);

	if(f_and_f) {
		Ip::Flags flags = dissect<FF_LEN, Ip::FLAGS_LENGTH>(*f_and_f,Ip::FRAG_OFFSET_LENGTH);
		Ip::FragOffset frag = dissect<FF_LEN, Ip::FRAG_OFFSET_LENGTH>(*f_and_f);
		context.b->set_flags(flags);
		context.b->set_fragment_offset(frag);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse flags or frag len";
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
		Ip::VERSION_LENGTH +
		Ip::HEADER_LENGTH_LENGTH +
		Ip::TOS_LENGTH +
		Ip::TOTAL_LENGTH_LENGTH +
		Ip::ID_LENGTH +
		Ip::FLAGS_LENGTH +
		Ip::FRAG_OFFSET_LENGTH +
		Ip::TTL_LENGTH +
		Ip::PROTOCOL_LENGTH +
		Ip::CHECKSUM_LENGTH +
		Ip::SOURCE_ADDR_LENGTH +
		Ip::DEST_ADDR_LENGTH +
		0;

	int extra = header_length.to_ulong() * 4 * BITS_PER_BYTE - ip_header_length;
	if( extra != 0 ) {
		if( extra % 32 == 0 ) {
#ifdef LOGGING
			LOG(INFO) << "Ip options present";
#endif
			boost::optional<BytesContainer> options = parse_data(context, extra/BITS_PER_BYTE);
			if( options ) {
				// TODO
				//context.b->set_options(*options);
			} else {
#ifdef LOGGING
				LOG(ERROR) << "Could not parse options";
#endif
				return false;
			}
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
		IpMaybe to_return;
		boost::shared_ptr<IpBuilder> ip_b(new IpBuilder());
		IpParseContext context(parse_context, ip_b);
		if(parse_internal(context)) {
			to_return = context.b->build();
		}
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
		NetworkLayerProtocolMaybePtr to_return;
		boost::shared_ptr<IpBuilder> ip_b( new IpBuilder());
		IpParseContext context(parse_context, ip_b);
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


