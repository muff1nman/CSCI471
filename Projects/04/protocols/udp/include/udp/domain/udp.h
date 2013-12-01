/*
 * udp.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef UDP_H
#define UDP_H

#include <bitset>
#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/logging.h"
#include "networkmuncher/domain/all.h"

typedef TransportLayerProtocol InheritedProtocol;
typedef TransportLayerProtocolPtr InheritedProtocolPtr;
typedef TransportLayerProtocolMaybePtr InheritedProtocolMaybePtr;

struct Udp : public InheritedProtocol, public Logging {
	public:

		static const size_t PORT_LENGTH = 16;
		static const size_t LENGTH_LENGTH = 16;
		static const size_t CHECKSUM_LENGTH = 16;

		typedef std::bitset<PORT_LENGTH> Port;
		typedef std::bitset<LENGTH_LENGTH> Length;
		typedef std::bitset<CHECKSUM_LENGTH> Checksum;

		Port dest;
		Port src;
		Length length;
		Checksum checksum;

		friend class UdpBuilder;

		virtual int what_type() const { return PType::Transport::UDP; }

		virtual std::string stringify_object() const {
			std::stringstream object;
			object << "dest: " << dest.to_ulong() << list_sep;
			object << "src: " << src.to_ulong() << list_sep;
			object << "length: " << length.to_ulong() << list_sep;
			object << "checksum: " << checksum.to_string() << sep;
			return object.str();
		}

		bool operator==( const Udp& other ) const {
			return
				dest == other.dest &&
				src == other.src &&
				length == other.length &&
				checksum == other.checksum &&
				true;
		}

		Udp(
				const Port& dest,
				const Port& src,
				const Length& length,
				const Checksum& checksum
			 ) : 
			dest(dest),
			src(src),
			length(length),
			checksum(checksum) { }

	protected:
		Udp() {}


};

#endif /* !UDP_H */

