#include <gtest.h>

TEST(SimpleMath, SumOfOddNumbers) {
    // 1+3+5+7+9 = 25 = 5^2
    EXPECT_EQ(1+3+5+7+9, 5*5);
    
    // 1+3+5+7+9+11 = 36 = 6^2  
    EXPECT_EQ(1+3+5+7+9+11, 6*6);
}

TEST(SimpleMath, BasicArithmetic) {
    EXPECT_EQ(2+2, 4);
    EXPECT_EQ(3*7, 21);
}
