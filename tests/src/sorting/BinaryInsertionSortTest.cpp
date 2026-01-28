#include <gtest/gtest.h>

#include <BinaryInsertionSort.h>

using namespace Algorithms::BinaryInsertionSort;

TEST(BinaryInsertionSort, SortsArrayOfLength1)
{
	int array[1] = { 316 };
	sort(array);
	ASSERT_EQ(316, array[0]);
}

TEST(BinaryInsertionSort, SortsArrayOfLength10)
{
	// Arrange
	int array[] = { 316, 284, 3912, 329111, 85, 0, 55, 22, -555, -328123 };
	const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(array);

	// Assert
	for (std::size_t i = 0, size = std::size(array); i < size; i++)
	{
		ASSERT_EQ(sorted[i], array[i]);
	}
}

TEST(BinaryInsertionSort, SortsSortedArray)
{
	// Arrange
	int array[] = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
	const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(array);

	// Assert
	for (std::size_t i = 0, size = std::size(array); i < size; i++)
	{
		ASSERT_EQ(sorted[i], array[i]);
	}
}

TEST(BinaryInsertionSort, SortsReverseArray)
{
	// Arrange
	int array[] = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };
	const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(array);

	// Assert
	for (std::size_t i = 0, size = std::size(array); i < size; i++)
	{
		ASSERT_EQ(sorted[i], array[i]);
	}
}

TEST(BinaryInsertionSort, SortsArrayDescendingUsingComparator)
{
	// Arrange
	int array[] = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
	const int sorted[] = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };

	// Act
	sort(array, std::greater<int>());

	// Assert
	for (std::size_t i = 0, size = std::size(array); i < size; i++)
	{
		ASSERT_EQ(sorted[i], array[i]);
	}
}

TEST(BinaryInsertionSort, SortsLettersInAscendingByDefault)
{
	// Arrange
	int array[] = { 'f', 'e', 'a', 'm', 't', 'l', 'r', 'a', 'd', 'b' };
	const int sorted[] = { 'a', 'a', 'b', 'd', 'e', 'f', 'l', 'm', 'r', 't' };

	// Act
	sort(array);

	// Assert
	for (std::size_t i = 0, size = std::size(array); i < size; i++)
	{
		ASSERT_EQ(sorted[i], array[i]);
	}
}

TEST(BinaryInsertionSort, SortsVectorOfLength10)
{
	// Arrange
	std::vector vector = { 316, 284, 3912, 329111, 85, 0, 55, 22, -555, -328123 };
	const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(vector);

	// Assert
	for (std::size_t i = 0, size = std::size(vector); i < size; i++)
	{
		ASSERT_EQ(sorted[i], vector[i]);
	}
}

TEST(BinaryInsertionSort, SortsSortedVector)
{
	// Arrange
	std::vector vector = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
	const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(vector);

	// Assert
	for (std::size_t i = 0, size = vector.size(); i < size; i++)
	{
		ASSERT_EQ(sorted[i], vector[i]);
	}
}

TEST(BinaryInsertionSort, SortsReverseVector)
{
	// Arrange
	std::vector vector = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };
	const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(vector);

	// Assert
	for (std::size_t i = 0, size = vector.size(); i < size; i++)
	{
		ASSERT_EQ(sorted[i], vector[i]);
	}
}