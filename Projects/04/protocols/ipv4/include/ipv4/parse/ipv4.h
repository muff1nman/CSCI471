/*
 * ipv4.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IPV4_PARSE_IPV4_H
#define IPV4_PARSE_IPV4_H

#include "ipv4/domain/domain.h"
#include "networkmuncher/util/byte/parse_context.h"
#include "networkmuncher/util/byte/parse_extra.h"
#include "networkmuncher/domain/all.h"

namespace IPV4 {

/**
 * Parses the given stream of bytes into an Ipv4 object.  If there was an issue,
 * the return value will not be instaniated.
 */
Ipv4Maybe from_data( ParseContext& parse_context );
Ipv4Maybe from_data( const BytesContainer& bytes );

/**
 * Do the same as #from_data but return a shared_ptr instead
 */
NetworkLayerProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context );
NetworkLayerProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes );

}

#endif /* !IPV4_PARSE_IPV4_H */

