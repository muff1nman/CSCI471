/*
 * parse_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "test_helper.h"
#include "ethernet_helper.h"

#include "ethernet/parse/ethernet.h"

TEST(ParseBytesFile, Helper) {
	const BytesContainer test = boost::assign::list_of 
		('\x9A')('\x4B')('\x4A')('\x40')('\xE7')('\x0C')('\x4C')
		('\x0F')('\x6E')('\x65')('\x7E')('\x60')('\x08')('\x00');

	EXPECT_EQ( 14, bytes_from_file(ETHERNETV2_HEADER).size());
	EXPECT_EQ( test, bytes_from_file(ETHERNETV2_HEADER));
}

TEST(ParseEthernet, Version2) {
	EthernetMaybe ethermaybe = ETHERNETV2::from_data(bytes_from_file(ETHERNETV2_HEADER));
	EthernetPtr expected = ethernet_v2();
	ASSERT_TRUE(ethermaybe);
	EXPECT_EQ(*expected, *ethermaybe);
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
