/*
 * dns_common.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __dns_common_h__
#define __dns_common_h__

#include "dnsmuncher/util/logging.h"
#include <iostream>
#include "dnsmuncher/domain/dns.h"
#include "dnsmuncher/domain/dns_builder.h"
#include <boost/shared_ptr.hpp>
#include <boost/assign/list_of.hpp>

boost::shared_ptr<DNS> query_a_google_obj() {	
	return DNSBuilder().
		set_id(29644).
		recursion_desired(true).
		is_query().
		question_count( 1 ).
		add_question( Question("www.google.com") ).
		build_ptr();
}

boost::shared_ptr<DNS> response_complex_google() {
	BytesContainer a1 =  boost::assign::list_of('\x4a')('\x7d')('\xe1')('\xe3');

	return DNSBuilder().
		set_id(45350).
		is_response().
		recursion_desired(true).
		recursion_available().
		zeros(std::bitset<DNS::Z_FIELD_LENGTH>(2)).
		question_count(1).
		add_question( Question("www.google.com")).
		add_resource( ResourceRecord("www.google.com", a1, Type::A, NetClass::IN, 183, 4) ).
		answer_count(5).
		build_ptr();
}

#endif /* !__dns_common_h__ */

