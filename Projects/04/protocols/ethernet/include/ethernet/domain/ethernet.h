/*
 * ethernet.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ETHERNET_H
#define ETHERNET_H

#include <bitset>
#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/logging.h"
#include "mac_addr.h"

struct Ethernet : public Logging {
	public:

		static const size_t EXTRA_LENGTH = 16;
		typedef std::bitset<EXTRA_LENGTH> Extra;

		Extra extra;
		MacAddr dest;
		MacAddr src;

		friend class EthernetBuilder;

		virtual std::string stringify_object() const {
			std::stringstream object;
			object << "extra: " << extra.to_ulong() << list_sep;
			object << "dest: " << dest.to_string() << list_sep;
			object << "src: " << dest.to_string() << sep;
			return object.str();
		}

		bool operator==( const Ethernet& other ) const {
			return
				extra   ==   other.extra   &&
				dest   ==   other.dest   &&
				src    ==   other.src    &&
				true;
		}

	protected:
		Ethernet() {}


};

#endif /* !ETHERNET_H */

