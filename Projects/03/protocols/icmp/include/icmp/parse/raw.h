/*
 * raw.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_PARSE_RAW_H
#define ICMP_PARSE_RAW_H

#include "echo.h"
#include "ip.h"

#include "networkmuncher/util/byte/print.h"

namespace RAW {
/**
 * Parses the given stream of bytes into an Raw object.  If there was an issue,
 * the return value will not be instaniated.
 */
RawMaybe from_data( ParseContext& parse_context ) {
  RawMaybe raw;
  demaria_util::to_string( parse_context.raw_data );
  IpMaybePtr ip = IP::from_data_as_ptr( parse_context );
  EchoMaybePtr echo = ECHO::from_data_as_ptr( parse_context );
  if( ip && echo ) {
    raw = Raw(*ip, *echo);
  }
	return raw;
}

/**
 * Do the same as #from_data but return a shared_ptr instead
 */
RawMaybePtr from_data_as_ptr( ParseContext& parse_context ) {
  RawMaybePtr raw;
  demaria_util::to_string( parse_context.raw_data );
  IpMaybePtr ip = IP::from_data_as_ptr( parse_context );
  EchoMaybePtr echo = ECHO::from_data_as_ptr( parse_context );
  if( ip && echo ) {
    raw = RawPtr( new Raw(*ip, *echo));
  }
	return raw;
}

}

#endif /* !ICMP_PARSE_RAW_H */

