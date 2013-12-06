/*
 * ip_addr_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IPv6_ADDR_CONVERT_H
#define IPv6_ADDR_CONVERT_H

#include "networkmuncher/data/convert.h"

#include "networkmuncher/util/logging.h"

#include "ipv6/domain/ipv6.h"

#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/byte/copy.h"
#include "networkmuncher/util/byte/convert.h"
#include "networkmuncher/util/index.h"
#include "networkmuncher/util/split.h"

#include <string>

/**
 * Handy class that will convert your ips to a binary representation.
 *
 * If something goes wrong, return an empty container.
 */
class Ipv6AddrConvert : public Convert {
	public:
		Ipv6AddrConvert(const std::string& ip) : ip(ip) { }

		virtual BytesContainer to_data() const {
			Ipv6::Addr ip_bytes = to_bitset();
			return convert_big_endian<Ipv6::ADDR_LENGTH_IN_BYTES>(ip_bytes);
		}

		Ipv6::Addr to_bitset() const {
			std::vector<unsigned short> ip_nums = split_numerics<unsigned short>( ip, std::string(".") );
			if( ip_nums.size() != Ipv6::ADDR_LENGTH_IN_BYTES) {
#ifdef LOGGING
				LOG(ERROR) << "Could not convert ip address ["<< ip <<"]";
#endif
				return Ipv6::Addr();
			}

			typedef std::bitset<BITS_PER_BYTE> Byte;
			Byte byte;
			Ipv6::Addr ip_bytes;
			for( size_t i = 0; i < Ipv6::ADDR_LENGTH_IN_BYTES; ++i ) {
				byte = Byte(ip_nums[i]);
				copy_into(ip_bytes, byte, BITS_PER_BYTE * reverse_index(i, +Ipv6::ADDR_LENGTH_IN_BYTES));
			}

			return ip_bytes;

		}

		virtual ~Ipv6AddrConvert() { }

	private:
		std::string ip;

};

#endif /* !IPv6_ADDR_CONVERT_H */

