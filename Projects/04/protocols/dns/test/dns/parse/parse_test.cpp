/*
 * parse_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "test_helper.h"
#include "file_names.h"
#include "dns_common.h"

#include "dns/parse/dns.h"

#include <boost/assign/list_of.hpp>

TEST(ParseBytesFile, Helper) {
	const BytesContainer test = boost::assign::list_of 
		('\x73') ('\xcc') ('\x01') ('\x00') ('\x00') ('\x01') ('\x00') ('\x00')
		('\x00') ('\x00') ('\x00') ('\x00') ('\x03') ('\x77') ('\x77') ('\x77')
		('\x06') ('\x67') ('\x6f') ('\x6f') ('\x67') ('\x6c') ('\x65') ('\x03')
		('\x63') ('\x6f') ('\x6d') ('\x00') ('\x00') ('\x01') ('\x00') ('\x01');
	EXPECT_EQ( test, bytes_from_file( QUERY_A_GOOGLE ));
}

TEST(ParseDNS, SimpleQuery) {
	EXPECT_EQ( *query_a_google_obj(), *from_data(bytes_from_file( QUERY_A_GOOGLE )));
}

TEST(ParseDNS, SimpleResponse) {
	EXPECT_EQ( *response_a_intel_without_link(), *from_data(bytes_from_file( RESPONSE_A_INTEL_WITHOUT_LINK )));
}

TEST(ParseDNS, ComplexResponse) {
	EXPECT_EQ( *response_complex_google(), *from_data(bytes_from_file( RESPONSE_COMPLEX_GOOGLE )));
}

TEST(ParseDNS, NameserverResponse) {
	EXPECT_EQ( *response_nameserver_google(), *from_data(bytes_from_file( RESPONSE_NAMESERVER_GOOGLE )));
}

TEST(ParseDNS, CnameResponse) {
	EXPECT_EQ( *response_cname_amazon(), *from_data(bytes_from_file( RESPONSE_CNAME_AMAZON )));
}

TEST(ParseDNS, NameserverAmazonResponse) {
	EXPECT_EQ( *response_nameserver_amazon(), *from_data(bytes_from_file( RESPONSE_NAMESERVER_AMAZON )));
}

// TODO test for root query

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
#ifdef LOGGING
	google::InitGoogleLogging( PROJECT_NAME "-" "TestParse");
	FLAGS_minloglevel = TEST_LOG_LEVEL;
	FLAGS_alsologtostderr = 1;
	FLAGS_colorlogtostderr = 1;
#endif
  return RUN_ALL_TESTS();
}
