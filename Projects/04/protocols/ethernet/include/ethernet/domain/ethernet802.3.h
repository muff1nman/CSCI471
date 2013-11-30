/*
 * ethernet8023.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ETHERNET8023_H
#define ETHERNET8023_H

#include <bitset>
#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/logging.h"
#include "mac_addr.h"

struct Ethernet8023 : public Ethernet {
	public:
	
		friend class EthernetBuilder;

		virtual int what_type() const { return PType::Link::ETHERNET_8023; }

		std::string stringify_object() const {
			std::stringstream object;
			object << "length: " << extra.to_ulong() << list_sep;
			object << "dest: " << dest.to_string() << list_sep;
			object << "src: " << dest.to_string() << sep;
			return object.str();
		}

		Ethernet8023(
				const Ethernet::Extra& extra, 
				const MacAddr& dest,
				const MacAddr& src
				) : Ethernet(extra, dest, src ) {}

};

#endif /* !ETHERNET_H */

