#pragma once

#include <cstddef>
#include <vector>

namespace Algorithms::Generic
{
	/**
	 * Find inversions in an array. Inversion means i < j and array[i] > array[j], or elements that are out of order.
	 * @tparam T Type of array passed in.
	 * @tparam Size Size of array.
	 * @tparam Comparator Type of comparator. Must be std::function<bool(T, T)>.
	 * @param array array to find the inversions in.
	 * @param comp comparator to compare the values to find inversion. Must be provided for custom types.
	 * @return number of inversions.
	 */
	template<typename T, std::size_t Size, typename Comparator>
	std::size_t countInversions(const T(&array)[Size], Comparator comp);

	/**
	 * Find inversions in an array.
	 * Inversion means i < j and array[i] > array[j], or elements that are out of order.
	 * Uses std::less_than as comparator.
	 * @tparam T Type of array passed in.
	 * @tparam Size Size of array.
	 * @param array array to find the inversions in.
	 * @return number of inversions.
	 */
	template<typename T, std::size_t Size>
	std::size_t countInversions(const T(&array)[Size]);

	/**
	 * Vector overload for finding inversions.
	 * @tparam T Type of array passed in.
	 * @tparam Comparator Type of comparator. Must be std::function<bool(T, T)>.
	 * @param vector vector to find the inversions in.
	 * @param comp comparator to compare the values to find inversion. Must be provided for custom types.
	 * @return number of inversions.
	 */
	template<typename T, typename Comparator>
	std::size_t countInversions(std::vector<T> vector, Comparator comp);

	/**
	 * Vector overload for finding inversions
	 * Uses std::less_than as comparator.
	 * @tparam T Type of array passed in.
	 * @param vector vector to find the inversions in.
	 * @return number of inversions.
	 */
	template<typename T>
	std::size_t countInversions(std::vector<T> vector);

}

#include "InversionCount.tpp"