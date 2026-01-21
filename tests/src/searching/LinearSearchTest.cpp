#include <gtest/gtest.h>

#include <LinearSearch.h>
using namespace Algorithms::Searching;




TEST(LinearSearch, SearchingItemInFirstIndexReturnsZero)
{
	// Arrange
	const int array[] = { 316, 55, 11, 293, 593, 55, 329, 592, 391, 999 };
	int searchElement = array[0];

	// Act
	int position = linearSearch(array, searchElement);

	// Assert
	ASSERT_EQ(0, position);
}

TEST(LinearSearch, SearchingItemInLastIndexReturnsLastIndexMinusOne)
{
	// Arrange
	const int array[] = { 316, 55, 11, 293, 593, 55, 329, 592, 391, 999 };
	int searchElement = array[std::size(array) - 1];

	// Act
	int position = linearSearch(array, searchElement);

	// Assert
	ASSERT_EQ(std::size(array) - 1, position);
}

TEST(LinearSearch, SearchingItemAtAnyPositionReturnsCorrectIndex)
{
	// Arrange
	const int array[] = { 316, 55, 11, 293, 593, 55, 329, 592, 391, 999 };
	int searchElement = 593;

	// Act
	int position = linearSearch(array, searchElement);

	// Assert
	ASSERT_EQ(4, position);
}

TEST(LinearSearch, SearchingNonExistantItemReturnsNegativeOne)
{
	// Arrange
	const int array[] = { 316, 55, 11, 293, 593, 55, 329, 592, 391, 999 };
	int searchElement = 455555;

	// Act
	int position = linearSearch(array, searchElement);

	// Assert
	ASSERT_EQ(-1, position);
}

TEST(LinearSearch, SearchForStringInStringArrayReturnssCorrectIndex)
{
	// Arrange
	const std::string array[] = { "test1", "test2", "test3", "test4", "test5"};
	std::string searchElement = "test3";

	// Act
	int position = linearSearch(array, searchElement);

	// Assert
	ASSERT_EQ(2, position);
}

TEST(LinearSearch, SearchForNumberInVectorReturnsCorrectIndex)
{
	// Arrange
	const std::vector<int> vector = { 316, 55, 11, 293, 593, 55, 329, 592, 391, 999 };
	int searchElement = vector[4];

	// Act
	int position = linearSearch(vector, searchElement);

	// Assert
	ASSERT_EQ(4, position);
}