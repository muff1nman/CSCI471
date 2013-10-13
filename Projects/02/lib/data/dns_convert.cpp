/*
 * dns_convert.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/config.h"
#include "dnsmuncher/data/dns_convert.h"
#include "dnsmuncher/util/byte/convert.h"
#include "dnsmuncher/util/byte/copy.h"

#include <cstring>
#ifdef LOGGING
#include <glog/logging.h>
#endif

DNSConvert::DNSConvert(boost::shared_ptr<DNS> dns) : dns(dns) {
	// TODO
}

void copy_into(std::bitset<n> larger, 

std::bitset<GENERIC_HEADER_LENGTH> flags() {
	const size_t QR_OFFSET = 0;
	const size_t OPCODE_OFFSET = 1;
	const size_t AA_OFFSET = 5;
	const size_t TC_OFFSET = 6;
	const size_t RD_OFFSET = 7;
	const size_t RA_OFFSET = 8;
	const size_t Z_OFFSET = 9;
	const size_t RCODE_OFFSET = 12;

	std::bitset<GENERIC_HEADER_LENGTH> flags;

	flags[QR_OFFSET] = qr;
	flags[AA_OFFSET] = aa;
	flags[TC_OFFSET] = tc;
	flags[RD_OFFSET] = rd;
	flags[RA_OFFSET] = ra;

	copy_into( flags, opcode, OPCODE_OFFSET );
	copy_into( flags, rcode, RCODE_OFFSET );

	return flags;
}

// TODO test
BytesContainer DNSConvert::to_data() const {
	BytesContainer c;
	c = convert_big_endian<2>(this->dns->id);
	c = join(c, convert_big_endian<2>(flags()));
	return c;
}



