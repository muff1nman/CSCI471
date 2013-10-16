/*
 * parse_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "test_helper.h"
#include "file_ops.h"
#include "file_names.h"
#include "dns_common.h"

#include "dnsmuncher/parse/dns.h"

#include <boost/assign/list_of.hpp>

TEST(Parse, Helper) {
	const BytesContainer test = boost::assign::list_of 
		('\x73') ('\xcc') ('\x01') ('\x00') ('\x00') ('\x01') ('\x00') ('\x00')
		('\x00') ('\x00') ('\x00') ('\x00') ('\x03') ('\x77') ('\x77') ('\x77')
		('\x06') ('\x67') ('\x6f') ('\x6f') ('\x67') ('\x6c') ('\x65') ('\x03')
		('\x63') ('\x6f') ('\x6d') ('\x00') ('\x00') ('\x01') ('\x00') ('\x01');
	EXPECT_EQ( test, bytes_from_file( QUERY_A_GOOGLE ));
}

TEST(Parse, SimpleQuery) {
	EXPECT_EQ( *query_a_google_obj(), from_data(bytes_from_file( QUERY_A_GOOGLE )));
}

TEST(Parse, ComplexResponse) {
	EXPECT_EQ( *response_complex_google(), from_data(bytes_from_file( RESPONSE_COMPLEX_GOOGLE )));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
#ifdef LOGGING
	google::InitGoogleLogging( PROJECT_NAME "-" "TestParse");
	FLAGS_minloglevel = LOG_LEVEL;
	FLAGS_alsologtostderr = 1;
	FLAGS_colorlogtostderr = 1;
#endif
  return RUN_ALL_TESTS();
}
