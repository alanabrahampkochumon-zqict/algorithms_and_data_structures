#pragma once
/**
 * @file BinaryInsertionSort.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Binary Insertion Sort implementation.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <functional>
#include <type_traits>


namespace algorithms
{
	template<typename T, typename Comparator>
	void _sort(T* data, std::size_t size, Comparator comp)
	{
		static_assert(std::is_invocable_r_v<bool, Comparator, T, T>, "Comparator must be a callable(function)(T, T) with a bool return type.");

		for (std::size_t i = 1; i < size; i++)
		{
			T key = data[i];
			
			// Binary Search to find the correct index
			std::ptrdiff_t start = 0, end = static_cast<int>(i), middle = 0;
			while (end > start)
			{
				middle = start + (end - start) / 2;
				if (comp(key, data[middle]))
				{
					end = middle;
				}
				else
				{
					start = middle + 1;
				}
			}

			for (int j = static_cast<int>(i) - 1; j >= start; --j)
			{
				data[j + 1] = data[j];
			}
			data[start] = key;
		}

		
	}


	template <typename T, std::size_t Size, typename Comparator>
	void binaryInsertionSort(T(& array)[Size], Comparator comp)
	{
		_sort(array, Size, comp);
	}

	template <typename T, std::size_t Size>
	void binaryInsertionSort(T(&array)[Size])
	{
		_sort(array, Size, std::less<T>());
	}


	template <typename T, typename Comparator>
	void binaryInsertionSort(std::vector<T>& vector, Comparator comp)
	{
		_sort(vector.data(), vector.size(), comp);
	}


	template <typename T>
	void binaryInsertionSort(std::vector<T>& vector)
	{
		binaryInsertionSort(vector, std::less<T>());
		
	}
}
