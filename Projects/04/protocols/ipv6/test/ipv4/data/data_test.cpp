/*
 * data_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "test_helper.h"
#include "ipv6/data/ipv6_addr_convert.h"

TEST(IPData, SimpleIp) {
	const BytesContainer expected = boost::assign::list_of
		('\x9c')('\x7b')('\x91')('\xf8');
	EXPECT_EQ(expected, Ipv6AddrConvert(std::string("156.123.145.248")).to_data());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
#ifdef LOGGING
	google::InitGoogleLogging( PROJECT_NAME "-" "TestData");
	FLAGS_minloglevel = TEST_LOG_LEVEL;
	FLAGS_alsologtostderr = 1;
	FLAGS_colorlogtostderr = 1;
#endif
  return RUN_ALL_TESTS();
}
