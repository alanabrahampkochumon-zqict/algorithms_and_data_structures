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

	template<std::ranges::contiguous_range Range>
	requires Arithmetic<std::ranges::range_value_t<Range>>
	std::tuple<std::size_t, std::size_t, WideType<std::ranges::range_value_t<Range>>> maxSumSubarray(const Range& elements, AlgorithmType algorithm = DIVIDE_AND_CONQUER);
}

#include "MaxSumSubarray.tpp"
