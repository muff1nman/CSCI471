/*
 * ipv6_helper.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IPV6_HELPER_H
#define IPV6_HELPER_H

#include "test_helper.h"

Ipv6Ptr google_echo_request_ipv6_part() {
	return Ipv6Builder()
		.set_total_length(84)
		.set_id(20409)
		.set_dont_fragment()
		.set_ttl(64)
		.set_protocol(1)
		.set_checksum(Ipv6::Checksum(std::string("110011000111111")))
		.set_source_addr(Ipv6::Addr(std::string("10001010010000111100111000011011")))
		.set_dest_addr(Ipv6::Addr(std::string("1001010011111011110000111010100")))
		.build_ptr();
}

Ipv6Ptr google_echo_reply_ipv6_part() {
	return Ipv6Builder()
		.set_total_length(84)
		.set_id(37189)
		.set_ttl(56)
		.set_protocol(1)
		.set_checksum(Ipv6::Checksum(std::string("110110010110011")))
		.set_source_addr(Ipv6::Addr(std::string("1001010011111011110000111010100")))
		.set_dest_addr(Ipv6::Addr(std::string("10001010010000111100111000011011")))
		.build_ptr();
}

#endif /* !IPV6_HELPER_H */

