/*
 * udp_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef UDP_BUILDER_H
#define UDP_BUILDER_H

#include "udp.h"
#include "ptr_types.h"

#include "networkmuncher/util/byte/byte.h"
class UdpBuilder {

	public:

		UdpBuilder& set_dest(const Udp::Port& dest) {
			this->dest = dest;
			return do_common();
		}

		UdpBuilder& set_src(const Udp::Port& src) {
			this->src = src;
			return do_common();
		}

		UdpBuilder& set_length(const Udp::Length& length) {
			this->length = length;
			return do_common();
		}

		UdpBuilder& set_checksum(const Udp::Checksum& checksum) {
			this->checksum = checksum;
			return do_common();
		}

		virtual Udp build() {
			set_default_fields();
			return Udp(dest, src, length, checksum);
		}

		virtual UdpPtr build_ptr() {
			set_default_fields();
			return UdpPtr( new Udp(dest,src,length,checksum) );
		}

		virtual ~UdpBuilder() { }

	protected:
		Udp::Port dest;
		Udp::Port src;
		Udp::Length length;
		Udp::Checksum checksum;

		UdpBuilder& do_common() {
			return *this;
		}

		void set_default_fields() {} // TODO, allow length and checksum to be calculated

};

#endif /* !UDP_BUILDER_H */

