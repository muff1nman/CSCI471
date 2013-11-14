/*
 * raw.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_DOMAIN_RAW_H
#define ICMP_DOMAIN_RAW_H

#include "ptr_types.h"
#include "networkmuncher/util/logging.h"

struct Raw : public Logging {
	Raw(IpPtr ip, EchoPtr echo) : ip(ip), echo(echo) { }

	IpPtr ip;
	EchoPtr echo;

	std::string stringify_object() const {
		std::stringstream object;
		object << "Ip: " << nested_start;
		object << ip->to_string() << list_sep;
		object << nested_finish;
		object << "Echo: " << nested_start;
		object << echo->to_string() << list_sep;
		object << nested_finish;
		return object.str();
	}

	bool operator==(const Raw& other) const {
		return ip == other.ip && echo == other.echo;
	}
};

#endif /* !ICMP_DOMAIN_RAW_H */

