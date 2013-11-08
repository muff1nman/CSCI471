/*
 * ip.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __ip_h__
#define __ip_h__

#include <string>
#include "networkmuncher/util/byte/byte.h"

const size_t BYTE_LENGTH = 4;

std::string ip_from_data( const BytesContainer& data );

#endif /* !__ip_h__ */

