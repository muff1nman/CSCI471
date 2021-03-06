/*
 * raw.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_PARSE_RAW_H
#define ICMP_PARSE_RAW_H

#include "echo.h"
#include "ipv4/parse/ipv4.h"

#include "networkmuncher/util/byte/print.h"

namespace RAW {
	/**
	 * Parses the given stream of bytes into an Raw object.  If there was an issue,
	 * the return value will not be instaniated.
	 */
	RawMaybe from_data( ParseContext& parse_context ) {
		RawMaybe raw;
#ifdef LOGGING
		LOG(INFO) << "Bytes off wire:\n" <<  demaria_util::to_string( parse_context.raw_data );
#endif
		NetworkLayerProtocolMaybePtr ip = IPV4::from_data_as_ptr( parse_context );
		TransportLayerProtocolMaybePtr echo = ECHO::from_data_as_ptr( parse_context );
		if( ip && echo ) {
			raw = Raw(boost::dynamic_pointer_cast<Ipv4>(*ip), boost::dynamic_pointer_cast<Echo>(*echo));
		}
		return raw;
	}

	RawMaybe from_data( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data( parse_context );
	}

	/**
	 * Do the same as #from_data but return a shared_ptr instead
	 */
	RawMaybePtr from_data_as_ptr( ParseContext& parse_context ) {
		RawMaybePtr raw;
#ifdef LOGGING
		LOG(INFO) << "Bytes off wire:\n" <<  demaria_util::to_string( parse_context.raw_data );
#endif
		NetworkLayerProtocolMaybePtr ip = IPV4::from_data_as_ptr( parse_context );
		TransportLayerProtocolMaybePtr echo = ECHO::from_data_as_ptr( parse_context );
		if( ip && echo ) {
#ifdef LOGGING
			LOG(INFO) << "Valid ip and echo";
#endif
			raw = RawPtr( new Raw(boost::dynamic_pointer_cast<Ipv4>(*ip), boost::dynamic_pointer_cast<Echo>(*echo)));

		}
#ifdef LOGGING
	   	else {
			if(!ip) {
				LOG(INFO) << "Invalid ip";
			}
			if(!echo) {
				LOG(INFO) << "Invalid echo";
			}
		}
#endif
		return raw;
	}

	RawMaybePtr from_data_as_ptr( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data_as_ptr( parse_context );
	}

}

#endif /* !ICMP_PARSE_RAW_H */

