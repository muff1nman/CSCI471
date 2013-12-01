/*
 * tcp.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef TCP_PARSE_IP_H
#define TCP_PARSE_IP_H

#include "tcp/domain/domain.h"
#include "networkmuncher/util/byte/parse_context.h"
#include "networkmuncher/util/byte/parse_extra.h"
#include "networkmuncher/parse/parser_types.h"

namespace TCP {

/**
 * Parses the given stream of bytes into an Tcp object.  If there was an issue,
 * the return value will not be instaniated.
 */
TcpMaybe from_data( ParseContext& parse_context );
TcpMaybe from_data( const BytesContainer& bytes );

/**
 * Do the same as #from_data but return a shared_ptr instead
 */
LinkLayerProtocolMaybePtr from_data_as_ptr( ParseContext& parse_context );
LinkLayerProtocolMaybePtr from_data_as_ptr( const BytesContainer& bytes );

}

#endif /* !TCP_PARSE_IP_H */

