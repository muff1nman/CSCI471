/*
 * ip_addr_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IP_ADDR_CONVERT_H
#define IP_ADDR_CONVERT_H

#include "convert.h"

#include "networkmuncher/domain/ip_addr.h"

#include "networkmuncher/util/logging.h"

#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/byte/copy.h"
#include "networkmuncher/util/byte/convert.h"
#include "networkmuncher/util/index.h"
#include "networkmuncher/util/split.h"

/**
 * Handy class that will convert your ips to a binary representation.
 *
 * If something goes wrong, return an empty container.
 */
class IpAddrConvert : public Convert {
	public:
		IpAddrConvert(IpAddr ip) : ip(ip) { }

		typedef std::bitset<IP_ADDR::BYTE_LENGTH * BITS_PER_BYTE> IpAddrBytes;

		virtual BytesContainer to_data() const {
			IpAddrBytes ip_bytes = to_bitset();
			return convert_big_endian<IP_ADDR::BYTE_LENGTH>(ip_bytes);
		}

		IpAddrBytes to_bitset() const {
			std::vector<unsigned short> ip_nums = split_numerics<unsigned short>( ip, std::string(".") );
			if( ip_nums.size() != IP_ADDR::BYTE_LENGTH ) {
#ifdef LOGGING
				LOG(ERROR) << "Could not convert ip address ["<< ip <<"]";
#endif
				return IpAddrBytes();
			}

			typedef std::bitset<BITS_PER_BYTE> Byte;
			Byte byte;
			IpAddrBytes ip_bytes;
			for( size_t i = 0; i < IP_ADDR::BYTE_LENGTH; ++i ) {
				byte = Byte(ip_nums[i]);
				copy_into(ip_bytes, byte, BITS_PER_BYTE * reverse_index(i, IP_ADDR::BYTE_LENGTH));
			}

			return ip_bytes;

		}

		virtual ~IpAddrConvert() { }

	private:
		IpAddr ip;

};

#endif /* !IP_ADDR_CONVERT_H */

