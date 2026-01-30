#pragma once
#include "MergeSort.h"
#include <algorithm>
#include <type_traits>

namespace Algorithms::Generic
{
	template<typename T>
	std::optional<std::size_t> findIndex(const T* data, std::size_t start, std::size_t end, T element)
	{
		while (end > start)
		{
			int middle = start + (end - start) / 2;
			if (element == data[middle])
				return middle;
			else if (element > data[middle])
				start = middle + 1;
			else
				end = middle;
		}
		return std::nullopt;
	}

	// The functions receives sorted array or T*
	template <typename T>
	std::optional<std::pair<T, T>> _twoSum(const T* data, const std::size_t size, T target)
	{
		static_assert(std::is_arithmetic_v<T>, "T must be a number like float, double, or int.");

		for (std::size_t i = 0; i < size; i++)
		{
			T key = data[i];
			T diff = target - key;
			std::optional<std::size_t> index = findIndex(data, (i + 1), size, diff);
			if (index.has_value())
			{
				return std::make_pair(data[i], data[index.value()]);
			}
		}
		return std::nullopt;
	}



	template <typename T, std::size_t Size>
	std::optional<std::pair<T, T>> twoSum(const T(&elements)[Size], T target)
	{
		// Array needs to be sorted, since merge sort implementation is in place, it will mutate the array requiring a temp array.
		T temp[Size];
		std::copy(std::begin(elements), std::end(elements), std::begin(temp));
		Algorithms::MergeSort::sort(temp);
		return _twoSum(temp, Size, target);
	}

	template <typename T>
	std::optional<std::pair<T, T>> twoSum(std::vector<T> elements, T target)
	{
		Algorithms::MergeSort::sort(elements);
		return _twoSum(elements.data(), elements.size(), target);
	}
}
