// test_extra.cpp - дополнительные тесты по заданию
#include <gtest.h>       
#include "tbitfield.h"
#include "tset.h"

// 1. Двойная очистка бита
TEST(TBitFieldExtra, DoubleClearBit) {
    TBitField bf(10);
    bf.SetBit(5);
    bf.ClrBit(5);
    bf.ClrBit(5);  // Вторая очистка
    EXPECT_FALSE(bf.GetBit(5));
}

// 2. Три битовых поля в одной операции
TEST(TBitFieldExtra, TripleBitwiseOr) {
    TBitField bf1(10), bf2(10), bf3(10);
    bf1.SetBit(1);
    bf2.SetBit(2);
    bf3.SetBit(3);
    
    TBitField result = bf1 | bf2 | bf3;
    
    EXPECT_TRUE(result.GetBit(1));
    EXPECT_TRUE(result.GetBit(2));
    EXPECT_TRUE(result.GetBit(3));
    EXPECT_FALSE(result.GetBit(4));
}

// 3. Три множества в одной операции  
TEST(TSetExtra, TripleSetUnion) {
    TSet set1(10), set2(10), set3(10);
    set1.InsElem(1);
    set2.InsElem(2);
    set3.InsElem(3);
    
    TSet result = set1 + set2 + set3;
    
    EXPECT_TRUE(result.IsMember(1));
    EXPECT_TRUE(result.IsMember(2));
    EXPECT_TRUE(result.IsMember(3));
    EXPECT_FALSE(result.IsMember(4));
}