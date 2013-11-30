/*
 * ethernet_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ETHERNET_8023_BUILDER_H
#define ETHERNET_8023_BUILDER_H

#include "ethernet802.3.h"
#include "ptr_types.h"

#include "networkmuncher/util/byte/byte.h"
#include "ethernet_builder.h"

class Ethernet8023Builder : public EthernetBuilder {

	public:

		// TODO fix return types
		EthernetBuilder& set_type(Ethernet::Extra type_field) {
			return set_extra(type_field);
		}

		virtual Ethernet build() {
			set_default_fields();
			return Ethernet8023(extra, dest, src);
		}

		virtual EthernetPtr build_ptr() {
			set_default_fields();
			return EthernetPtr( new Ethernet8023(extra, dest, src) );
		}

};

#endif /* !ETHERNET_8023_BUILDER_H */

