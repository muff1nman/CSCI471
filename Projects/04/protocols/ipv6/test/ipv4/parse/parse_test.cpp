/*
 * parse_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "test_helper.h"
#include "ipv6_helper.h"

#include "ipv6/parse/ipv6.h"

TEST(ParseIpv6, GoogleIpv6Request) {
	Ipv6Maybe ipv6 = IPV6::from_data(bytes_from_file(GOOGLE_ECHO_REQUEST_IPV6_ONLY));
	ASSERT_TRUE(ipv6);
	EXPECT_EQ(*(google_echo_request_ipv6_part()), *ipv6);
}

TEST(ParseIpv6, SimpleIP) {
	const BytesContainer test = boost::assign::list_of
		('\x9c')('\x7b')('\x91')('\xf8');
	EXPECT_EQ( std::string("156.123.145.248"), Ipv6::addr_from_data( test ));
}

TEST(ParseIpv6, Extrabytes) {
	const BytesContainer test = boost::assign::list_of
		('\x9c')('\x7b')('\x91')('\xf8')('\x93')('\xa3');
	EXPECT_EQ( std::string("156.123.145.248"), Ipv6::addr_from_data( test ));
}

TEST(ParseIpv6, NumbersSmallerThan64) {
	const BytesContainer test = boost::assign::list_of
		('\x63')('\x00')('\x25')('\x01');
	EXPECT_EQ( std::string("99.0.37.1"), Ipv6::addr_from_data( test ));
}

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
