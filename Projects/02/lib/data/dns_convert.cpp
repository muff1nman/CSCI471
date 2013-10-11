/*
 * dns_convert.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/config.h"
#include "dnsmuncher/data/dns_convert.h"
#include <cstring>
#ifdef LOGGING
#include <glog/logging.h>
#endif

DNSConvert::DNSConvert(boost::shared_ptr<DNS> dns) : dns(dns) {
	// TODO
}

BytesContainer DNSConvert::to_data() const {
	BytesContainer c;
	c = convert_big_endian<2>(this->dns->id);
	return c;
}



