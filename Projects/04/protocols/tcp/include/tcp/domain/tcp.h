/*
 * tcp.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef TCP_H
#define TCP_H

#include <bitset>
#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/logging.h"
#include "networkmuncher/domain/network_layer_protocol.h"

struct Tcp : public NetworkLayerProtocol, public Logging {
	public:

		static const size_t EXTRA_LENGTH = 16;
		typedef std::bitset<EXTRA_LENGTH> Extra;

		Extra extra;
		MacAddr dest;
		MacAddr src;

		friend class TcpBuilder;

		virtual int what_type() const { return PType::Link::TCP_UNKNOWN; }

		virtual std::string stringify_object() const {
			std::stringstream object;
			object << "extra: " << extra.to_ulong() << list_sep;
			object << "dest: " << dest.to_string() << list_sep;
			object << "src: " << dest.to_string() << sep;
			return object.str();
		}

		bool operator==( const Tcp& other ) const {
			return
				extra == other.extra &&
				dest == other.dest &&
				src == other.src &&
				true;
		}

		Tcp(
				const Extra& extra, 
				const MacAddr& dest,
				const MacAddr& src
				) : 
					extra(extra),
					dest(dest),
					src(src) 
				{}

	protected:
		Tcp() {}


};

#endif /* !TCP_H */

