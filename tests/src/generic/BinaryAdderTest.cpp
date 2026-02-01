#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>

#include <BinaryAdder.h>

using ::testing::ElementsAreArray;
using namespace Algorithms::Generic;

TEST(BinaryAdder, AddTwoArrayOfSameSizeReturnsCorrectResult)
{
	// Arrange
	std::array bin1 = {1, 0, 0, 0, 1};
	std::array bin2 = {0, 0, 1, 0, 1};
	std::array result = {0, 1, 0, 1, 1, 0};

	// Act
	auto calc = binaryAdd(bin1, bin2);

	
	// Assert
	ASSERT_TRUE(calc.has_value());
	auto unwrapper = calc.value_or({});
	std::size_t size = unwrapper.size();
	EXPECT_EQ(result.size(), size);
	EXPECT_EQ(result, unwrapper);
	
}

TEST(BinaryAdder, AddTwoArrayResultingInOverflowReturnsCorrectResult)
{
	// Arrange
	std::array bin1 = { 1, 1, 1, 1, 1 };
	std::array bin2 = { 1, 1, 1, 1, 1 };
	std::array result = { 1, 1, 1, 1, 1, 0 };

	// Act
	auto calc = binaryAdd(bin1, bin2);

	// Assert
	ASSERT_TRUE(calc.has_value());
	auto unwrapper = calc.value_or({});
	std::size_t size = unwrapper.size();
	EXPECT_EQ(result.size(), size);
	EXPECT_EQ(result, unwrapper);
}

TEST(BinaryAdder, InvalidBinaryResultsInANull)
{
	// Arrange
	std::array bin1 = { 2, 1, 1, 1, 1 };
	std::array bin2 = { 1, 1, 3, 1, 1 };

	// Act
	auto calc = binaryAdd(bin1, bin2);

	// Assert
	EXPECT_EQ(std::nullopt, calc);
}