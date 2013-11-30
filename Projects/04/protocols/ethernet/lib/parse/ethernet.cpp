/*
 * ethernet.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "ethernet/domain/domain.h"
#include "ethernet/parse/ethernet.h"
#include "networkmuncher/util/logging.h"

namespace ETHERNETV2 {

	/**
	 * Parses the given stream of bytes into an Ethernet object.  If there was an issue,
	 * the return value will not be instaniated.
	 */
	EthernetMaybe from_data( ParseContext& parse_context ) {
		/*TODO*/ 
		EthernetMaybe to_return;

		EthernetBuilder b;

		to_return = b.build();
		return to_return;
	}

	EthernetMaybe from_data( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data( parse_context );
	}

	/**
	 * Do the same as #from_data but return a shared_ptr instead
	 */
	LinkLayerProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context ) {
		/*TODO*/ 
		LinkLayerProtocolMaybePtr to_return;

		EthernetBuilder b;

		to_return = boost::dynamic_pointer_cast<LinkLayerProtocol>(b.build_ptr());

		return to_return;
	}


	LinkLayerProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data_as_ptr( parse_context );
	}

}

namespace ETHERNET8023 {

	/**
	 * Parses the given stream of bytes into an Ethernet object.  If there was an issue,
	 * the return value will not be instaniated.
	 */
	EthernetMaybe from_data( ParseContext& parse_context ) {
		/*TODO*/ 
		EthernetMaybe to_return;

		EthernetBuilder b;

		to_return = b.build();
		return to_return;
	}

	EthernetMaybe from_data( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data( parse_context );
	}

	/**
	 * Do the same as #from_data but return a shared_ptr instead
	 */
	LinkLayerProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context ) {
		/*TODO*/ 
		LinkLayerProtocolMaybePtr to_return;

		EthernetBuilder b;

		to_return = boost::dynamic_pointer_cast<LinkLayerProtocol>(b.build_ptr());

		return to_return;
	}


	LinkLayerProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data_as_ptr( parse_context );
	}

}


