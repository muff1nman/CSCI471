/*
 * raw.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_DOMAIN_RAW_H
#define ICMP_DOMAIN_RAW_H

#include "ptr_types.h"

struct Raw {
	Raw(IpPtr ip, EchoPtr echo) : ip(ip), echo(echo) { }
	IpPtr ip;
	EchoPtr echo;
};

#endif /* !ICMP_DOMAIN_RAW_H */

