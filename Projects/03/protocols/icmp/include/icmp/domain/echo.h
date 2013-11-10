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
	static const size_t TYPE_LENGTH         = 8;
	static const size_t CODE_LENGTH         = 8;
	static const size_t CHECKSUM_LENGTH     = 16;
	static const size_t IDENTIFIER_LENGTH   = 16;
	static const size_t SEQUENCE_NUM_LENGTH = 16;

	std::bitset<TYPE_LENGTH>           type;
	std::bitset<CODE_LENGTH>           code;
	std::bitset<CHECKSUM_LENGTH>       checksum;
	std::bitset<IDENTIFIER_LENGTH>     identifier;
	std::bitset<SEQUENCE_NUM_LENGTH>   sequence_num;
	BytesContainer                     data;
	
}

#endif /* !DOMAIN_ECHO_H */

