/*
 * ethernetv2.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ETHERNETV2_H
#define ETHERNETV2_H

#include <bitset>
#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/logging.h"
#include "mac_addr.h"

struct Ethernetv2 : public Ethernet {
	public:
	
		friend class EthernetBuilder;

		std::string stringify_object() const {
			std::stringstream object;
			object << "type: " << type.to_ulong() << list_sep;
			object << "dest: " << dest.to_string() << list_sep;
			object << "src: " << dest.to_string() << sep;
			return object.str();
		}

};

#endif /* !ETHERNET_H */

