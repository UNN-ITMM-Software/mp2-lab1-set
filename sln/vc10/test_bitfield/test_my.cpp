//#include "tbitfield.h"
//#include "tset.h"
//#include <gtest.h>
//
//
//TEST(TBitFieldTest, DoubleClearBit) 
//{
//    TBitField bf(10);  // ������ ������� ���� �������� 10
//    bf.ClrBit(3);      // ������� ��� 3
//    bf.ClrBit(3);      // ����� ������� ��� 3
//    EXPECT_EQ(bf.GetBit(3), 0);  // ���������, ��� ��� 3 ����� 0
//}
//
//
//TEST(TBitFieldTest, MultipleBitwiseOR) {
//    TBitField bf1(5);
//    TBitField bf2(5);
//    TBitField bf3(5);
//
//    
//    bf1.SetBit(0); 
//    bf1.SetBit(2); 
//    bf2.SetBit(1); 
//    bf3.SetBit(3); 
//
//
//    TBitField result = bf1 | bf2 | bf3;
//
//    // ��������� ���������: ������ ���� ����������� ���� 0, 1, 2 � 3
//    EXPECT_TRUE(result.GetBit(0));
//    EXPECT_TRUE(result.GetBit(1));
//    EXPECT_TRUE(result.GetBit(2));
//    EXPECT_TRUE(result.GetBit(3));
//    EXPECT_FALSE(result.GetBit(4)); // ��� 4 �� ������ ���� ����������
//}
//
//
//
//TEST(TSetTest, MultipleSetOperations) 
//{
//    TSet set1(5);
//    set1.InsElem(1);
//    set1.InsElem(3);
//
//    TSet set2(5);
//    set2.InsElem(0);
//    set2.InsElem(4);
//
//    TSet set3(5);
//    set3.InsElem(2);
//
//    TSet result = set1 + set2 + set3;  // ��������� �������� �� ���� ����������
//
//    EXPECT_EQ(result.IsMember(0), true);  // ���������, ��� ������� 0 � ���������
//    EXPECT_EQ(result.IsMember(1), true);  // ���������, ��� ������� 1 � ���������
//    EXPECT_EQ(result.IsMember(2), true);  // ���������, ��� ������� 2 � ���������
//    EXPECT_EQ(result.IsMember(3), true);  // ���������, ��� ������� 3 � ���������
//    EXPECT_EQ(result.IsMember(4), true);  // ���������, ��� ������� 4 � ���������
//}
//
//
