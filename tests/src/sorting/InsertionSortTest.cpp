#include <gtest/gtest.h>
#include <cstddef>

#include <InsertionSort.h>

using namespace Sorting::InsertionSort;

TEST(InsertionSort, SortsArrayOfLength1)
{
	int array[1] = { 316 };
	sort(array);
	ASSERT_EQ(316, array[0]);
}

TEST(InsertionSort, SortsArrayOfLength10)
{
	std::size_t SIZE = 10;
	int array[] = { 316, 284, 3912, 329111, 85, 0, 55, 22, -555, -328123 };
	int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };
	sort(array);

	for (std::size_t i = 0; i < SIZE; i++)
	{
		ASSERT_EQ(sorted[i], array[i]);
	}
}

TEST(InsertionSort, SortsSortedArray)
{
	std::size_t SIZE = 10;
	int array[] = { -328123, -555, 0, 22, 85, 55, 284, 316, 3912, 329111 };
	int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };
	sort(array);

	for (std::size_t i = 0; i < SIZE; i++)
	{
		ASSERT_EQ(sorted[i], array[i]);
	}
}

TEST(InsertionSort, SortsReverseArray)
{
	std::size_t SIZE = 10;
	int array[] = { 329111, 3912, 316, 284, 85, 55, 22, 0, -555, -328123 };
	int sorted[] = { -328123, -555, 0, 22, 55, 85, 284, 316, 3912, 329111 };
	sort(array);

	std::size_t size = sizeof(array) / sizeof(*array);

	for (std::size_t i = 0; i < size; i++)
	{
		ASSERT_EQ(sorted[i], array[i]);
	}
}