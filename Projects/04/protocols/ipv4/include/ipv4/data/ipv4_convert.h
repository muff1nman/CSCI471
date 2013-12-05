/*
 * ipv4_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IPV4_CONVERT_H
#define IPV4_CONVERT_H

#include "networkmuncher/data/convert.h"
#include "ipv4/domain/domain.h"
#include "networkmuncher/util/join.h"
#include "networkmuncher/util/byte/convert.h"
#include "networkmuncher/util/byte/copy.h"
#include "networkmuncher/util/byte/print.h"
#include "networkmuncher/util/logging.h"

class Ipv4Convert : public Convert {
	public:
		Ipv4Convert(Ipv4Ptr ptr) : ipv4(ptr) { }

		virtual BytesContainer to_data() const {
			BytesContainer bytes;

			std::bitset<Ipv4::VERSION_LENGTH + Ipv4::HEADER_LENGTH_LENGTH> temp_byte;
			copy_into(temp_byte, ipv4->version, Ipv4::HEADER_LENGTH_LENGTH);
			copy_into(temp_byte, ipv4->header_length, 0);
			bytes = join(bytes, convert_big_endian
					<(Ipv4::VERSION_LENGTH + Ipv4::HEADER_LENGTH_LENGTH) / BITS_PER_BYTE>
					(temp_byte));

			bytes = join(bytes, convert_big_endian
					<Ipv4::TOS_LENGTH / BITS_PER_BYTE>
					(ipv4->tos));

			bytes = join(bytes, convert_big_endian
					<Ipv4::TOTAL_LENGTH_LENGTH / BITS_PER_BYTE>
					(ipv4->total_length));

			bytes = join(bytes, convert_big_endian
					<Ipv4::ID_LENGTH / BITS_PER_BYTE>
					(ipv4->id));

			std::bitset<Ipv4::FLAGS_LENGTH + Ipv4::FRAG_OFFSET_LENGTH> temp_byte_2;
			copy_into(temp_byte_2, ipv4->flags, Ipv4::FRAG_OFFSET_LENGTH);
			copy_into(temp_byte_2, ipv4->frag_offset, 0);
			bytes = join(bytes, convert_big_endian
					<(Ipv4::FLAGS_LENGTH + Ipv4::FRAG_OFFSET_LENGTH) / BITS_PER_BYTE>
					(temp_byte_2));

			bytes = join(bytes, convert_big_endian
					<Ipv4::TTL_LENGTH / BITS_PER_BYTE>
					(ipv4->ttl));

			bytes = join(bytes, convert_big_endian
					<Ipv4::PROTOCOL_LENGTH / BITS_PER_BYTE>
					(ipv4->protocol));

			bytes = join(bytes, convert_big_endian
					<Ipv4::CHECKSUM_LENGTH / BITS_PER_BYTE>
					(ipv4->checksum));

			bytes = join(bytes, convert_big_endian
					<Ipv4::ADDR_LENGTH / BITS_PER_BYTE>
					(ipv4->source_addr));

			bytes = join(bytes, convert_big_endian
					<Ipv4::ADDR_LENGTH / BITS_PER_BYTE>
					(ipv4->dest_addr));


			// options would go here

			return bytes;

		}

	private:
		Ipv4Ptr ipv4;
};

#endif /* !IPV4_CONVERT_H */

