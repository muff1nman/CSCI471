/*
 * ethernet_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef IP_BUILDER_H
#define IP_BUILDER_H

#include "ethernet.h"
#include "ptr_types.h"

#include "networkmuncher/util/byte/byte.h"
class EthernetBuilder {

	public:

		static const long TYPE_IP = 2048;

		EthernetBuilder& set_type(Ethernet::Extra extra_field) {
			variable_holder.extra = extra_field;
			extra_set = true;
			return do_common();
		}

		EthernetBuilder& set_source_addr(MacAddr addr) {
			variable_holder.src = addr;
			source_addr_set = true;
			return do_common();
		}

		EthernetBuilder& set_dest_addr(MacAddr addr) {
			variable_holder.dest = addr;
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

		Ethernet build() {
			set_default_fields();
			return Ethernet(variable_holder);
		}

		EthernetPtr build_ptr() {
			set_default_fields();
			return EthernetPtr( new Ethernet(variable_holder) );
		}

	private:
		Ethernet variable_holder;

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

#endif /* !IP_BUILDER_H */

