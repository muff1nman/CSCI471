/*
 * arp.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "arp/domain/domain.h"
#include "arp/parse/arp.h"
#include "networkmuncher/util/logging.h"
#include "arp_parse_context.h"
#include "networkmuncher/util/byte/parse_extra.h"

bool parse_internal( ArpParseContext& context ) {
	boost::optional<Arp::HardwareType> hardware_type = parse_bitset<Arp::HARDWARE_TYPE_LENGTH / BITS_PER_BYTE>(context);
	if(hardware_type) {
		// ensure we are looking at ethernet
		const size_t ETHERNET = 1;
		if((*hardware_type).to_ulong() == ETHERNET) {
			context.b->set_hardware_type(*hardware_type);
		} else {
#ifdef LOGGING
			LOG(WARNING) << "Found invalid hardware type (expected is " << ETHERNET << " but was " << (*hardware_type);
#endif
			return false;
		}
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse hardware_type";
#endif
		return false;
	}

	boost::optional<Arp::ProtocolType> protocol_type = parse_bitset<Arp::PROTOCOL_TYPE_LENGTH / BITS_PER_BYTE>(context);
	if(protocol_type) {
		// ensure we are looking at ethernet
		if((*protocol_type).to_ulong() == 2048) {
			context.b->set_protocol_type(*protocol_type);
		} else {
#ifdef LOGGING
			LOG(WARNING) << "Found invalid protocol type";
#endif
			return false;
		}
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse protocol_type";
#endif
		return false;
	}

	boost::optional<Arp::HardwareSize> hardware_size = parse_bitset<Arp::HARDWARE_SIZE_LENGTH / BITS_PER_BYTE>(context);
	if(hardware_size) {
		context.b->set_hardware_size(*hardware_size);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse hardware size";
#endif
		return false;
	}

	boost::optional<Arp::ProtocolSize> protocol_size = parse_bitset<Arp::PROTOCOL_SIZE_LENGTH / BITS_PER_BYTE>(context);
	if(protocol_size) {
		context.b->set_protocol_size(*protocol_size);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse protocol size";
#endif
		return false;
	}

// TODO

	return true;
}

namespace ARP {

	ArpMaybe from_data( ParseContext& parse_context ) {
		ArpMaybe to_return;
		boost::shared_ptr<ArpBuilder> b( new ArpBuilder());
		ArpParseContext context(parse_context,b);

		if(parse_internal(context)) {
			to_return = context.b->build();
#ifdef LOGGING
		} else {
			LOG(WARNING) << "Could not parse a arp packet";
#endif
		}

		return to_return;
	}

	ArpMaybe from_data( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data( parse_context );
	}

	Arp::InheritedProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context ) {
		Arp::InheritedProtocolMaybePtr to_return;
		boost::shared_ptr<ArpBuilder> b( new ArpBuilder());
		ArpParseContext context(parse_context,b);

		if(parse_internal(context)) {
			to_return = boost::dynamic_pointer_cast<Arp::InheritedProtocol>(context.b->build_ptr());
#ifdef LOGGING
		} else {
			LOG(WARNING) << "Could not parse a arp packet";
#endif
		}

		return to_return;
	}


	Arp::InheritedProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data_as_ptr( parse_context );
	}

}

