#include <gtest/gtest.h>

#include <HornersRule.h>

using namespace Algorithms::Generic;

TEST(HornersRule, StandardPolynomialEvaluatesToCorrectSum)
{
	// Arrange 2x^3 + 4x^2 + 5x + 7 for x = 3
	int coefficients[] = {2, 4, 5, 7};
	int x = 3;
	int expectedOutput = 112;

	// Act
	int result = hornersRule(coefficients, x);

	// Assert
	EXPECT_EQ(expectedOutput, result);
}

TEST(HornersRule, PolynomialWithNegativeTermEvaluatesToCorrectSum)
{
	// Arrange 2x^2 - 3x + 1 for x = -2
	int coefficients[] = { 2, -3, 1};
	int x = -2;
	int expectedOutput = 15;

	// Act
	int result = hornersRule(coefficients, x);

	// Assert
	EXPECT_EQ(expectedOutput, result);
}


TEST(HornersRule, PolynomialWithOnlyConstantTermEvaluatesToCorrectSum)
{
	// Arrange 42 for x = 10
	int coefficients[] = { 42 };
	int x = 5;
	int expectedOutput = 42;

	// Act
	int result = hornersRule(coefficients, x);

	// Assert
	EXPECT_EQ(expectedOutput, result);
}

TEST(HornersRule, PolynomialZeroCoefficientsTermsEvaluatesToCorrectSum)
{
	// Arrange x^4 + 1 for x = 10
	int coefficients[] = { 1, 0, 0, 0, 1 };
	int x = 2;
	int expectedOutput = 17;

	// Act
	int result = hornersRule(coefficients, x);

	// Assert
	EXPECT_EQ(expectedOutput, result);
}