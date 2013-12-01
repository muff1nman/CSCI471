/*
 * tcp_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IP_BUILDER_H
#define IP_BUILDER_H

#include "tcp.h"
#include "ptr_types.h"

#include "networkmuncher/util/byte/byte.h"
class TcpBuilder {

	public:

		static const long TYPE_IP = 2048;

		TcpBuilder& set_extra(Tcp::Extra extra_field) {
			extra = extra_field;
			extra_set = true;
			return do_common();
		}

		TcpBuilder& set_source_addr(MacAddr addr) {
			src = addr;
			source_addr_set = true;
			return do_common();
		}

		TcpBuilder& set_dest_addr(MacAddr addr) {
			dest = addr;
			dest_addr_set = true;
			return do_common();
		}


		bool is_valid() {
			return 
				extra_set &&
				source_addr_set &&
				dest_addr_set &&
				true; // why? cause I wanted the three lines above nice and symmetric :)
		}

		virtual Tcp build() {
			set_default_fields();
			return Tcp(extra, dest, src);
		}

		virtual TcpPtr build_ptr() {
			set_default_fields();
			return TcpPtr( new Tcp(extra, dest, src) );
		}

	protected:
		Tcp::Extra extra;
		MacAddr dest;
		MacAddr src;

		TcpBuilder& do_common() {
			return *this;
		}

		void set_default_fields() {}

		/* 
		 * Keep track of which varibles have been set
		 */
		bool
			extra_set, 
			dest_addr_set,
			source_addr_set;

};

#endif /* !IP_BUILDER_H */

