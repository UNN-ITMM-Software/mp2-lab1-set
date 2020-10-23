#include "tratio.h"

#include <gtest.h>

TEST(TRatio, two_plus_two_equals_four)
{
    // Arrange
    int x = 0;

    // Act
    x = 2 + 2;

    // Assert
    EXPECT_EQ(4, x);
}

TEST(TRatio, can_create_ratio)
{
    // Arrange & Act & Assert
    ASSERT_NO_THROW(TRatio r);
}

TEST(TRatio, can_create_ratio_with_one_parameter)
{
    // Arrange
    int numerator = 1;

    // Act & Assert
    ASSERT_NO_THROW(TRatio r(numerator));
}

TEST(TRatio, can_create_ratio_with_two_parameters)
{
    // Arrange
    int num = 1;
    int den = 2;

    // Act & Assert
    ASSERT_NO_THROW(TRatio r(num, den));
}

TEST(TRatio, can_get_numerator_given_to_ctor)
{
    // Arrange
    int numerator = 3;

    // Act
    TRatio r(numerator);

    // Assert
    EXPECT_EQ(numerator, r.GetNumerator());
}

TEST(TRatio, can_get_another_numerator_given_to_ctor)
{
    // Arrange
    int numerator = 5;

    // Act
    TRatio r(numerator);

    // Assert
    EXPECT_EQ(numerator, r.GetNumerator());
}

TEST(TRatio, can_get_denominator_given_to_ctor)
{
    // Arrange
    int denominator = 3;

    // Act
    TRatio r(1, denominator);

    // Assert
    EXPECT_EQ(denominator, r.GetDenominator());
}

TEST(TRatio, default_numerator_is_equal_to_zero)
{
    // Arrange
    TRatio r;

    // Act
    int numerator = r.GetNumerator();

    // Assert
    EXPECT_EQ(0, numerator);
}

TEST(TRatio, default_denominator_is_equal_to_one)
{
    // Arrange
    TRatio r(2);

    // Act
    int denominator = r.GetDenominator();

    // Assert
    EXPECT_EQ(1, denominator);
}

TEST(TRatio, throws_on_zero_denominator)
{
    // Arrange & Act & Assert
    ASSERT_ANY_THROW(TRatio r(2, 0));
}

TEST(TRatio, sign_moves_to_numerator)
{
    // Arrange & Act
    TRatio r(1, -3);

    // Assert
    EXPECT_EQ(-1, r.GetNumerator());
    EXPECT_EQ(3, r.GetDenominator());
}

TEST(TRatio, sign_moves_to_numerator_and_gcd_applied)
{
    // Arrange & Act
    TRatio r(4, -16);

    // Assert
    EXPECT_EQ(-1, r.GetNumerator());
    EXPECT_EQ(4, r.GetDenominator());
}

TEST(TRatio, sign_stays_in_numerator_and_gcd_applied)
{
    // Arrange & Act
    TRatio r(-5, 10);

    // Assert
    EXPECT_EQ(-1, r.GetNumerator());
    EXPECT_EQ(2, r.GetDenominator());
}

TEST(TRatio, ratio_divided_by_gcd)
{
    // Arrange & Act
    TRatio r(2, 4);

    // Assert
    EXPECT_EQ(1, r.GetNumerator());
    EXPECT_EQ(2, r.GetDenominator());
}
