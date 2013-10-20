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
	BytesContainer a1 =  boost::assign::list_of('\x4a')('\x7d')('\xe1')('\xd3');
	BytesContainer a2 =  boost::assign::list_of('\x4a')('\x7d')('\xe1')('\xd2');
	BytesContainer a3 =  boost::assign::list_of('\x4a')('\x7d')('\xe1')('\xd4');
	BytesContainer a4 =  boost::assign::list_of('\x4a')('\x7d')('\xe1')('\xd0');
	BytesContainer a5 =  boost::assign::list_of('\x4a')('\x7d')('\xe1')('\xd1');

	return DNSBuilder().
		set_id(45350).
		is_response().
		recursion_desired(true).
		recursion_available().
		zeros(std::bitset<DNS::Z_FIELD_LENGTH>(2)).
		question_count(1).
		add_question( Question("www.google.com")).
		add_resource( ResourceRecord("www.google.com", a1, Type::A, NetClass::IN, 183, 4) ).
		add_resource( ResourceRecord("www.google.com", a2, Type::A, NetClass::IN, 183, 4) ).
		add_resource( ResourceRecord("www.google.com", a3, Type::A, NetClass::IN, 183, 4) ).
		add_resource( ResourceRecord("www.google.com", a4, Type::A, NetClass::IN, 183, 4) ).
		add_resource( ResourceRecord("www.google.com", a5, Type::A, NetClass::IN, 183, 4) ).
		answer_count(5).
		build_ptr();
}

boost::shared_ptr<DNS> response_a_intel_without_link() {
	BytesContainer a1 = boost::assign::list_of('\xc6')('\xaf')('\x74')('\x36');
  ResourceRecord r("intel.com", a1, Type::A, NetClass::IN, 19, 4);
	return DNSBuilder().
		set_id(51134).
		is_response().
		recursion_desired(true).
		recursion_available().
		zeros(std::bitset<DNS::Z_FIELD_LENGTH>(2)).
		question_count(1).
		answer_count(1).
		add_question( Question("intel.com") ).
		add_resource( r ).
		build_ptr();
}

boost::shared_ptr<DNS> response_nameserver_google() {
	BytesContainer a1 = boost::assign::list_of
('\x03') ('\x6E') ('\x73') ('\x31') ('\xC0') ('\x10') ('\x09') ('\x64') ('\x6E')
('\x73') ('\x2D') ('\x61') ('\x64') ('\x6D') ('\x69') ('\x6E') ('\xC0') ('\x10')
('\x00') ('\x17') ('\x6F') ('\x53') ('\x00') ('\x00') ('\x1C') ('\x20') ('\x00')
('\x00') ('\x07') ('\x08') ('\x00') ('\x12') ('\x75') ('\x00') ('\x00') ('\x00')
('\x01') ('\x2C');

	ResourceRecord r("google.com", a1, 6, NetClass::IN, 14, 38);
	return DNSBuilder().
		set_id(48908).
		is_response().
		recursion_desired(true).
		recursion_available().
		question_count(1).
		nameserver_count(1).
		add_question( Question("www.google.com", Type::NS, NetClass::IN) ).
		add_resource( r ).
		build_ptr();
}

#endif /* !__dns_common_h__ */

