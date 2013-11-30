/*
 * ip.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_PARSE_IP_H
#define ICMP_PARSE_IP_H

#include "icmp/domain/domain.h"
#include "networkmuncher/util/byte/parse_context.h"
#include "networkmuncher/util/byte/parse_extra.h"
#include "networkmuncher/domain/all.h"

namespace IP {

/**
 * Parses the given stream of bytes into an Ip object.  If there was an issue,
 * the return value will not be instaniated.
 */
IpMaybe from_data( ParseContext& parse_context );
IpMaybe from_data( const BytesContainer& bytes );

/**
 * Do the same as #from_data but return a shared_ptr instead
 */
NetworkLayerProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context );
NetworkLayerProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes );

}

#endif /* !ICMP_PARSE_IP_H */

