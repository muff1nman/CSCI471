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
	boost::optional<Tcp::Port> source_port = parse_bitset<Tcp::PORT_LENGTH / BITS_PER_BYTE>(context);
	if(source_port) {
		context.b->set_source_port(*source_port);
	} else {
#ifdef LOGGING
		LOG(WARNING) << "Could not parse source port";
#endif
		return false;
	}

	boost::optional<Tcp::Port> dest_port = parse_bitset<Tcp::PORT_LENGTH / BITS_PER_BYTE>(context);
	if(dest_port) {
		context.b->set_dest_port(*dest_port);
	} else {
#ifdef LOGGING
		LOG(WARNING) << "Could not parse dest port";
#endif
		return false;
	}

	boost::optional<Tcp::SynAck> seq_num = parse_bitset<Tcp::SYNACK_NUM_LENGTH/ BITS_PER_BYTE>(context);
	if(seq_num) {
		context.b->set_seq_num(*seq_num);
	} else {
#ifdef LOGGING
		LOG(WARNING) << "Could not parse sequence number";
#endif
		return false;
	}

	boost::optional<Tcp::SynAck> ack_num = parse_bitset<Tcp::SYNACK_NUM_LENGTH/ BITS_PER_BYTE>(context);
	if(ack_num) {
		context.b->set_ack_num(*ack_num);
	} else {
#ifdef LOGGING
		LOG(WARNING) << "Could not parse ack number";
#endif
		return false;
	}

#define DATA_RESERVED_FLAGS_LENGTH (Tcp::DATA_OFFSET_LENGTH + Tcp::RESERVED_LENGTH + Tcp::FLAGS_LENGTH)


	boost::optional<std::bitset<DATA_RESERVED_FLAGS_LENGTH> > combined = parse_bitset<DATA_RESERVED_FLAGS_LENGTH / BITS_PER_BYTE>(context);
	Tcp::DataOffset data_offset;
	Tcp::Reserved reserved;
	Tcp::Flags flags;
	if(combined) {
		 data_offset = dissect<DATA_RESERVED_FLAGS_LENGTH,Tcp::DATA_OFFSET_LENGTH>(*combined, DATA_RESERVED_FLAGS_LENGTH - Tcp::DATA_OFFSET_LENGTH);
		 reserved = dissect<DATA_RESERVED_FLAGS_LENGTH,Tcp::RESERVED_LENGTH>(*combined, Tcp::FLAGS_LENGTH);
		 flags = dissect<DATA_RESERVED_FLAGS_LENGTH,Tcp::FLAGS_LENGTH>(*combined, 0);
		 context.b->set_data_offset(data_offset);
		 context.b->set_reserved(reserved);
		 context.b->set_flags(flags);
	} else {
#ifdef LOGGING
		LOG(WARNING) << "Could not parse data offset, reserved or flags";
#endif
		return false;

	}

	//if(data_offset) {
		//context.b->set_data_offset(*data_offset);
	//} else {
//#ifdef LOGGING
		//LOG(WARNING) << "Could not parse data offset";
//#endif
		//return false;
	//}

	//boost::optional<Tcp::Reserved> reserved = parse_bitset<Tcp::RESERVED_LENGTH / BITS_PER_BYTE>(context);
	//if(reserved) {
		//context.b->set_reserved(*reserved);
	//} else {
//#ifdef LOGGING
		//LOG(WARNING) << "Could not parse reserved";
//#endif
		//return false;
	//}

	//boost::optional<Tcp::Flags> flags = parse_bitset<Tcp::FLAGS_LENGTH / BITS_PER_BYTE>(context);
	//if(flags) {
		//context.b->set_flags(*flags);
	//} else {
//#ifdef LOGGING
		//LOG(WARNING) << "Could not parse flags";
//#endif
		//return false;
	//}

	boost::optional<Tcp::WindowSize> window_size = parse_bitset<Tcp::WINDOW_SIZE_LENGTH / BITS_PER_BYTE>(context);
	if(window_size) {
		context.b->set_window_size(*window_size);
	} else {
#ifdef LOGGING
		LOG(WARNING) << "Could not parse window size";
#endif
		return false;
	}

	boost::optional<Tcp::Checksum> checksum = parse_bitset<Tcp::CHECKSUM_LENGTH / BITS_PER_BYTE>(context);
	if(checksum) {
		context.b->set_checksum(*checksum);
	} else {
#ifdef LOGGING
		LOG(WARNING) << "Could not parse checksum";
#endif
		return false;
	}

	boost::optional<Tcp::Urgent> urgent = parse_bitset<Tcp::URGENT_LENGTH / BITS_PER_BYTE>(context);
	if(urgent) {
		context.b->set_urgent(*urgent);
	} else {
#ifdef LOGGING
		LOG(WARNING) << "Could not parse urgent";
#endif
		return false;
	}

	// based on data offset, do we have any bytes left?
	size_t tcp_header_length = 
		2 * Tcp::PORT_LENGTH +
		2 * Tcp::SYNACK_NUM_LENGTH +
		Tcp::DATA_OFFSET_LENGTH + 
		Tcp::RESERVED_LENGTH + 
		Tcp::FLAGS_LENGTH +
		Tcp::WINDOW_SIZE_LENGTH +
		Tcp::CHECKSUM_LENGTH +
		Tcp::URGENT_LENGTH;

	int extra = data_offset.to_ulong() * 4 * BITS_PER_BYTE - tcp_header_length;

	if( extra != 0 ) {
		if( extra % 32 == 0 ) {
#ifdef LOGGING
			LOG(INFO) << "Tcp options available";
#endif
			boost::optional<Tcp::Options> options = parse_data(context, extra/BITS_PER_BYTE);

			if(options) {
				context.b->set_options(*options);
			} else {
#ifdef LOGGING
				LOG(WARNING) << "Could not parse options";
#endif
				return false;
			}
		} else {
#ifdef LOGGING
			LOG(WARNING) << "Options not divisible by 32 bits";
#endif
			return false;
		}
	}

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

