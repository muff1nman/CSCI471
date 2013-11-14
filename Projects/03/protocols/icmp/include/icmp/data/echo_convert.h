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

			return bytes;

		}

	private:
		EchoPtr echo;
};

#endif /* !ECHO_CONVERT_H */

