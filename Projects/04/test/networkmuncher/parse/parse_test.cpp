/*
 * parse_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "test_helper.h"
#include "file_ops.h"
#include "file_names.h"

#include "networkmuncher/parse/ip_addr.h"

#include <boost/assign/list_of.hpp>

TEST(ParseBytesFile, Helper) {
	const BytesContainer test = boost::assign::list_of 
		('\x73') ('\xcc') ('\x01') ('\x00') ('\x00') ('\x01') ('\x00') ('\x00')
		('\x00') ('\x00') ('\x00') ('\x00') ('\x03') ('\x77') ('\x77') ('\x77')
		('\x06') ('\x67') ('\x6f') ('\x6f') ('\x67') ('\x6c') ('\x65') ('\x03')
		('\x63') ('\x6f') ('\x6d') ('\x00') ('\x00') ('\x01') ('\x00') ('\x01');
	EXPECT_EQ( test, bytes_from_file( QUERY_A_GOOGLE ));
}

TEST(ParseIP, SimpleIP) {
	const BytesContainer test = boost::assign::list_of
		('\x9c')('\x7b')('\x91')('\xf8');
	EXPECT_EQ( std::string("156.123.145.248"), ip_from_data( test ));
}

TEST(ParseIP, Extrabytes) {
	const BytesContainer test = boost::assign::list_of
		('\x9c')('\x7b')('\x91')('\xf8')('\x93')('\xa3');
	EXPECT_EQ( std::string("156.123.145.248"), ip_from_data( test ));
}

TEST(ParseIP, NumbersSmallerThan64) {
	const BytesContainer test = boost::assign::list_of
		('\x63')('\x00')('\x25')('\x01');
	EXPECT_EQ( std::string("99.0.37.1"), ip_from_data( test ));
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
