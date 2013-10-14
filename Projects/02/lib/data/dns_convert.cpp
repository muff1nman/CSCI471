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

std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> DNSConvert::flags() const {
	std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> flags;

	flags[DNS::QR_OFFSET] = this->dns->qr;
	flags[DNS::AA_OFFSET] = this->dns->aa;
	flags[DNS::TC_OFFSET] = this->dns->tc;
	flags[DNS::RD_OFFSET] = this->dns->rd;
	flags[DNS::RA_OFFSET] = this->dns->ra;

	copy_into( flags, this->dns->opcode, DNS::OPCODE_OFFSET );
	copy_into( flags, this->dns->rcode, DNS::RCODE_OFFSET );

	return flags;
}

BytesContainer DNSConvert::to_data() const {
	BytesContainer c;
	c = convert_big_endian<2>(this->dns->id);
	c = join(c, convert_big_endian<2>(flags()));
	return c;
}



