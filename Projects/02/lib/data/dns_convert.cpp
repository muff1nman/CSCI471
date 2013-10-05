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
	const char* data = "HelloWorld";
#ifdef LOGGING
	LOG(INFO) << "Is it a query? " << this->dns->qr;
#endif
	BytesContainer c;
	c.data = Bytes( new Byte[strlen(data)] );
	strcpy(reinterpret_cast<char*>(c.data.get()), data);
	c.data.get()[0] = (Byte) this->dns->qr;
	c.size = strlen(data);
#ifdef LOGGING
	LOG(INFO) << "Estimated message size: " << c.size;
#endif
	return c;
}



