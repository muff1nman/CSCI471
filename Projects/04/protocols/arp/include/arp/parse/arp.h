/*
 * arp.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ARP_PARSE_IP_H
#define ARP_PARSE_IP_H

#include "arp/domain/domain.h"
#include "networkmuncher/util/byte/parse_context.h"
#include "networkmuncher/util/byte/parse_extra.h"
#include "networkmuncher/parse/parser_types.h"

namespace ARP {

/**
 * Parses the given stream of bytes into an Arp object.  If there was an issue,
 * the return value will not be instaniated.
 */
ArpMaybe from_data( ParseContext& parse_context );
ArpMaybe from_data( const BytesContainer& bytes );

/**
 * Do the same as #from_data but return a shared_ptr instead
 */
Arp::InheritedProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context );
Arp::InheritedProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes );

}

#endif /* !ARP_PARSE_IP_H */

