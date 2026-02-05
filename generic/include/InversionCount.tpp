#pragma once

#include <algorithm>
#include <functional>
#include <type_traits>

namespace Algorithms::Generic
{

	template<typename T, typename Comparator>
	std::size_t _merge(T* data, std::size_t start, std::size_t middle, std::size_t end, Comparator comp)
	{
		return 0;
	}

	template<typename T, typename Comparator>
	std::size_t _mergeAndCountInversions(T* data, std::size_t start, std::size_t end, Comparator comp)
	{
		if (end - start < 2) return 0;

		std::size_t middle = start + (end - start) / 2;
		return _mergeAndCountInversions(data, start, middle, comp) + _mergeAndCountInversions(data, start, middle, comp) + _merge(data, start, middle, end, comp);
	}

	template<typename T, std::size_t Size, typename Comparator>
	std::size_t countInversions(const T(&array)[Size], Comparator comp)
	{
		static_assert(std::is_invocable_r_v<bool, Comparator, T, T>, "Comparator must be an invocable(function)(T, T) that returns a bool");
		// Copying the array since the mergeAndCountInversion Function can mutate the array.
		T temp[Size];
		std::copy(std::begin(array), std::end(array), std::begin(temp));

		return _mergeAndCountInversions(temp,0, Size, comp);

	}

	template<typename T, std::size_t Size>
	std::size_t countInversions(const T(&array)[Size])
	{
		return countInversions(array, std::less<T>());
	}

	template<typename T, typename Comparator>
	std::size_t countInversions(std::vector<T> vector, Comparator comp)
	{
		static_assert(std::is_invocable_r_v<bool, Comparator, T, T>, "Comparator must be an invocable(function)(T, T) that returns a bool");
		return _mergeAndCountInversions(vector.data(), 0, vector.size(), comp);
	}

	template<typename T>
	std::size_t countInversions(std::vector<T> vector)
	{
		return countInversions(vector, std::less<T>());
	}

}