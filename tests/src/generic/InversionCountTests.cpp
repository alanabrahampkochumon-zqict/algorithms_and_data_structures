#include <gtest/gtest.h>

#include <InversionCount.h>

using namespace Algorithms::Generic;

TEST(InversionCount, GivenArrayOfSizeOneReturnsZero)
{
	// Arrange
	int array[] = {1};
	std::size_t expected = 0;

	// Act
	std::size_t actual = countInversions(array);

	// Assert
	EXPECT_EQ(expected, actual);

}

TEST(InversionCount, GivenSortedAscedingArrayOfSize10ReturnsZero)
{
	// Arrange
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::size_t expected = 0;

	// Act
	std::size_t actual = countInversions(array);

	// Assert
	EXPECT_EQ(expected, actual);
}

TEST(InversionCount, GivenSortedArrayDescendingOfSize10ReturnsFortyFive)
{
	// Arrange
	int array[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	std::size_t expected = 45;

	// Act
	std::size_t actual = countInversions(array);

	// Assert
	EXPECT_EQ(expected, actual);
}

TEST(InversionCount, GivenArbitraryCharArrayReturnsCorrectInversionCount)
{
	// Arrange
	int array[] = { 'b', 'c', 'h', 'f', 'a' };
	std::size_t expected = 5;

	// Act
	std::size_t actual = countInversions(array);

	// Assert
	EXPECT_EQ(expected, actual);
}

TEST(InversionCount, GivenArbitraryArrayReturnsCorrectInversionCount)
{
	// Arrange
	int array[] = { 2, 3, 8, 6, 1 };
	std::size_t expected = 5;

	// Act
	std::size_t actual = countInversions(array);

	// Assert
	EXPECT_EQ(expected, actual);
}


TEST(InversionCount, GivenArbitraryVectorReturnsCorrectInversionCount)
{
	// Arrange
	int array[] = { 2, 3, 8, 6, 1 };
	std::size_t expected = 5;

	// Act
	std::size_t actual = countInversions(array);

	// Assert
	EXPECT_EQ(expected, actual);
}

struct Player
{
	int points;
	std::string name;
};

TEST(InversionCount, GivenCustomDataTypeAndComparatorReturnsCorrectInversions)
{
	// Arrange
	Player players[] = {
		{2, "Player 1"},
		{3, "Player 2"},
		{8, "Player 3"},
		{6, "Player 4"},
		{1, "Player 5"},
	};

	std::size_t expected = 5;

	// Act
	std::size_t actual = countInversions(players, [](const Player& one, const Player& two)->bool { return one.points <= two.points; });

	// Assert
	EXPECT_EQ(expected, actual);
}