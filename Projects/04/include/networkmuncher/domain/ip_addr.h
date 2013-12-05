/*
 * ip_addr.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef DOMAIN_IP_ADDR_H
#define DOMAIN_IP_ADDR_H

#include <string>

typedef std::string IpAddr;

namespace IPV4_ADDR {
	const size_t BYTE_LENGTH = 4;
}

namespace IPV6_ADDR {
	const size_t BYTE_LENGTH = 16;
}

#endif /* !DOMAIN_IP_ADDR_H */

