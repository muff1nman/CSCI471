/*
 * parse_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "test_helper.h"

#include <boost/assign/list_of.hpp>

TEST(ParseBytesFile, Helper) {
	const BytesContainer test = boost::assign::list_of 
('\x45') ('\x00') ('\x00') ('\x54') ('\xF7') ('\x49') ('\x40') ('\x00') ('\x40')
('\x01') ('\x0C') ('\x31') ('\x0A') ('\x00') ('\x00') ('\xFD') ('\x4A') ('\x7D')
('\xE1') ('\xB4') ('\x08') ('\x00') ('\xBB') ('\x53') ('\x52') ('\x25') ('\x00')
('\x05') ('\x6C') ('\xC9') ('\x81') ('\x52') ('\x00') ('\x00') ('\x00') ('\x00')
('\x34') ('\x93') ('\x09') ('\x00') ('\x00') ('\x00') ('\x00') ('\x00') ('\x10')
('\x11') ('\x12') ('\x13') ('\x14') ('\x15') ('\x16') ('\x17') ('\x18') ('\x19')
('\x1A') ('\x1B') ('\x1C') ('\x1D') ('\x1E') ('\x1F') ('\x20') ('\x21') ('\x22')
('\x23') ('\x24') ('\x25') ('\x26') ('\x27') ('\x28') ('\x29') ('\x2A') ('\x2B')
('\x2C') ('\x2D') ('\x2E') ('\x2F') ('\x30') ('\x31') ('\x32') ('\x33') ('\x34')
('\x35') ('\x36') ('\x37');

	EXPECT_EQ( test, bytes_from_file(GOOGLE_ECHO_REQUEST));
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
