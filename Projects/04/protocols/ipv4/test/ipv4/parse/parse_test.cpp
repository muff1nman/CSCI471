/*
 * parse_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "test_helper.h"
#include "ipv4_helper.h"

#include "ipv4/parse/ipv4.h"

TEST(ParseIpv4, GoogleIpv4Request) {
	Ipv4Maybe ipv4 = IPV4::from_data(bytes_from_file(GOOGLE_ECHO_REQUEST_IPV4_ONLY));
	ASSERT_TRUE(ipv4);
	EXPECT_EQ(*(google_echo_request_ipv4_part()), *ipv4);
}

TEST(ParseIpv4, SimpleIP) {
	const BytesContainer test = boost::assign::list_of
		('\x9c')('\x7b')('\x91')('\xf8');
	EXPECT_EQ( std::string("156.123.145.248"), Ipv4::addr_from_data( test ));
}

TEST(ParseIpv4, Extrabytes) {
	const BytesContainer test = boost::assign::list_of
		('\x9c')('\x7b')('\x91')('\xf8')('\x93')('\xa3');
	EXPECT_EQ( std::string("156.123.145.248"), Ipv4::addr_from_data( test ));
}

TEST(ParseIpv4, NumbersSmallerThan64) {
	const BytesContainer test = boost::assign::list_of
		('\x63')('\x00')('\x25')('\x01');
	EXPECT_EQ( std::string("99.0.37.1"), Ipv4::addr_from_data( test ));
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
