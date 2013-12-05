/*
 * parse_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "test_helper.h"
#include "ipv4_helper.h"

#include "ipv4/parse/echo.h"
#include "ipv4/parse/ipv4.h"
#include "ipv4/parse/raw.h"

TEST(ParseIpv4, GoogleIpv4Request) {
	Ipv4Maybe ipv4 = IPV4::from_data(bytes_from_file(GOOGLE_ECHO_REQUEST_IPV4_ONLY));
	ASSERT_TRUE(ipv4);
	EXPECT_EQ(*(google_echo_request()->ipv4), *ipv4);
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
