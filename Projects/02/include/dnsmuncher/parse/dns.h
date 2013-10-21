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

boost::optional<DNS> from_data( const BytesContainer raw );

DnsMaybePtr from_data_as_ptr( const BytesContainer raw );

#endif /* !__dns_h__ */

