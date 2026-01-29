#pragma once
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

namespace Algorithms::MergeSort
{
	template <typename T, typename Comparator>
	void _mergeSort(T* data, std::size_t start, std::size_t end, Comparator comp)
	{
		static_assert(std::is_invocable_r_v<bool, Comparator, T, T>, "Comparator must be a invocable(function)(T, T) with a bool return type.");

		if (end - start < 2) return;

		std::size_t middle = start + (end - start) / 2;

		_mergeSort(data, start, middle, comp);
		_mergeSort(data, middle, end, comp);

		_merge(data, start, middle, end, comp);
	}

	template <typename T, typename Comparator>
	void _merge(T* data, std::size_t start, std::size_t middle,std::size_t end, Comparator comp)
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

		// Pushing any remaining elements from left or right partition to the array
		while (i < middle)
			temp[k++] = data[i++];

		while (j < end)
			temp[k++] = data[j++];

		// Copying the elements since mergesort is not in place
		for (std::size_t i = start; i < end; i++)
		{
			data[i] = temp[i - start];
		}
	}

	template <typename T, std::size_t Size, typename Comparator>
	void sort(T(&array)[Size], Comparator comp)
	{
		_mergeSort(array, 0, Size, comp);
	}

	template <typename T, std::size_t Size>
	void sort(T(&array)[Size])
	{
		_mergeSort(array, 0, Size, std::less<T>());
	}

	template <typename T, typename Comparator>
	void sort(std::vector<T>& vector, Comparator comp)
	{
		_mergeSort(vector.data(), 0, vector.size(), comp);
	}

	template <typename T>
	void sort(std::vector<T>& vector)
	{
		sort(vector, std::less<T>());
	}
}
