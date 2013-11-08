/*
 * util_test.cpp
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#include "test_helper.h"

#include "dnsmuncher/util/byte/byte.h"
#include "dnsmuncher/util/byte/convert.h"
#include "dnsmuncher/util/byte/copy.h"
#include "dnsmuncher/util/split.h"
#include "dnsmuncher/util/join.h"

#include <boost/assign/list_of.hpp>
#include <bitset>
#include <string>

TEST(ByteListTest, MultipleWidthBitset) {
	const char* same_order = "\xa5\x51";
	const char* flip_order = "\x51\xa5";

	// in decimal: 165,81; in hex: a5,51
	std::bitset<16> t1(std::string("1010010101010001"));
	BytesContainer a = convert_big_endian<2>(t1);
	EXPECT_EQ(2, a.size());
	EXPECT_TRUE( 0 == memcmp( same_order, a.data(), a.size())) << "Convert big endian out of order";
	a = convert_little_endian<2>(t1);
	EXPECT_EQ(2, a.size());
	EXPECT_TRUE( 0 == memcmp( flip_order, a.data(), a.size())) << "Convert little endian out of order";
}

TEST(ByteTest, SingleWidthBitset) {
	std::bitset<8> t1(1);
	EXPECT_EQ(t1.to_ulong(), (unsigned long) convert_to_char_little_endian<8>(t1)) << "Char does not hold a single bit";
	EXPECT_EQ(t1.to_ulong(), (unsigned long) convert_to_char_big_endian<8>(t1)) << "Char does not hold a single bit";

	t1 = std::bitset<8>(std::string("11111111"));
	EXPECT_EQ(255, (unsigned long) convert_to_char_little_endian<8>(t1)) << "Returned character is not set with every bit";
	EXPECT_EQ(255, (unsigned long) convert_to_char_big_endian<8>(t1)) << "Returned character is not set with every bit";
}

TEST(ByteTest, MultipleWidthBitset) {
	std::bitset<6> t1(std::string("110100"));
	EXPECT_EQ(6, (unsigned long) convert_to_char_little_endian<3>( t1, 1 ));
	EXPECT_EQ(4, (unsigned long) convert_to_char_little_endian<3>( t1, 0));

	EXPECT_EQ(6, (unsigned long) convert_to_char_big_endian<3>( t1, 0 ));
	EXPECT_EQ(4, (unsigned long) convert_to_char_big_endian<3>( t1, 1 ));

	std::bitset<16> t2(std::string("0101110110000110"));
	EXPECT_EQ(93, (unsigned long) convert_to_char_little_endian<8>( t2, 1));
	EXPECT_EQ(134, (unsigned long) convert_to_char_little_endian<8>( t2, 0));

	EXPECT_EQ(93, (unsigned long) convert_to_char_big_endian<8>( t2, 0));
	EXPECT_EQ(134, (unsigned long) convert_to_char_big_endian<8>( t2, 1));

}

TEST(ByteTest, InvalidParams) {
	std::bitset<4> t1(std::string("1000"));
	EXPECT_DEATH({ convert_to_char_little_endian<2>( t1, 3 );}, "Out of Bounds");
	EXPECT_DEATH({ convert_to_char_little_endian<5>( t1, 1 );}, "Width too large");

	EXPECT_DEATH({ convert_to_char_big_endian<2>( t1, 3 );}, "Out of Bounds");
	EXPECT_DEATH({ convert_to_char_big_endian<5>( t1, 1 );}, "Width too large");

}

TEST(CopyInto, Empty) {
	std::bitset<5> empty;
	std::bitset<3> not_empty(std::string("101"));
	std::bitset<5> result(std::string("00101"));
	EXPECT_EQ( result, (copy_into<5,3>(empty, not_empty)));
	empty.reset();

	EXPECT_EQ( result << 2, (copy_into<5,3>(empty, not_empty, 2))) << "Test with non-zero dst index";
	empty.reset();

	EXPECT_EQ( result << 4, (copy_into<5,3>(empty, not_empty, 4))) << "Test with non-zero dst index that creates out of bounds scenario";
	empty.reset();
}

TEST(CopyInto, TooLarge) {
	std::bitset<5> empty;
	std::bitset<10> large_src(std::string("1001010111"));
	std::bitset<5> smaller_result(std::string("10111"));

	EXPECT_EQ( smaller_result, (copy_into<5,10>(empty, large_src))) << "Test with larger src";
}

/*
 *TEST(CopyInto, WithExistingContent) {
 *  // TODO
 *}
 */

TEST(Dissect, Simple) {
	std::bitset<5> random(std::string("01011"));

	EXPECT_EQ( std::bitset<3>(std::string("011")), (dissect<5,3>(random,0)));
	EXPECT_EQ( random, (dissect<5,5>(random,0))) << "Identity operation";
	EXPECT_EQ( std::bitset<3>(std::string("001")), (dissect<5,3>(random,3))) << "Only a piece";
}

TEST(Join, Simple) {
	std::vector<int> first = boost::assign::list_of(3)(4)(1);

	std::vector<int> second = boost::assign::list_of(-4)(-7);

	std::vector<int> expected = boost::assign::list_of(3)(4)(1)(-4)(-7);

	EXPECT_EQ( expected, join( first, second ));
}

// TODO test Join optional

TEST(SplitName, Empty) {
	EXPECT_DEATH({ split_name(""); }, "empty domain");
}

TEST(SplitName, Single) {
	std::vector<std::string> expected = boost::assign::list_of(std::string("ello"));
	EXPECT_EQ( expected, split_name("ello"));
	
	std::vector<std::string> expected1 = boost::assign::list_of(std::string("ello"));
	EXPECT_EQ( expected1, split_name("ello.")) << "Allow trailing period";

	std::vector<std::string> expected2;
	EXPECT_EQ( expected2, split_name(".")) << "Allow a single period";
}

TEST(SplitName, Multiple) {
	std::vector<std::string> expected = boost::assign::list_of(std::string("www"))(std::string("cats"))(std::string("foobar"));
	EXPECT_EQ( expected, split_name("www.cats.foobar"));
}

TEST(SplitName, DoublePeriods) {
	EXPECT_DEATH({ split_name("www.hell..o.com"); }, "duplicate periods");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
#ifdef LOGGING
	google::InitGoogleLogging("TestUtil");
	FLAGS_minloglevel = TEST_LOG_LEVEL;
	FLAGS_alsologtostderr = 1;
	FLAGS_colorlogtostderr = 1;
#endif
  return RUN_ALL_TESTS();
}

