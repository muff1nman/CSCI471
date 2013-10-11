/*
 * util_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "dnsmuncher/config.h"
#include "dnsmuncher/util/byte.h"
#include "gtest/gtest.h"
#ifdef LOGGING
#include <glog/logging.h>
#endif

#include <bitset>
#include <string>

TEST(ByteTest, SingleWidthBitset) {
	std::bitset<8> t1(1);
	EXPECT_EQ(t1.to_ulong(), (unsigned long) convert_to_char_little_endian<8>(t1)) << "Char does not hold a single bit";

	t1 = std::bitset<8>(std::string("11111111"));
	EXPECT_EQ(255, (unsigned long) convert_to_char_little_endian<8>(t1)) << "Returned character is not set with every bit";
}

TEST(ByteTest, MultipleWidthBitset) {
	std::bitset<6> t1(std::string("110100"));
	EXPECT_EQ(6, (unsigned long) convert_to_char_little_endian<3>( t1, 1 ));
	EXPECT_EQ(4, (unsigned long) convert_to_char_little_endian<3>( t1, 0));

	std::bitset<16> t2(std::string("0101110110000110"));
	EXPECT_EQ(93, (unsigned long) convert_to_char_little_endian<8>( t2, 1));
	EXPECT_EQ(134, (unsigned long) convert_to_char_little_endian<8>( t2, 0));

}

TEST(ByteTest, InvalidParams) {
	std::bitset<4> t1(std::string("1000"));
	EXPECT_DEATH({ convert_to_char_little_endian<2>( t1, 3 );}, "Out of Bounds");
	EXPECT_DEATH({ convert_to_char_little_endian<5>( t1, 1 );}, "Width too large");

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
#ifdef LOGGING
	google::InitGoogleLogging("TestUtil");
	FLAGS_minloglevel = LOG_LEVEL;
	FLAGS_alsologtostderr = 1;
	FLAGS_colorlogtostderr = 1;
#endif
  return RUN_ALL_TESTS();
}

