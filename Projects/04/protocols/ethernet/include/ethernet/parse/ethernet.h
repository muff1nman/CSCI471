/*
 * ethernet.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ETHERNET_PARSE_IP_H
#define ETHERNET_PARSE_IP_H

#include "ethernet/domain/domain.h"
#include "networkmuncher/util/byte/parse_context.h"
#include "networkmuncher/util/byte/parse_extra.h"
#include "networkmuncher/parse/parser_types.h"

namespace ETHERNETV2 {

/**
 * Parses the given stream of bytes into an Ethernet object.  If there was an issue,
 * the return value will not be instaniated.
 */
EthernetMaybe from_data( ParseContext& parse_context );
EthernetMaybe from_data( const BytesContainer& bytes );

/**
 * Do the same as #from_data but return a shared_ptr instead
 */
LinkLayerProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context );
LinkLayerProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes );

}

namespace ETHERNET8023 {

/**
 * Parses the given stream of bytes into an Ethernet object.  If there was an issue,
 * the return value will not be instaniated.
 */
EthernetMaybe from_data( ParseContext& parse_context );
EthernetMaybe from_data( const BytesContainer& bytes );

/**
 * Do the same as #from_data but return a shared_ptr instead
 */
LinkLayerProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context );
LinkLayerProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes );

}

#endif /* !ETHERNET_PARSE_IP_H */

