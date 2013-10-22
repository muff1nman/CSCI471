/*
 * dns.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __parse_dns_h__
#define __parse_dns_h__

#include "dnsmuncher/domain/dns.h"
#include "dnsmuncher/dns.h"
#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>

/**
 * Parses the given stream of bytes into a DNS object.  If there was an issue,
 * the return value will not be instaniated.
 */
boost::optional<DNS> from_data( const BytesContainer raw );

/**
 * Do the same as #from_data but return a shared_ptr instead
 */
DnsMaybePtr from_data_as_ptr( const BytesContainer raw );

#endif /* !__dns_h__ */

