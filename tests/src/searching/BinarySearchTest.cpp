#include <gtest/gtest.h>

#include <BinarySearch.h>

using namespace Algorithms::Searching;


TEST(BinarySearch, SearchingItemInFirstIndexReturnsZero)
{
	// Arrange
	const int array[] = { 11, 55, 55, 293, 316, 329, 391, 592, 593, 9999 };
	int searchElement = array[0];

	// Act
	std::optional<size_t> position = binarySearch(array, searchElement);

	// Assert
	ASSERT_EQ(0, position);
}

TEST(BinarySearch, SearchingItemInLastIndexReturnsArraySizeMinusOne)
{
	// Arrange
	const int array[] = { 11, 55, 55, 293, 316, 329, 391, 592, 593, 9999 };
	int searchElement = array[std::size(array) - 1];

	// Act
	std::optional<size_t> position = binarySearch(array, searchElement);

	// Assert
	ASSERT_EQ(std::size(array) - 1, position);
}

TEST(BinarySearch, SearchingItemAtAnyPositionReturnsCorrectIndex)
{
	// Arrange
	const int array[] = { 11, 55, 55, 293, 316, 329, 391, 592, 593, 9999 };
	int searchElement = 593;

	// Act
	std::optional<size_t> position = binarySearch(array, searchElement);

	// Assert
	ASSERT_EQ(8, position);
}

TEST(BinarySearch, SearchingNonExistantItemReturnsNullOptional)
{
	// Arrange
	const int array[] = { 11, 55, 55, 293, 316, 329, 391, 592, 593, 9999 };
	int searchElement = 455555;

	// Act
	std::optional<size_t> position = binarySearch(array, searchElement);

	// Assert
	ASSERT_EQ(std::nullopt, position);
}

TEST(BinarySearch, SearchForStringInStringArrayReturnssCorrectIndex)
{
	// Arrange
	const std::string array[] = { "test1", "test2", "test3", "test4", "test5" };
	std::string searchElement = "test3";

	// Act
	std::optional<size_t> position = binarySearch(array, searchElement);

	// Assert
	ASSERT_EQ(2, position);
}

TEST(BinarySearch, SearchForNumberInVectorReturnsCorrectIndex)
{
	// Arrange
	const std::vector vector = { 11, 55, 55, 293, 316, 329, 391, 592, 593, 9999 };
	int searchElement = vector[4];

	// Act
	std::optional<size_t> position = binarySearch(vector, searchElement);

	// Assert
	ASSERT_EQ(4, position);
}

