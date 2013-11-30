/*
 * icmp_helper.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_HELPER_H
#define ICMP_HELPER_H

#include "test_helper.h"

EchoPtr google_echo_request_echo_part() {
	Echo::Checksum checksum = Echo::Checksum(std::string("0100111101110011"));
	BytesContainer data = boost::assign::list_of
		('\x77') ('\xd2') ('\x83') ('\x52') ('\x00') ('\x00') ('\x00') ('\x00') ('\xe2')
		('\x5c') ('\x09') ('\x00') ('\x00') ('\x00') ('\x00') ('\x00') ('\x10') ('\x11')
		('\x12') ('\x13') ('\x14') ('\x15') ('\x16') ('\x17') ('\x18') ('\x19') ('\x1a')
		('\x1b') ('\x1c') ('\x1d') ('\x1e') ('\x1f') ('\x20') ('\x21') ('\x22') ('\x23')
		('\x24') ('\x25') ('\x26') ('\x27') ('\x28') ('\x29') ('\x2a') ('\x2b') ('\x2c')
		('\x2d') ('\x2e') ('\x2f') ('\x30') ('\x31') ('\x32') ('\x33') ('\x34') ('\x35')
		('\x36') ('\x37') ;

	return EchoBuilder()
		.set_request_type()
		.set_checksum(checksum) // TODO test to catch not flipping of the bits
		.set_identifier(823)
		.set_sequence_num(1)
		.set_data(data)
		.build_ptr();
}

IpPtr google_echo_request_ip_part() {
	return IpBuilder()
		.set_total_length(84)
		.set_id(20409)
		.set_dont_fragment()
		.set_ttl(64)
		.set_protocol(1)
		.set_checksum(Ip::Checksum(std::string("110011000111111")))
		.set_source_addr(Ip::SourceAddr(std::string("10001010010000111100111000011011")))
		.set_dest_addr(Ip::DestAddr(std::string("1001010011111011110000111010100")))
		.build_ptr();
}

RawPtr google_echo_request() {
	return RawPtr(new Raw(google_echo_request_ip_part(), google_echo_request_echo_part()));
}

EchoPtr google_echo_reply_echo_part() {
	BytesContainer data = boost::assign::list_of
		('\x77') ('\xd2') ('\x83') ('\x52') ('\x00') ('\x00') ('\x00') ('\x00')
		('\xe2') ('\x5c') ('\x09') ('\x00') ('\x00') ('\x00') ('\x00') ('\x00')
		('\x10') ('\x11') ('\x12') ('\x13') ('\x14') ('\x15') ('\x16') ('\x17')
		('\x18') ('\x19') ('\x1a') ('\x1b') ('\x1c') ('\x1d') ('\x1e') ('\x1f')
		('\x20') ('\x21') ('\x22') ('\x23') ('\x24') ('\x25') ('\x26') ('\x27')
		('\x28') ('\x29') ('\x2a') ('\x2b') ('\x2c') ('\x2d') ('\x2e') ('\x2f')
		('\x30') ('\x31') ('\x32') ('\x33') ('\x34') ('\x35') ('\x36') ('\x37');
	return EchoBuilder()
		.set_reply_type()
		.set_checksum(Echo::Checksum(std::string("101011101110011")))
		.set_identifier(823)
		.set_sequence_num(1)
		.set_data(data)
		.build_ptr();
}

IpPtr google_echo_reply_ip_part() {
	return IpBuilder()
		.set_total_length(84)
		.set_id(37189)
		.set_ttl(56)
		.set_protocol(1)
		.set_checksum(Ip::Checksum(std::string("110110010110011")))
		.set_source_addr(Ip::SourceAddr(std::string("1001010011111011110000111010100")))
		.set_dest_addr(Ip::DestAddr(std::string("10001010010000111100111000011011")))
		.build_ptr();
}

RawPtr google_echo_reply() {
	return RawPtr(new Raw(google_echo_reply_ip_part(), google_echo_reply_echo_part()));
}



#endif /* !ICMP_HELPER_H */

