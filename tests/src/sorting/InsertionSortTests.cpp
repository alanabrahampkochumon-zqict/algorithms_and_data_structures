/**
 * @file InsertionSortTests.cpp
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Insertion Sort tests.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <InsertionSort.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::ElementsAreArray;

using namespace algorithms;

TEST(InsertionSort, SortsArrayOfLength1)
{
    int array[1] = { 316 };
    insertionSort(array);
    EXPECT_EQ(316, array[0]);
}

TEST(InsertionSort, SortsArrayOfLength10)
{
    // Arrange
    int array[] = { 316, 284, 3912, 329111, 85, 0, 55, 22, -555, -328123 };
    const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

    // Act
    insertionSort(array);

    // Assert
    EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(InsertionSort, SortsSortedArray)
{
    // Arrange
    int array[] = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
    const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

    // Act
    insertionSort(array);

    // Assert
    EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(InsertionSort, SortsReverseArray)
{
    // Arrange
    int array[] = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };
    const int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

    // Act
    insertionSort(array);

    // Assert
    EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(InsertionSort, SortsArrayDescendingUsingComparator)
{
    // Arrange
    int array[] = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
    const int sorted[] = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };

    // Act
    insertionSort(array, std::greater<int>());

    // Assert
    EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(InsertionSort, SortsLettersInAscendingByDefault)
{
    // Arrange
    int array[] = { 'f', 'e', 'a', 'm', 't', 'l', 'r', 'a', 'd', 'b' };
    const int sorted[] = { 'a', 'a', 'b', 'd', 'e', 'f', 'l', 'm', 'r', 't' };

    // Act
    insertionSort(array);

    // Assert
    EXPECT_THAT(sorted, ElementsAreArray(array));
}

TEST(InsertionSort, SortsVectorOfLength10)
{
    // Arrange
    std::vector vector = { 316, 284, 3912, 329111, 85, 0, 55, 22, -555, -328123 };
    const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

    // Act
    insertionSort(vector);

    // Assert
    EXPECT_EQ(sorted, vector);
}

TEST(InsertionSort, SortsSortedVector)
{
    // Arrange
    std::vector vector = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
    const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

    // Act
    insertionSort(vector);

    // Assert
    EXPECT_EQ(sorted, vector);
}

TEST(InsertionSort, SortsReverseVector)
{
    // Arrange
    std::vector vector = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };
    const std::vector sorted = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };

    // Act
    insertionSort(vector);

    // Assert
    EXPECT_EQ(sorted, vector);
}