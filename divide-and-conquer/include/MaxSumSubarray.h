#pragma once

#include <cstddef>
#include <ranges>
#include <tuple>
#include <concepts>

namespace Algorithms::DivideAndConquer
{
	template<typename T>
	concept Arithmetic = std::integral<T> || std::floating_point<T>;

	template<typename T>
	using WideType = std::conditional_t<std::is_floating_point_v<T>, double, long long>;

	enum AlgorithmType
	{
		BRUTE_FORCE,
		DIVIDE_AND_CONQUER,
		HYBRID
	};

	/**
	 * Finds the maximum sum subarray in the given array or vector.
	 * @tparam Range A contiguous container type (e.g., std::vector, std::array, std::span, or C-array) whose elements satisfy the Arithmetic concept.
	 * @param elements C-style array, std::array or std::vector elements in which to find the max sum subarray. 
	 * @param algorithm Algorithm to use. Options are AlgorithmType::BRUTE_FORCE, DIVIDE_AND_CONQUER, and HYBRID. Default is DIVIDE_AND_CONQUER
	 * @return std::tuple(start, end, maxSum)
	 */
	template<std::ranges::contiguous_range Range>
	requires Arithmetic<std::ranges::range_value_t<Range>>
	std::tuple<std::size_t, std::size_t, WideType<std::ranges::range_value_t<Range>>> maxSumSubarray(const Range& elements, AlgorithmType algorithm = DIVIDE_AND_CONQUER);
}

#include "MaxSumSubarray.tpp"
