#include <gtest/gtest.h>

#include <TwoSum.h>

using namespace Algorithms::Generic;

TEST(TwoSum, ArrayOfPositiveIntegersWithElementsHavingSumReturnsValidPair)
{
	// Arrange
	const int nums[] = {2, 7, 11, 15};
	constexpr int target = 9;

	// Act
	const std::optional<std::pair<int, int>> result = twoSum(nums, target);

	// Assert
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(2, result->first);
	EXPECT_EQ(7, result->second);
}

TEST(TwoSum, ArrayOfNegativeIntegersWithElementsHavingSumReturnsValidPair)
{
	// Arrange
	const int nums[] = { 1, -2, 5, 10 };
	constexpr int target = -1;

	// Act
	const std::optional<std::pair<int, int>> result = twoSum(nums, target);

	// Assert
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(-2, result->first);
	EXPECT_EQ(1, result->second);
}

TEST(TwoSum, ArrayOfMixedIntegersWithElementsHavingSumReturnsValidPair)
{
	// Arrange
	const int nums[] = { -5, -3, 2, 3, 8, 10, 15 };
	constexpr int target = 5;

	// Act
	const std::optional<std::pair<int, int>> result = twoSum(nums, target);

	// Assert
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(-5, result->first);
	EXPECT_EQ(10, result->second);
}

TEST(TwoSum, ArrayOfMixedIntegersWithoutElementsHavingSumReturnsNullOptional)
{
	// Arrange
	const int nums[] = { 2, 6, 5, 8, 11 };
	constexpr int target = 15;

	// Act
	const std::optional<std::pair<int, int>> result = twoSum(nums, target);

	// Assert
	EXPECT_EQ(std::nullopt, result);
}

TEST(TwoSum, ArrayOfIntegersWithSumZeroReturnsPairOfZero)
{
	// Arrange
	const int nums[] = { 0, 4, 3, 0 };
	constexpr int target = 0;

	// Act
	twoSum(nums, 5);
	const std::optional<std::pair<int, int>> result = twoSum(nums, target);

	// Assert
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(0, result->first);
	EXPECT_EQ(0, result->second);
}

TEST(TwoSum, ArrayOfMixedFloatsWithElementsHavingSumReturnsValidPair)
{
	// Arrange
	const float nums[] = { -5.0, -3.0, 2.0, 3.0, 8.0, 10.0, 15.0 };
	constexpr float target = 5.0;

	// Act
	const std::optional<std::pair<float, float>> result = twoSum(nums, target);

	// Assert
	ASSERT_TRUE(result.has_value());
	ASSERT_FLOAT_EQ(-5.0, result->first);
	ASSERT_FLOAT_EQ(10.0, result->second);
}


TEST(TwoSum, ArrayOfMixedFloatsWithoutElementsHavingSumReturnsNullOptional)
{
	// Arrange
	const float nums[] = { 2.0, 6.0, 5.0, 8.0, 11.0 };
	constexpr float target = 15.0;

	// Act
	const std::optional<std::pair<float, float>> result = twoSum(nums, target);

	// Assert
	EXPECT_EQ(std::nullopt, result);
}

TEST(TwoSum, VectorOfMixedIntegersWithElementHavingSumReturnValidPair)
{
	// Arrange
	const std::vector nums = { -5, -3, 2, 3, 8, 10, 15 };
	constexpr int target = 5;

	// Act
	const std::optional<std::pair<int, int>> result = twoSum(nums, target);

	// Assert
	ASSERT_TRUE(result.has_value());
	EXPECT_EQ(-5, result->first);
	EXPECT_EQ(10, result->second);

}

TEST(TwoSum, VectorOfMixedFloatsWithoutElementsHavingSumReturnsNullOptional)
{
	// Arrange
	const std::vector nums = { 2, 6, 5, 8, 11 };
	constexpr int target = 15;

	// Act
	const std::optional<std::pair<int, int>> result = twoSum(nums, target);

	// Assert
	EXPECT_EQ(std::nullopt, result);
}