/*
 * data_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "test_helper.h"
#include "file_names.h"
#include "dns_common.h"

#include "dns/data/dns_convert.h"

#include <string>

TEST(DNSConvert, SimpleQuery) {
	EXPECT_EQ(bytes_from_file( QUERY_A_GOOGLE ), DNSConvert(query_a_google_obj()).to_data());
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


