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

boost::shared_ptr<DNS> response_cname_amazon() {
	BytesContainer a1 = boost::assign::list_of
('\x03') ('\x77') ('\x77') ('\x77') ('\x0D') ('\x61') ('\x6E') ('\x64') ('\x72') ('\x65') ('\x77') ('\x64') ('\x65') ('\x6D') ('\x61') ('\x72') ('\x69') ('\x61') ('\x03') ('\x63') ('\x6F') ('\x6D') ('\x14') ('\x73') ('\x33') ('\x2D') ('\x77') ('\x65') ('\x62') ('\x73') ('\x69') ('\x74') ('\x65') ('\x2D') ('\x75') ('\x73') ('\x2D') ('\x77') ('\x65') ('\x73') ('\x74') ('\x2D') ('\x32') ('\x09') ('\x61') ('\x6D') ('\x61') ('\x7A') ('\x6F') ('\x6E') ('\x61') ('\x77') ('\x73') ('\xC0') ('\x1E');
	ResourceRecord r1("www.andrewdemaria.com", a1, 5, NetClass::IN, 5*60, 55);

	BytesContainer a2 = boost::assign::list_of
('\x07') ('\x6E') ('\x73') ('\x2D') ('\x31') ('\x34') ('\x39') ('\x32') ('\x09') ('\x61') ('\x77') ('\x73') ('\x64') ('\x6E') ('\x73') ('\x2D') ('\x35') ('\x38') ('\x03') ('\x6F') ('\x72') ('\x67') ('\x00');
	ResourceRecord r2("andrewdemaria.com", a2, Type::NS, NetClass::IN, 2 * 24 * 60 * 60, 23);

	BytesContainer a3 = boost::assign::list_of
('\x07') ('\x6E') ('\x73') ('\x2D') ('\x31') ('\x35') ('\x39') ('\x39') ('\x09') ('\x61') ('\x77') ('\x73') ('\x64') ('\x6E') ('\x73') ('\x2D') ('\x30') ('\x37') ('\x02') ('\x63') ('\x6F') ('\x02') ('\x75') ('\x6B') ('\x00');
	ResourceRecord r3("andrewdemaria.com", a3, Type::NS, NetClass::IN, 2 * 24 * 60 * 60, 25);

	BytesContainer a4 = boost::assign::list_of
('\x06') ('\x6E') ('\x73') ('\x2D') ('\x32') ('\x38') ('\x32') ('\x09') ('\x61') ('\x77') ('\x73') ('\x64') ('\x6E') ('\x73') ('\x2D') ('\x33') ('\x35') ('\xC0') ('\x1E');
	ResourceRecord r4("andrewdemaria.com", a4, Type::NS, NetClass::IN, 2 * 24 * 60 * 60, 19);

	BytesContainer a5 = boost::assign::list_of
('\x06') ('\x6E') ('\x73') ('\x2D') ('\x37') ('\x33') ('\x34') ('\x09') ('\x61') ('\x77') ('\x73') ('\x64') ('\x6E') ('\x73') ('\x2D') ('\x32') ('\x37') ('\x03') ('\x6E') ('\x65') ('\x74') ('\x00');
	ResourceRecord r5("andrewdemaria.com", a5, Type::NS, NetClass::IN, 2 * 24 * 60 * 60, 22);

	return DNSBuilder().
		set_id(234).
		is_response().
		authoritative_bit(true).
		recursion_desired(true).
		question_count(1).
		answer_count(1).
		nameserver_count(4).
		add_question( Question("www.andrewdemaria.com", Type::CNAME, NetClass::IN)).
		add_resource( r1 ).
		add_resource( r2 ).
		add_resource( r3 ).
		add_resource( r4 ).
		add_resource( r5 ).
		build_ptr();
}

boost::shared_ptr<DNS> response_nameserver_amazon() {

	return DNSBuilder().
		set_id(0).
		is_response().
		question_count(1).
		nameserver_count(8).
		additional_count(8).
		add_question( Question("www.amazon.com", Type::NS, NetClass::IN)).
		add_resource( 
				ResourceRecord("www.amazon.com", boost::assign::list_of
('\x06')('\x6e')('\x73')('\x2d')('\x39')('\x32')('\x32')('\xc0')('\x10'),
Type::NS, NetClass::IN, 3655, 9) ).
		add_resource( 
				ResourceRecord("www.amazon.com", boost::assign::list_of
('\x06')('\x6e')('\x73')('\x2d')('\x39')('\x32')('\x34')('\xc0')('\x10'),
Type::NS, NetClass::IN, 3655, 9) ).
		add_resource( 
				ResourceRecord("www.amazon.com", boost::assign::list_of
('\x06')('\x6e')('\x73')('\x2d')('\x39')('\x34')('\x31')('\xc0')('\x10'),
Type::NS, NetClass::IN, 3655, 9) ).
		add_resource( 
				ResourceRecord("www.amazon.com", boost::assign::list_of
('\x06')('\x6e')('\x73')('\x2d')('\x39')('\x34')('\x32')('\xc0')('\x10'),
Type::NS, NetClass::IN, 3655, 9) ).
		add_resource( 
				ResourceRecord("www.amazon.com", boost::assign::list_of
('\x06')('\x6e')('\x73')('\x2d')('\x39')('\x32')('\x33')('\xc0')('\x10'),
Type::NS, NetClass::IN, 3655, 9) ).
		add_resource( 
				ResourceRecord("www.amazon.com", boost::assign::list_of
('\x06')('\x6e')('\x73')('\x2d')('\x39')('\x32')('\x31')('\xc0')('\x10'),
Type::NS, NetClass::IN, 3655, 9) ).
		add_resource( 
				ResourceRecord("www.amazon.com", boost::assign::list_of
('\x06')('\x6e')('\x73')('\x2d')('\x39')('\x31')('\x31')('\xc0')('\x10'),
Type::NS, NetClass::IN, 3655, 9) ).
		add_resource( 
				ResourceRecord("www.amazon.com", boost::assign::list_of
('\x06')('\x6e')('\x73')('\x2d')('\x39')('\x31')('\x32')('\xc0')('\x10'),
Type::NS, NetClass::IN, 3655, 9) ).

		add_resource( 
				ResourceRecord("ns-911.amazon.com", boost::assign::list_of
('\xcf')('\xab')('\xb2')('\x06'),
Type::A, NetClass::IN, 900, 4) ).
		add_resource( 
				ResourceRecord("ns-912.amazon.com", boost::assign::list_of
('\xcc')('\xf6')('\xa2')('\x05'),
Type::A, NetClass::IN, 600, 4) ).
		add_resource( 
				ResourceRecord("ns-921.amazon.com", boost::assign::list_of
('\x48')('\x15')('\xc0')('\xd7'),
Type::A, NetClass::IN, 600, 4) ).
		add_resource( 
				ResourceRecord("ns-922.amazon.com", boost::assign::list_of
('\x48')('\x15')('\xc0')('\xd3'),
Type::A, NetClass::IN, 900, 4) ).
		add_resource( 
				ResourceRecord("ns-923.amazon.com", boost::assign::list_of
('\x48')('\x15')('\xd0')('\xd7'),
Type::A, NetClass::IN, 900, 4) ).
		add_resource( 
				ResourceRecord("ns-924.amazon.com", boost::assign::list_of
('\x48')('\x15')('\xd0')('\xd7'),
Type::A, NetClass::IN, 600, 4) ).
		add_resource( 
				ResourceRecord("ns-941.amazon.com", boost::assign::list_of
('\xcc')('\xf6')('\xa0')('\x05'),
Type::A, NetClass::IN, 900, 4) ).
		add_resource( 
				ResourceRecord("ns-942.amazon.com", boost::assign::list_of
('\xcc')('\xf6')('\xa0')('\x07'),
Type::A, NetClass::IN, 900, 4) ).
		build_ptr();

}

#endif /* !__dns_common_h__ */

