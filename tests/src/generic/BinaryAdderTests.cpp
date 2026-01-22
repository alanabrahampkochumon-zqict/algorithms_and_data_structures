#include <gtest/gtest.h>
#include <BinaryAdder.h>
#include <array>

using namespace Algorithms::Generic;

TEST(BinaryAdder, AddTwoArrayOfSameSizeReturnsCorrectResult)
{
	// Arrange
	std::array bin1 = {1, 0, 0, 0, 1};
	std::array bin2 = {0, 0, 1, 0, 1};
	std::array result = {0, 1, 0, 1, 1, 0};

	// Act
	std::array calc = binaryAdd(bin1, bin2);

	// Assert
	std::size_t size = calc.size();
	ASSERT_EQ(result.size(), size);

	for (std::size_t i = 0; i < size; i++)
	{
		ASSERT_EQ(result[i], calc[i]);
	}
}

TEST(BinaryAdder, AddTwoArrayResultingInOverflowReturnsCorrectResult)
{
	// Arrange
	std::array bin1 = { 1, 1, 1, 1, 1 };
	std::array bin2 = { 1, 1, 1, 1, 1 };
	std::array result = { 1, 1, 1, 1, 1, 0 };

	// Act
	std::array calc = binaryAdd(bin1, bin2);

	// Assert
	std::size_t size = calc.size();
	ASSERT_EQ(result.size(), size);

	for (std::size_t i = 0; i < size; i++)
	{
		ASSERT_EQ(result[i], calc[i]);
	}
}