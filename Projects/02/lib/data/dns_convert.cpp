/*
 * dns_convert.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/data/dns_convert.h"
#include <cstring>

BytesContainer DNSConvert::to_data() const {
	const char* data = "HelloWorld";
	BytesContainer c;
	c.data = Bytes( new Byte[sizeof(data)] );
	strcpy(reinterpret_cast<char*>(c.data.get()), data);
	c.size = sizeof(data);
	return c;
}



