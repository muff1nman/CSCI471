/*
 * parse_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "test_helper.h"
#include "icmp_helper.h"

#include "icmp/parse/echo.h"
#include "icmp/parse/ip.h"
#include "icmp/parse/raw.h"

TEST(ParseBytesFile, Helper) {
	const BytesContainer test = boost::assign::list_of 
('\x45') ('\x00') ('\x00') ('\x54') ('\x4F') ('\xB9') ('\x40') ('\x00') ('\x40')
('\x01') ('\x66') ('\x3F') ('\x8A') ('\x43') ('\xCE') ('\x1B') ('\x4A') ('\x7D')
('\xE1') ('\xD4') ('\x08') ('\x00') ('\x4F') ('\x73') ('\x03') ('\x37') ('\x00')
('\x01') ('\x77') ('\xD2') ('\x83') ('\x52') ('\x00') ('\x00') ('\x00') ('\x00')
('\xE2') ('\x5C') ('\x09') ('\x00') ('\x00') ('\x00') ('\x00') ('\x00') ('\x10')
('\x11') ('\x12') ('\x13') ('\x14') ('\x15') ('\x16') ('\x17') ('\x18') ('\x19')
('\x1A') ('\x1B') ('\x1C') ('\x1D') ('\x1E') ('\x1F') ('\x20') ('\x21') ('\x22')
('\x23') ('\x24') ('\x25') ('\x26') ('\x27') ('\x28') ('\x29') ('\x2A') ('\x2B')
('\x2C') ('\x2D') ('\x2E') ('\x2F') ('\x30') ('\x31') ('\x32') ('\x33') ('\x34')
('\x35') ('\x36') ('\x37') ;

	EXPECT_EQ( 84, bytes_from_file(GOOGLE_ECHO_REQUEST).size());
	EXPECT_EQ( test, bytes_from_file(GOOGLE_ECHO_REQUEST));
}

TEST(ParseEcho, GoogleEchoRequest) {
	EchoMaybe echo = ECHO::from_data(bytes_from_file(GOOGLE_ECHO_REQUEST_ICMP_ONLY));
	ASSERT_TRUE(echo);
	EXPECT_EQ(*(google_echo_request()->echo), *echo);
}

TEST(ParseIp, GoogleIpRequest) {
	IpMaybe ip = IP::from_data(bytes_from_file(GOOGLE_ECHO_REQUEST_IP_ONLY));
	ASSERT_TRUE(ip);
	EXPECT_EQ(*(google_echo_request()->ip), *ip);
}

TEST(ParseRaw, FullGoogleEchoRequest) {
	RawMaybe raw = RAW::from_data(bytes_from_file(GOOGLE_ECHO_REQUEST));
	ASSERT_TRUE(raw);
	EXPECT_EQ(*google_echo_request(), *raw);
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
