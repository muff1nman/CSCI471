/*
 * ethernet_helper.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ETHERNET_HELPER_H
#define ETHERNET_HELPER_H

#include "test_helper.h"

EthernetPtr ethernet_v2() {
	return EthernetBuilder()
		.set_extra(2048)
		.set_dest_addr(MacAddr(long(169648158992140)))
		.set_source_addr(MacAddr(long(83629160365664)))
		.build_ptr();
}

#endif /* !ETHERNET_HELPER_H */

