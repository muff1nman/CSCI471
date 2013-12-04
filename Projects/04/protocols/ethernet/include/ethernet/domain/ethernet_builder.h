/*
 * ethernet_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ETHERNET_BUILDER_H
#define ETHERNET_BUILDER_H

#include "ethernet.h"
#include "ptr_types.h"

#include "networkmuncher/util/byte/byte.h"
class EthernetBuilder {

	public:

		static const long TYPE_IP = 2048;

		EthernetBuilder& set_extra(Ethernet::Extra extra_field) {
			extra = extra_field;
			extra_set = true;
			return do_common();
		}

		EthernetBuilder& set_source_addr(MacAddr addr) {
			src = addr;
			source_addr_set = true;
			return do_common();
		}

		EthernetBuilder& set_dest_addr(MacAddr addr) {
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

		virtual Ethernet build() {
			set_default_fields();
			return Ethernet(extra, dest, src);
		}

		virtual EthernetPtr build_ptr() {
			set_default_fields();
			return EthernetPtr( new Ethernet(extra, dest, src) );
		}

		virtual ~EthernetBuilder() { };

	protected:
		Ethernet::Extra extra;
		MacAddr dest;
		MacAddr src;

		EthernetBuilder& do_common() {
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

#endif /* !ETHERNET_BUILDER_H */

