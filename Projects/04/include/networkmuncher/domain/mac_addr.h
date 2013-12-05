/*
 * mac_addr.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef MAC_ADDR_H
#define MAC_ADDR_H

#include <bitset>

#include "networkmuncher/util/logging.h"
#include "networkmuncher/util/byte/byte.h"

static const size_t MAC_ADDR_LENGTH = 6 * BITS_PER_BYTE;

typedef std::bitset<MAC_ADDR_LENGTH> MacAddr;

#endif /* !MAC_ADDR_H */

