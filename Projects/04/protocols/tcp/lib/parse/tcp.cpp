/*
 * tcp.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "tcp/domain/domain.h"
#include "tcp/parse/tcp.h"
#include "networkmuncher/util/logging.h"
#include "tcp_parse_context.h"
#include "networkmuncher/util/byte/parse_extra.h"

bool parse_internal( TcpParseContext& context ) {
	boost::optional<Tcp::HardwareType> hardware_type = parse_bitset<Tcp::HARDWARE_TYPE_LENGTH / BITS_PER_BYTE>(context);
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

	boost::optional<Tcp::ProtocolType> protocol_type = parse_bitset<Tcp::PROTOCOL_TYPE_LENGTH / BITS_PER_BYTE>(context);
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

	boost::optional<Tcp::HardwareSize> hardware_size = parse_bitset<Tcp::HARDWARE_SIZE_LENGTH / BITS_PER_BYTE>(context);
	if(hardware_size) {
		context.b->set_hardware_size(*hardware_size);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse hardware size";
#endif
		return false;
	}

	boost::optional<Tcp::ProtocolSize> protocol_size = parse_bitset<Tcp::PROTOCOL_SIZE_LENGTH / BITS_PER_BYTE>(context);
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

namespace TCP {

	TcpMaybe from_data( ParseContext& parse_context ) {
		TcpMaybe to_return;
		boost::shared_ptr<TcpBuilder> b( new TcpBuilder());
		TcpParseContext context(parse_context,b);

		if(parse_internal(context)) {
			to_return = context.b->build();
#ifdef LOGGING
		} else {
			LOG(WARNING) << "Could not parse a tcp packet";
#endif
		}

		return to_return;
	}

	TcpMaybe from_data( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data( parse_context );
	}

	Tcp::InheritedProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context ) {
		Tcp::InheritedProtocolMaybePtr to_return;
		boost::shared_ptr<TcpBuilder> b( new TcpBuilder());
		TcpParseContext context(parse_context,b);

		if(parse_internal(context)) {
			to_return = boost::dynamic_pointer_cast<Tcp::InheritedProtocol>(context.b->build_ptr());
#ifdef LOGGING
		} else {
			LOG(WARNING) << "Could not parse a tcp packet";
#endif
		}

		return to_return;
	}


	Tcp::InheritedProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data_as_ptr( parse_context );
	}

}

