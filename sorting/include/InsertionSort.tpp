#pragma once
/**
 * @file InsertionSort.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Insertion Sort implementation.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


namespace algorithms
{
	template <typename T, typename Comparator>
	void _sort(T* data, std::size_t size, Comparator comp)
	{
		for (std::size_t i = 1; i < size; i++)
		{
			T key = data[i];
			int j = i - 1;
			while (j >= 0 && comp(key, data[j]))
			{
				data[j + 1] = data[j];
				--j;
			}
			data[j + 1] = key;
		}
	}

	template <typename T, std::size_t Size, typename Comparator>
	void insertionSort(T (&array)[Size], Comparator comp)
	{
		_sort(array, Size, comp);
	}

	template <typename T, std::size_t Size>
	void insertionSort(T (&array)[Size])
	{
		insertionSort(array, std::less<T>());
	}

	template<typename T, typename Comparator>
	void insertionSort(std::vector<T>& vector, Comparator comp)
	{
			_sort(vector.data(), vector.size(), comp);
	}

	template<typename T>
    void insertionSort(std::vector<T>& vector)
	{
		insertionSort(vector, std::less<T>());
	}
}
