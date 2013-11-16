/*
 * echo_convert.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ECHO_CONVERT_H
#define ECHO_CONVERT_H

#include "networkmuncher/data/convert.h"
#include "icmp/domain/domain.h"
#include "networkmuncher/util/join.h"
#include "networkmuncher/util/byte/convert.h"
#include <boost/assign.hpp>

class EchoConvert : public Convert {
	public:
		EchoConvert(EchoPtr ptr) : echo(ptr) { }

		virtual BytesContainer to_data() const {
			BytesContainer bytes;

			bytes = join(bytes, convert_big_endian
					<Echo::TYPE_LENGTH / BITS_PER_BYTE>
					(echo->type));

			bytes = join(bytes, convert_big_endian
					<Echo::CODE_LENGTH / BITS_PER_BYTE>
					(echo->code));

			bytes = join(bytes, convert_big_endian
					<Echo::CHECKSUM_LENGTH / BITS_PER_BYTE>
					(echo->checksum));

			bytes = join(bytes, convert_big_endian
					<Echo::IDENTIFIER_LENGTH / BITS_PER_BYTE>
					(echo->identifier));

			bytes = join(bytes, convert_big_endian
					<Echo::SEQUENCE_NUM_LENGTH / BITS_PER_BYTE>
					(echo->sequence_num));

			bytes = join(bytes, echo->data);

			BytesContainer extra_bytes = boost::assign::list_of
				('\x01')
				('\x02')
				('\x03')
				('\x04')
				('\x05')
				('\x06')
				('\x07')
				('\x08')
				('\x09')
				('\x0a')
				('\x10')
				('\x11')
				('\x12')
				('\x13')
				('\x14')
				('\x15')
				('\x16')
				('\x17')
				('\x1a')
				('\x20')
				('\x21')
				('\x22')
				('\x23')
				('\x24')
				('\x25')
				('\x26')
				('\x27')
				('\x2a')
				('\x3a')
				('\x4a')
				('\x5a')
				('\x6a')
				('\x7a')
				('\x8a')
				('\x9a');
			bytes = join(bytes, extra_bytes);

			return bytes;

		}

	private:
		EchoPtr echo;
};

#endif /* !ECHO_CONVERT_H */

