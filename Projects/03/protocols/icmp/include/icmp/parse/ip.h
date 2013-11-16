/*
 * ip.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_PARSE_IP_H
#define ICMP_PARSE_IP_H

#include "icmp/domain/domain.h"

namespace IP {

/**
 * Parses the given stream of bytes into an Ip object.  If there was an issue,
 * the return value will not be instaniated.
 */
IpMaybe from_data( const BytesContainer& raw ) {
	// TODO
	return IpMaybe();
}

/**
 * Do the same as #from_data but return a shared_ptr instead
 */
IpMaybePtr from_data_as_ptr( const BytesContainer& raw ) {
	/*TODO*/ 
	return IpMaybePtr();
}

}

#endif /* !ICMP_PARSE_IP_H */

