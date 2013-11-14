/*
 * ip_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IP_CONVERT_H
#define IP_CONVERT_H

#include "networkmuncher/data/convert.h"
#include "icmp/domain/domain.h"
#include "networkmuncher/util/join.h"
#include "networkmuncher/util/byte/convert.h"
#include "networkmuncher/util/byte/copy.h"

class IpConvert : public Convert {
	public:
		IpConvert(IpPtr ptr) : ip(ptr) { }

		virtual BytesContainer to_data() const {
			BytesContainer bytes;

			std::bitset<Ip::VERSION_LENGTH + Ip::HEADER_LENGTH_LENGTH> temp_byte;
			copy_into(temp_byte, ip->version, Ip::HEADER_LENGTH_LENGTH);
			copy_into(temp_byte, ip->header_length, 0);
			join(bytes, convert_big_endian
					<(Ip::VERSION_LENGTH + Ip::HEADER_LENGTH_LENGTH) / BITS_PER_BYTE>
					(temp_byte));

			join(bytes, convert_big_endian
					<Ip::TOS_LENGTH / BITS_PER_BYTE>
					(ip->tos));

			join(bytes, convert_big_endian
					<Ip::TOTAL_LENGTH_LENGTH / BITS_PER_BYTE>
					(ip->total_length));

			join(bytes, convert_big_endian
					<Ip::ID_LENGTH / BITS_PER_BYTE>
					(ip->id));

			std::bitset<Ip::FLAGS_LENGTH + Ip::FRAG_OFFSET_LENGTH> temp_byte_2;
			copy_into(temp_byte_2, ip->flags, Ip::FRAG_OFFSET_LENGTH);
			copy_into(temp_byte_2, ip->frag_offset, 0);
			join(bytes, convert_big_endian
					<(Ip::FLAGS_LENGTH + Ip::FRAG_OFFSET_LENGTH) / BITS_PER_BYTE>
					(temp_byte_2));

			join(bytes, convert_big_endian
					<Ip::TTL_LENGTH / BITS_PER_BYTE>
					(ip->ttl));

			join(bytes, convert_big_endian
					<Ip::PROTOCOL_LENGTH / BITS_PER_BYTE>
					(ip->protocol));

			join(bytes, convert_big_endian
					<Ip::CHECKSUM_LENGTH / BITS_PER_BYTE>
					(ip->checksum));

			join(bytes, convert_big_endian
					<Ip::SOURCE_ADDR_LENGTH / BITS_PER_BYTE>
					(ip->source_addr));

			join(bytes, convert_big_endian
					<Ip::DEST_ADDR_LENGTH / BITS_PER_BYTE>
					(ip->dest_addr));


			// options would go here

			return bytes;

		}

	private:
		IpPtr ip;
};

#endif /* !IP_CONVERT_H */

