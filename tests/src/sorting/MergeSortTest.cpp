#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <MergeSort.h>

using ::testing::ElementsAreArray;

using namespace Algorithms::MergeSort;

TEST(MergeSort, SortsArrayOfLength1)
{
	int array[1] = { 316 };
	sort(array);
	EXPECT_EQ(316, array[0]);
}

TEST(MergeSort, SortsArrayOfLength10)
{
	// Arrange
	int array[] = { 316, 284, 3912, 329111, 85, 0, 55, 22, -555, -328123 };
	const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(array);

	// Assert
	EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(MergeSort, SortsSortedArray)
{
	// Arrange
	int array[] = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
	const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(array);

	// Assert
	EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(MergeSort, SortsReverseArray)
{
	// Arrange
	int array[] = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };
	const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(array);

	// Assert
	EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(MergeSort, SortsArrayDescendingUsingComparator)
{
	// Arrange
	int array[] = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
	const int sorted[] = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };

	// Act
	sort(array, std::greater<int>());

	// Assert
	EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(MergeSort, SortsLettersInAscendingByDefault)
{
	// Arrange
	int array[] = { 'f', 'e', 'a', 'm', 't', 'l', 'r', 'a', 'd', 'b' };
	const int sorted[] = { 'a', 'a', 'b', 'd', 'e', 'f', 'l', 'm', 'r', 't' };

	// Act
	sort(array);

	// Assert
	EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(MergeSort, SortsVectorOfLength10)
{
	// Arrange
	std::vector vector = { 316, 284, 3912, 329111, 85, 0, 55, 22, -555, -328123 };
	const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(vector);

	// Assert
	EXPECT_EQ(sorted, vector);
}

TEST(MergeSort, SortsSortedVector)
{
	// Arrange
	std::vector vector = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
	const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(vector);

	// Assert
	EXPECT_EQ(sorted, vector);
}

TEST(MergeSort, SortsReverseVector)
{
	// Arrange
	std::vector vector = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };
	const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

	// Act
	sort(vector);

	// Assert
	EXPECT_EQ(sorted, vector);
}