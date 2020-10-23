#include <gtest.h>

TEST(TRatio, two_plus_two_equals_four)
{
    // Arrange
    int x = 2;

    // Act
    x = x + x;

    // Assert
    EXPECT_EQ(4, x);
}
