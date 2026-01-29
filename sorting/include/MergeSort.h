#pragma once

#include <cstddef>
#include <vector>

namespace Algorithms::MergeSort
{
	/**
	 * Sorts an array of elements in-place using Merge Sort.
	 * @tparam T Type of elements to be sorted.
	 * @tparam Size Size of the array.
	 * @tparam Comparator Comparator to use for comparison of elements.
	 * @param array Array to be sorted(psuedo in-place).
	 * @param comp Comparator function that compares element when sorting.
	 */
	template <typename T, std::size_t Size, typename Comparator>
	void sort(T(&array)[Size], Comparator comp);

	/**
	 * Sorts an array of elements in-place using Merge Sort.
	 * @tparam T Type of elements to be sorted.
	 * @tparam Size Size of the array.
	 * @param array Array to be sorted(psuedo in-place).
	 */
	template <typename T, std::size_t Size>
	void sort(T(&array)[Size]);

	/**
	 * Sorts a vector of elements in-place using Merge Sort.
	 * @tparam T Type of elements to be sorted.
	 * @tparam Comparator Comparator to use for comparison of elements.
	 * @param vector Vector to be sorted(psuedo in-place).
	 * @param comp Comparator function that compares element when sorting.
	 */
	template <typename T, typename Comparator>
	void sort(std::vector<T>& vector, Comparator comp);
	
	/**
	 * Sorts a vector of elements in-place using Merge Sort.
	 * @tparam T Type of elements to be sorted.
	 * @param vector Vector to be sorted(psuedo in-place).
	 */
	template <typename T>
	void sort(std::vector<T>& vector);
}

#include "MergeSort.tpp"