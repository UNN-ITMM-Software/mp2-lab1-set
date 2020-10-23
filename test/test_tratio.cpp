#include <gtest.h>

#include "tratio.h"

TEST(TRatio, can_use_default_ctor)
{
    // Arrange & Act & Assert
    ASSERT_NO_THROW(TRatio r);
}

TEST(TRatio, can_use_ctor_with_two_parameters)
{
    // Arrange & Act & Assert
    ASSERT_NO_THROW(TRatio r(1, 2));
}

TEST(TRatio, can_use_ctor_with_one_parameter)
{
    // Arrange & Act & Assert
    ASSERT_NO_THROW(TRatio r(1));
}

TEST(TRatio, can_get_numerator)
{
    // Arrange & Act
    TRatio r(3);

    // Assert
    EXPECT_EQ(3, r.GetNumerator());
}

TEST(TRatio, can_get_another_numerator)
{
    // Arrange & Act
    TRatio r(5);

    // Assert
    EXPECT_EQ(5, r.GetNumerator());
}

TEST(TRatio, can_get_denominator)
{
    // Arrange & Act
    TRatio r(1, 3);

    // Assert
    EXPECT_EQ(3, r.GetDenominator());
}
