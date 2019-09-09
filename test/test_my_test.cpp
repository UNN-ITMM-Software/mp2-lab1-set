#include "tbitfield.h"

#include <gtest.h>
#include "tset.h"

TEST(MYTEST, 1_plus_3_plus_5_plus_7_plus_9_equals_25)
{
	EXPECT_EQ(5 * 5, 1 + 3 + 5 + 7 + 9);
}

TEST(TBitField, can_twice_clear_bit)
{
	TBitField bf(12);

	int bitIdx = 5;

	bf.SetBit(bitIdx);
	EXPECT_NE(0, bf.GetBit(bitIdx));
	bf.ClrBit(bitIdx);
	bf.ClrBit(bitIdx);
	EXPECT_EQ(0, bf.GetBit(bitIdx));
}

TEST(TBitField, or_operator_applied_to_three_bitfields_of_equal_size)
{
	const int size = 4;
	TBitField bf1(size), bf2(size),bf3(size), expBf(size);
	// bf1 = 0001
	bf1.SetBit(1);
	// bf2 = 0101
	bf2.SetBit(1);
	bf2.SetBit(3);
	// bf3 = 1001
	bf3.SetBit(1);
	bf3.SetBit(4);
	// expBf = 1101
	expBf.SetBit(1);
	expBf.SetBit(3);
	expBf.SetBit(4);

	EXPECT_EQ(expBf, bf1 | bf2 | bf3);
}
TEST(TBitField, and_operator_applied_to_three_bitfields_of_equal_size)
{
	const int size = 4;
	TBitField bf1(size), bf2(size), bf3(size), expBf(size);
	// bf1 = 1001
	bf1.SetBit(1);
	bf1.SetBit(4);
	// bf2 = 1101
	bf2.SetBit(1);
	bf2.SetBit(3);
	bf2.SetBit(4);
	// bf3 = 0001
	bf3.SetBit(1);
	// expBf = 0001
	expBf.SetBit(1);

	EXPECT_EQ(expBf, bf1 & bf2 & bf3);
}

TEST(TSet, can_combine_three_sets_of_non_equal_size)
{
	const int size1 = 5, size2 = 7, size3 = 9;
	TSet set1(size1), set2(size2), set3(size3), set4(size1), expSet(size3);
	// set1 = {1, 2, 4}
	set1.InsElem(1);
	set1.InsElem(2);
	set1.InsElem(4);
	// set2 = {0, 1, 2, 6}
	set2.InsElem(0);
	set2.InsElem(1);
	set2.InsElem(2);
	set2.InsElem(6);
	// set3 = {0, 8}
	set3.InsElem(0);
	set3.InsElem(8);
	
	set4 = set1 + set2 + set3;
	// expSet = {0, 1, 2, 4, 6, 8}
	expSet.InsElem(0);
	expSet.InsElem(1);
	expSet.InsElem(2);
	expSet.InsElem(4);
	expSet.InsElem(6);
	expSet.InsElem(8);
	EXPECT_EQ(expSet, set4);
}