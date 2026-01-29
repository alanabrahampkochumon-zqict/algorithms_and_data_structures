#pragma once

#include <utility>
#include <cstddef>
#include <optional>
#include <vector>


namespace Algorithms::Generic
{
	/**
	 * Finds if a pair of numbers that sum to `target` exist in the `elements` array.
	 * @tparam T Integral or Floating Number
	 * @param elements Array of number to search for.
	 * @param target The sum to look for in the array.
	 * @return If two numbers add up to the target, they are returned in ascending order, else `std::nullopt` is returned
	 */
	template <typename T, std::size_t Size>
	std::optional<std::pair<T, T>> twoSum(const T(&elements)[Size], T target);

	/**
	 * Finds if a pair of numbers that sum to `target` exist in the `elements` vector.
	 * @tparam T Integral or Floating Number
	 * @param elements Vector of numbers to search for.
	 * @param target The sum to look for in the array.
	 * @return If two numbers add up to the target, they are returned in ascending order, else `std::nullopt` is returned
	 */
	template <typename T>
	std::optional<std::pair<T, T>> twoSum(const std::vector<T>& elements, T target);
}

#include "TwoSum.tpp"