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
#include "networkmuncher/domain/link_layer_protocol.h"
#include "mac_addr.h"

struct Ethernet : public LinkLayerProtocol, public Logging {
	public:

		static const size_t EXTRA_LENGTH = 16;
		typedef std::bitset<EXTRA_LENGTH> Extra;

		Extra extra;
		MacAddr dest;
		MacAddr src;

		friend class EthernetBuilder;

		virtual int what_type() const { return PType::Link::ETHERNET_UNKNOWN; }

		virtual std::string stringify_object() const {
			std::stringstream object;
			object << "extra: " << extra.to_ulong() << list_sep;
			object << "dest: " << dest.to_string() << list_sep;
			object << "src: " << dest.to_string() << sep;
			return object.str();
		}

		bool operator==( const Ethernet& other ) const {
			return
				extra == other.extra &&
				dest == other.dest &&
				src == other.src &&
				true;
		}

		Ethernet(
				const Extra& extra, 
				const MacAddr& dest,
				const MacAddr& src
				) : 
					extra(extra),
					dest(dest),
					src(src) 
				{}

	protected:
		Ethernet() {}


};

#endif /* !ETHERNET_H */

