#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <RecursiveInsertionSort.h>

using ::testing::ElementsAreArray;

using namespace Algorithms::RecursiveInsertionSort;

TEST(RecursiveInsertionSort, SortsArrayOfLength1)
{
	int array[1] = { 316 };
	sort(array);
	EXPECT_EQ(316, array[0]);
}

TEST(RecursiveInsertionSort, SortsArrayOfLength10)
{
	// Arrange
	int array[] = { 316, 284, 3912, 329111, 85, 0, 55, 22, -555, -328123 };
	const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(array);

	// Assert
	EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(RecursiveInsertionSort, SortsSortedArray)
{
	// Arrange
	int array[] = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
	const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(array);

	// Assert
	EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(RecursiveInsertionSort, SortsReverseArray)
{
	// Arrange
	int array[] = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };
	const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(array);

	// Assert
	EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(RecursiveInsertionSort, SortsArrayDescendingUsingComparator)
{
	// Arrange
	int array[] = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
	const int sorted[] = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };

	// Act
	sort(array, std::greater<int>());

	// Assert
	EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(RecursiveInsertionSort, SortsLettersInAscendingByDefault)
{
	// Arrange
	int array[] = { 'f', 'e', 'a', 'm', 't', 'l', 'r', 'a', 'd', 'b' };
	const int sorted[] = { 'a', 'a', 'b', 'd', 'e', 'f', 'l', 'm', 'r', 't' };

	// Act
	sort(array);

	// Assert
	EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(RecursiveInsertionSort, SortsVectorOfLength10)
{
	// Arrange
	std::vector vector = { 316, 284, 3912, 329111, 85, 0, 55, 22, -555, -328123 };
	const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(vector);

	// Assert
	EXPECT_EQ(sorted, vector);
}

TEST(RecursiveInsertionSort, SortsSortedVector)
{
	// Arrange
	std::vector vector = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
	const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(vector);

	// Assert
	EXPECT_EQ(sorted, vector);
}

TEST(RecursiveInsertionSort, SortsReverseVector)
{
	// Arrange
	std::vector vector = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };
	const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(vector);

	// Assert

	EXPECT_EQ(sorted, vector);

}