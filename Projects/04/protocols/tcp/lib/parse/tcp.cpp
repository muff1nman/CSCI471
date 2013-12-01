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

bool parse_internal( TcpParseContext& parse_context ) {
	return false;
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

	LinkLayerProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context ) {
		LinkLayerProtocolMaybePtr to_return;
		boost::shared_ptr<TcpBuilder> b( new Tcpv2Builder());
		TcpParseContext context(parse_context,b);

		if(parse_internal(context)) {
			to_return = boost::dynamic_pointer_cast<LinkLayerProtocol>(context.b->build_ptr());
#ifdef LOGGING
		} else {
			LOG(WARNING) << "Could not parse a tcp packet";
#endif
		}

		return to_return;
	}


	LinkLayerProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data_as_ptr( parse_context );
	}

}

