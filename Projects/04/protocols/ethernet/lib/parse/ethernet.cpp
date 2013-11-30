/*
 * ethernet.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "ethernet/domain/domain.h"
#include "ethernet/parse/ethernet.h"
#include "networkmuncher/util/logging.h"
#include "ethernet_parse_context.h"
#include "networkmuncher/util/byte/parse_extra.h"

bool parse_internal( EthernetParseContext& parse_context, bool ethernetv2or8023 ) {
	boost::optional<MacAddr> dest = parse_bitset<MAC_ADDR_LENGTH / BITS_PER_BYTE>(parse_context);
	if(dest) {
		parse_context.b->set_dest_addr(*dest);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse dest";
#endif
		return false;
	}

	boost::optional<MacAddr> src = parse_bitset<MAC_ADDR_LENGTH / BITS_PER_BYTE>(parse_context);
	if(src) {
		parse_context.b->set_source_addr(*src);
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse src";
#endif
		return false;
	}

	boost::optional<Ethernet::Extra> extra = parse_bitset<Ethernet::EXTRA_LENGTH / BITS_PER_BYTE>(parse_context);
	if(extra) {
		parse_context.b->set_extra(*extra);
		if( ethernetv2or8023 ) {
			// ethernet2: parse as type
			if(extra->to_ulong() < 1536 ) {
#ifdef LOGGING
				LOG(WARNING) << "Extra could not be interpretted as type (Ethernet II)";
#endif
				return false;
			}
		} else {
			// ethernet 802.3: parse as length
			if(extra->to_ulong() > 1500 ) {
#ifdef LOGGING
				LOG(WARNING) << "Extra could not be interpretted as length (802.3)";
#endif
				return false;
			}
		}
	} else {
#ifdef LOGGING
		LOG(ERROR) << "Could not parse extra";
#endif
		return false;
	}

	return true;
}

namespace ETHERNETV2 {

	EthernetMaybe from_data( ParseContext& parse_context ) {
		EthernetMaybe to_return;
		boost::shared_ptr<EthernetBuilder> b( new Ethernetv2Builder());
		EthernetParseContext context(parse_context,b);

		if(parse_internal(context, true)) {
			to_return = context.b->build();
#ifdef LOGGING
		} else {
			LOG(WARNING) << "Could not parse an ethernet II packet";
#endif
		}

		return to_return;
	}

	EthernetMaybe from_data( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data( parse_context );
	}

	LinkLayerProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context ) {
		LinkLayerProtocolMaybePtr to_return;
		boost::shared_ptr<EthernetBuilder> b( new Ethernetv2Builder());
		EthernetParseContext context(parse_context,b);

		if(parse_internal(context, true)) {
			to_return = boost::dynamic_pointer_cast<LinkLayerProtocol>(context.b->build_ptr());
#ifdef LOGGING
			LOG(INFO) << "What type? " << (*to_return)->what_type();
		} else {
			LOG(WARNING) << "Could not parse an ethernet II packet";
#endif
		}

		return to_return;
	}


	LinkLayerProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data_as_ptr( parse_context );
	}

}

namespace ETHERNET8023 {

	EthernetMaybe from_data( ParseContext& parse_context ) {
		EthernetMaybe to_return;
		boost::shared_ptr<EthernetBuilder> b( new Ethernet8023Builder());
		EthernetParseContext context(parse_context,b);

		if(parse_internal(context, false)) {
			to_return = context.b->build();
#ifdef LOGGING
		} else {
			LOG(WARNING) << "Could not parse an ethernet 802.3 packet";
#endif
		}

		return to_return;
	}

	EthernetMaybe from_data( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data( parse_context );
	}

	LinkLayerProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context ) {
		LinkLayerProtocolMaybePtr to_return;
		boost::shared_ptr<EthernetBuilder> b( new Ethernet8023Builder());
		EthernetParseContext context(parse_context,b);

		if(parse_internal(context, false)) {
			to_return = boost::dynamic_pointer_cast<LinkLayerProtocol>(context.b->build_ptr());
#ifdef LOGGING
		} else {
			LOG(WARNING) << "Could not parse an ethernet 802.3 packet";
#endif
		}

		return to_return;
	}


	LinkLayerProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes ) {
		ParseContext parse_context(bytes, bytes.begin(), bytes.end(), bytes.begin());
		return from_data_as_ptr( parse_context );
	}

}


