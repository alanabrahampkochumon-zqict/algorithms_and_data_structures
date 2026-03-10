/**
 * @file BinaryInsertionSortTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Binary Insertion Sort tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <BinaryInsertionSort.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace algorithms;
using ::testing::ElementsAreArray;

TEST(BinaryInsertionSort, SortsArrayOfLength1)
{
    int array[1] = { 316 };
    binaryInsertionSort(array);
    EXPECT_EQ(316, array[0]);
}

TEST(BinaryInsertionSort, SortsArrayOfLength10)
{
    // Arrange
    int array[] = { 316, 284, 3912, 329111, 85, 0, 55, 22, -555, -328123 };
    const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

    // Act
    binaryInsertionSort(array);

    // Assert
    EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(BinaryInsertionSort, SortsSortedArray)
{
    // Arrange
    int array[] = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
    const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

    // Act
    binaryInsertionSort(array);

    // Assert
    EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(BinaryInsertionSort, SortsReverseArray)
{
    // Arrange
    int array[] = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };
    const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

    // Act
    binaryInsertionSort(array);

    // Assert
    EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(BinaryInsertionSort, SortsArrayDescendingUsingComparator)
{
    // Arrange
    int array[] = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
    const int sorted[] = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };

    // Act
    binaryInsertionSort(array, std::greater<int>());

    // Assert
    EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(BinaryInsertionSort, SortsLettersInAscendingByDefault)
{
    // Arrange
    int array[] = { 'f', 'e', 'a', 'm', 't', 'l', 'r', 'a', 'd', 'b' };
    const int sorted[] = { 'a', 'a', 'b', 'd', 'e', 'f', 'l', 'm', 'r', 't' };

    // Act
    binaryInsertionSort(array);

    // Assert
    EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(BinaryInsertionSort, SortsVectorOfLength10)
{
    // Arrange
    std::vector vector = { 316, 284, 3912, 329111, 85, 0, 55, 22, -555, -328123 };
    const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

    // Act
    binaryInsertionSort(vector);

    // Assert
    EXPECT_EQ(sorted, vector);
}

TEST(BinaryInsertionSort, SortsSortedVector)
{
    // Arrange
    std::vector vector = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
    const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

    // Act
    binaryInsertionSort(vector);

    // Assert
    EXPECT_EQ(sorted, vector);
}

TEST(BinaryInsertionSort, SortsReverseVector)
{
    // Arrange
    std::vector vector = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };
    const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

    // Act
    binaryInsertionSort(vector);

    // Assert
    EXPECT_EQ(sorted, vector);
}