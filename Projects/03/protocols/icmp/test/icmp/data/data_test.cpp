/*
 * data_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "test_helper.h"
#include "icmp_helper.h"
#include "icmp/data/icmp_convert.h"
#include "networkmuncher/util/byte/print.h"

#include <string>

TEST(ICMPConvert, SimpleEchoRequest) {
	EXPECT_EQ(bytes_from_file( GOOGLE_ECHO_REQUEST ), ICMPConvert(google_echo_request()).to_data());
}

TEST(ICMPConvert, SimpleEchoRequestICMPPart) {
	BytesContainer expected = bytes_from_file( GOOGLE_ECHO_REQUEST_ICMP_ONLY );
	BytesContainer actual = EchoConvert(google_echo_request_echo_part()).to_data();
	EXPECT_EQ(expected,actual);
}

TEST(ICMPConvert, SimpleEchoReply) {
	EXPECT_EQ(bytes_from_file( GOOGLE_ECHO_REPLY ), ICMPConvert(google_echo_reply()).to_data());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
#ifdef LOGGING
	google::InitGoogleLogging( PROJECT_NAME "-" "TestData" );
	FLAGS_minloglevel = TEST_LOG_LEVEL;
	FLAGS_alsologtostderr = 1;
	FLAGS_colorlogtostderr = 1;
#endif
  return RUN_ALL_TESTS();
}


