/*
 * raw.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_PARSE_RAW_H
#define ICMP_PARSE_RAW_H

namespace RAW {
/**
 * Parses the given stream of bytes into an Raw object.  If there was an issue,
 * the return value will not be instaniated.
 */
RawMaybe from_data( const BytesContainer& raw ) {
	/*TODO*/
	return RawMaybe();
}

/**
 * Do the same as #from_data but return a shared_ptr instead
 */
RawMaybePtr from_data_as_ptr( const BytesContainer& raw ) {
	/*TODO*/
	return RawMaybePtr();
}

}

#endif /* !ICMP_PARSE_RAW_H */

