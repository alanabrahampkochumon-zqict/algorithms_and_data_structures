#pragma once
#include "InsertionSort.h"
#include <utility>

namespace Algorithms::HybridSort
{
	template<typename T, typename Comparator>
	void _insertionSort(T* data, std::size_t start, std::size_t end, Comparator comp)
	{
		for (std::size_t i = (start + 1); i < end; ++i)
		{
			T key = std::move(data[i]);
			int j = i;
			while (j > start && comp(key, data[j - 1]))
			{
				data[j] = std::move(data[j -1]);
				j--;
			}
			data[j] = std::move(key);
		}
	}

	
	template<typename T, typename Comparator>
	void _merge(T* data, std::size_t start, std::size_t middle, std::size_t end, Comparator comp)
	{
		std::vector<T> temp(end - start);

		std::size_t i = start, j = middle, k = 0;
		while (i < middle && j < end)
		{
			if (comp(data[i], data[j]))
				temp[k++] = data[i++];
			else
				temp[k++] = data[j++];
		}



		// Push in any remaining elements
		while (i < middle)
			temp[k++] = data[i++];

		while (j < end)
			temp[k++] = data[j++];

		// Copy temp elements to the array to imitate in-place sorting
		for (std::size_t i = start; i < end; i++)
		{
			data[i] = temp[i - start];
		}
	}


	template<typename T, typename Comparator>
	void _sort(T* data, std::size_t start, std::size_t end, Comparator comp, unsigned int kValue)
	{

		static_assert(std::is_invocable_r_v<bool, Comparator, T, T>, "Comparator must be an invocable(function)(T, T) with a bool return type.");

		if (end - start < kValue)
		{
			return _insertionSort(data, start, end, comp);
		}

		std::size_t middle = start + (end - start) / 2;
		// Left Partition
		_sort(data, start, middle, comp, kValue); 
		// Right Partition
		_sort(data, middle, end, comp, kValue); // Since end value is inclusive, we don't need to use + 1 offset.

		_merge(data, start, middle, end, comp);
	}

	template <typename T, std::size_t Size, typename Comparator>
	void sort(T(& array)[Size], Comparator comp, unsigned int kValue)
	{
		_sort(array, 0, Size, comp, kValue);
	}

	template <typename T, std::size_t Size>
	void sort(T(& array)[Size], unsigned int kValue)
	{
		_sort(array, 0, Size, std::less<T>(), kValue);
	}

	template <typename T, typename Comparator>
	void sort(std::vector<T>& vector, Comparator comp, unsigned int kValue)
	{
		_sort(vector.data(), 0, vector.size(), comp, kValue);
	}

	template <typename T>
	void sort(std::vector<T>& vector, unsigned int kValue)
	{
		sort(vector, std::less<T>(), kValue);
	}
}
