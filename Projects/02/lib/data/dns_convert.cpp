/*
 * dns_convert.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/config.h"
#include "dnsmuncher/util/byte/convert.h"
#include "dnsmuncher/util/byte/copy.h"
#include "dnsmuncher/util/join.h"
#include "dnsmuncher/data/convert_all.h"

#include <cstring>
#ifdef LOGGING
#include <glog/logging.h>
#endif

std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> DNSConvert::flags() const {
	std::bitset<DNS::GENERIC_HEADER_FIELD_LENGTH> flags;

	flags[DNS::QR_OFFSET] = this->dns->response;
	flags[DNS::AA_OFFSET] = this->dns->aa;
	flags[DNS::TC_OFFSET] = this->dns->tc;
	flags[DNS::RD_OFFSET] = this->dns->rd;
	flags[DNS::RA_OFFSET] = this->dns->ra;

	copy_into( flags, this->dns->opcode, DNS::OPCODE_OFFSET );
	copy_into( flags, this->dns->rcode, DNS::RCODE_OFFSET );

	return flags;
}

BytesContainer DNSConvert::to_data() const {
	const size_t gen_by_len = DNS::GENERIC_HEADER_FIELD_LENGTH / BITS_PER_BYTE;
	BytesContainer c;
	c = convert_big_endian<gen_by_len>(this->dns->id);
	c = join(c, convert_big_endian<gen_by_len>(flags()));
	c = join(c, convert_big_endian<gen_by_len>( this->dns->qd_count ));
	c = join(c, convert_big_endian<gen_by_len>( this->dns->an_count ));
	c = join(c, convert_big_endian<gen_by_len>( this->dns->ns_count ));
	c = join(c, convert_big_endian<gen_by_len>( this->dns->ar_count ));
	for( size_t i = 0; i < this->dns->questions.size(); ++i ) {
		c = join(c, QuestionConvert(*(this->dns->questions.at(i))).to_data());
	}
	for( size_t i = 0; i < this->dns->records.size(); ++i ) {
		c = join(c, ResourceRecordConvert(*(this->dns->records.at(i))).to_data());
	}
	return c;
}



