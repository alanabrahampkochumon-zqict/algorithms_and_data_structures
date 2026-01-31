#include <iterator>

#include <gtest/gtest.h>

#include <HybridSort.h>
#include <random>

using namespace Algorithms::HybridSort;

TEST(HybridSort, SortsArrayOfLength1)
{
    int array[1] = {316};
    sort(array);
    EXPECT_EQ(316, array[0]);
}

TEST(HybridSort, SortsArrayOfLength10)
{
    // Arrange
    int array[] = {316, 284, 3912, 329111, 85, 0, 55, 22, -555, -328123};
    const int sorted[] = {-328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111};

    // Act
    sort(array);

    // Assert
    for (std::size_t i = 0, size = std::size(array); i < size; i++)
    {
        EXPECT_EQ(sorted[i], array[i]);
    }
}

TEST(HybridSort, SortsSortedArray)
{
    // Arrange
    int array[] = {-328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111};
    const int sorted[] = {-328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111};

    // Act
    sort(array);

    // Assert
    for (std::size_t i = 0, size = std::size(array); i < size; i++)
    {
        EXPECT_EQ(sorted[i], array[i]);
    }
}

TEST(HybridSort, SortsReverseArray)
{
    // Arrange
    int array[] = {329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123};
    const int sorted[] = {-328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111};

    // Act
    sort(array);

    // Assert
    for (std::size_t i = 0, size = std::size(array); i < size; i++)
    {
        EXPECT_EQ(sorted[i], array[i]);
    }
}

TEST(HybridSort, SortsArrayDescendingUsingComparator)
{
    // Arrange
    int array[] = {-328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111};
    const int sorted[] = {329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123};

    // Act
    sort(array, std::greater<int>());

    // Assert
    for (std::size_t i = 0, size = std::size(array); i < size; i++)
    {
        EXPECT_EQ(sorted[i], array[i]);
    }
}

TEST(HybridSort, SortsLettersInAscendingByDefault)
{
    // Arrange
    int array[] = {'f', 'e', 'a', 'm', 't', 'l', 'r', 'a', 'd', 'b'};
    const int sorted[] = {'a', 'a', 'b', 'd', 'e', 'f', 'l', 'm', 'r', 't'};

    // Act
    sort(array);

    // Assert
    for (std::size_t i = 0, size = std::size(array); i < size; i++)
    {
        EXPECT_EQ(sorted[i], array[i]);
    }
}

TEST(HybridSort, SortsVectorOfLength10)
{
    // Arrange
    std::vector vector = {316, 284, 3912, 329111, 85, 0, 55, 22, -555, -328123};
    const std::vector sorted = {-328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111};

    // Act
    sort(vector);

    // Assert
    for (std::size_t i = 0, size = std::size(vector); i < size; i++)
    {
        EXPECT_EQ(sorted[i], vector[i]);
    }
}

TEST(HybridSort, SortsSortedVector)
{
    // Arrange
    std::vector vector = {-328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111};
    const std::vector sorted = {-328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111};

    // Act
    sort(vector);

    // Assert
    for (std::size_t i = 0, size = vector.size(); i < size; i++)
    {
        EXPECT_EQ(sorted[i], vector[i]);
    }
}

static std::vector<int> genRandomVector(std::size_t size)
{
    std::vector<int> vector(size);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution dist(-10000, 10000); // Generate between -10000, 10000 in a uniform distribution

    for (int& currentValue : vector)
    {
        currentValue = dist(rng);
    }

    return vector;
}

TEST(HybridSort, GivenLargeVectorTheVectorIsSortedAsExpected)
{
    constexpr std::size_t SIZE = 10000;
    std::vector randomVector = genRandomVector(SIZE);
    std::vector sortedVector = randomVector;
    std::sort(sortedVector.begin(), sortedVector.end());

    // Act
    sort(randomVector);

    // Assert
    EXPECT_EQ(sortedVector, randomVector);
}

TEST(HybridSort, GivenLargeReversedVectorTheVectorIsSortsAsExpected)
{
    // Arrange
    constexpr std::size_t SIZE = 10000;
    std::vector reverseVector = genRandomVector(SIZE);
    std::sort(reverseVector.begin(), reverseVector.end(), std::greater<int>());

    std::vector sortedVector = reverseVector;
    std::sort(sortedVector.begin(), sortedVector.end());

    // Act
    sort(reverseVector);

    // Assert
    EXPECT_EQ(sortedVector, reverseVector);
}

