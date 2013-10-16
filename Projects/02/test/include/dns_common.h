/*
 * dns_common.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_common_h__
#define __dns_common_h__

#include "dnsmuncher/domain/dns.h"
#include "dnsmuncher/domain/dns_builder.h"
#include <boost/shared_ptr.hpp>

boost::shared_ptr<DNS> query_a_google_obj() {	
	return DNSBuilder().
		set_id(29644).
		recursion_desired(true).
		question_count( 1 ).
		add_question( Question("www.google.com") ).
		build_ptr();
}

#endif /* !__dns_common_h__ */

