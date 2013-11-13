/*
 * echo.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef DOMAIN_ECHO_H
#define DOMAIN_ECHO_H

#include "networkmuncher/util/byte/byte.h"

struct Echo {
	public:
		static const size_t TYPE_LENGTH         = 8;
		static const size_t CODE_LENGTH         = 8;
		static const size_t CHECKSUM_LENGTH     = 16;
		static const size_t IDENTIFIER_LENGTH   = 16;
		static const size_t SEQUENCE_NUM_LENGTH = 16;

		typedef std::bitset<TYPE_LENGTH>           Type;
		typedef std::bitset<CODE_LENGTH>           Code;
		typedef std::bitset<CHECKSUM_LENGTH>       Checksum;
		typedef std::bitset<IDENTIFIER_LENGTH>     Identifier;
		typedef std::bitset<SEQUENCE_NUM_LENGTH>   SequenceNum;
		typedef BytesContainer                     Data;

		Type          type;
		Code          code;
		Checksum      checksum;
		Identifier    identifier;
		SequenceNum   sequence_num;
		Data          data;

		friend class EchoBuilder;

	protected:
		Echo() { }

};

#endif /* !DOMAIN_ECHO_H */

