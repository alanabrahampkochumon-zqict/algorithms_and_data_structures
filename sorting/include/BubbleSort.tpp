#pragma once
/**
 * @file BubbleSort.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Bubble Sort implementation.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <functional>

namespace algorithms
{

	template<typename T, typename Comparator>
	void _sort(T* data, std::size_t size, Comparator comp)
	{
		if (size < 2) return;

		for (std::size_t i = 0; i < size - 1; ++i) // Loop through the data
		{
			for (std::size_t j = size - 1; j > i; --j) // Iterate from last element to the ith element + 1
			{
				if (comp(data[j], data[j - 1])) // Sink(bubbling) down: Compare current element with previous element, if current element is smaller than previous
					std::swap(data[j], data[j - 1]); // Swap
			}
		}
	}

	template <typename T, std::size_t Size, typename Comparator>
	void bubbleSort(T(&array)[Size], Comparator comp)
	{
		_sort(array, Size, comp);
	}

	template <typename T, std::size_t Size>
	void bubbleSort(T(&array)[Size])
	{
		_sort(array, Size, std::less<T>());
	}


	template <typename T, typename Comparator>
	void bubbleSort(std::vector<T>& vector, Comparator comp)
	{
		_sort(vector.data(), vector.size(), comp);
	}

	template <typename T>
	void bubbleSort(std::vector<T>& vector)
	{
		bubbleSort(vector, std::less<T>());
	}
}
