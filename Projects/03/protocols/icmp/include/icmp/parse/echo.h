/*
 * echo.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_PARSE_ECHO_H
#define ICMP_PARSE_ECHO_H

#include "icmp/domain/domain.h"

namespace ECHO {

/**
 * Parses the given stream of bytes into an Echo object.  If there was an issue,
 * the return value will not be instaniated.
 */
EchoMaybe from_data( ParseContext& parse_context );
EchoMaybe from_data( const BytesContainer& bytes );

/**
 * Do the same as #from_data but return a shared_ptr instead
 */
EchoMaybePtr from_data_as_ptr( ParseContext& parse_context );
EchoMaybePtr from_data_as_ptr( const BytesContainer& bytes );

}

#endif /* !ICMP_PARSE_ECHO_H */

