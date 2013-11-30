/*
 * ip.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "icmp/parse/ip.h"
#include "networkmuncher/util/logging.h"


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


