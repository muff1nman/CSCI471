/*
 * udp.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef UDP_PARSE_IP_H
#define UDP_PARSE_IP_H

#include "udp/domain/domain.h"
#include "networkmuncher/util/byte/parse_context.h"
#include "networkmuncher/util/byte/parse_extra.h"
#include "networkmuncher/parse/parser_types.h"

namespace UDP {

/**
 * Parses the given stream of bytes into an Udp object.  If there was an issue,
 * the return value will not be instaniated.
 */
UdpMaybe from_data( ParseContext& parse_context );
UdpMaybe from_data( const BytesContainer& bytes );

/**
 * Do the same as #from_data but return a shared_ptr instead
 */
Udp::InheritedProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context );
Udp::InheritedProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes );

}

#endif /* !UDP_PARSE_IP_H */

