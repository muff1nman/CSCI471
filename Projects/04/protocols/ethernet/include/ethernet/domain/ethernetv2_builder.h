/*
 * ethernet_builder.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ETHERNET_v2_BUILDER_H
#define ETHERNET_v2_BUILDER_H

#include "ethernetv2.h"
#include "ptr_types.h"

#include "networkmuncher/util/byte/byte.h"
#include "ethernet_builder.h"

class Ethernetv2Builder : public EthernetBuilder {

	public:

		// TODO fix return types
		EthernetBuilder& set_type(Ethernet::Extra type_field) {
			return set_extra(type_field);
		}

		Ethernet build() {
			set_default_fields();
			return Ethernetv2(extra, dest, src);
		}

		EthernetPtr build_ptr() {
			set_default_fields();
			return EthernetPtr( new Ethernetv2(extra, dest, src) );
		}

};

#endif /* !ETHERNET_v2_BUILDER_H */

