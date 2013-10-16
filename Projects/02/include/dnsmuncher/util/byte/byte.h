/*
 * byte.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __byte_h__
#define __byte_h__

#include <bitset>
#include <string>
#include <vector>

#include "dnsmuncher/util/logging.h"

#define BITS_PER_BYTE 8

typedef unsigned char Byte;
typedef std::vector<Byte> BytesContainer;

typedef unsigned int generic_number;
typedef unsigned short opcode_number;
typedef unsigned int ttl_number;
typedef unsigned int rdata_length_number;

#endif /* !__byte_h__ */

