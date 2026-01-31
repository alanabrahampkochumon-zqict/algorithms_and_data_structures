#pragma once

#include <cstddef>
#include <vector>

/*
* Hybrid sort uses a combination of Merge and Insertion sort,
* taking advantage of efficiency of Insertion sort at lower array sizes like 16 or 32,
* due to its linear operations making it favorable for cache hits.
*/

namespace Algorithms::HybridSort
{
	/**
	 * Sorts an array using merge sort and insertion sort, taking advantage of both sorting algorithms.
	 * @tparam T Type of array to be sorted.
	 * @tparam Size Size of the array.
	 * @tparam Comparator Comparator used for sorting like std::less
	 * @param array The data to be sorted.
	 * @param comp Comparator function passed in.
	 * @param kValue Threshold for using insertion sort, stopping merge sort at n/k. Default = 16.
	 */
	template <typename T, std::size_t Size, typename Comparator>
	void sort(T(&array)[Size], Comparator comp, unsigned int kValue = 16);

	/**
	 * Sorts a vector using merge sort and insertion sort, taking advantage of both sorting algorithms.
	 * @tparam T Type of array to be sorted.
	 * @tparam Size Size of the array.
	 * @param array The data to be sorted.
	 * @param kValue Threshold for using insertion sort, stopping merge sort at n/k. Default = 16.
	 */
	template <typename T, std::size_t Size>
	void sort(T(&array)[Size], unsigned int kValue = 16);


	/**
	 * Sorts a vector using merge sort and insertion sort, taking advantage of both sorting algorithms.
	 * @tparam T Type of vector to be sorted.
	 * @tparam Comparator Comparator used for sorting like std::less
	 * @param vector The data to be sorted.
	 * @param comp Comparator function passed in.
	 * @param kValue Threshold for using insertion sort, stopping merge sort at n/k. Default = 16.
	 */
	template <typename T, typename Comparator>
	void sort(std::vector<T>& vector, Comparator comp, unsigned int kValue = 16);


	/**
	 * Sorts a vector using merge sort and insertion sort, taking advantage of both sorting algorithms.
	 * @tparam T Type of vector to be sorted.
	 * @param vector The data to be sorted.
	 * @param kValue Threshold for using insertion sort, stopping merge sort at n/k. Default = 16.
	 */
	template <typename T>
	void sort(std::vector<T>& vector, unsigned int kValue = 16);
}

#include "HybridSort.tpp"