#pragma once

#include <tuple>

namespace Algorithms::DivideAndConquer
{
	template<std::ranges::contiguous_range Range>
		requires Arithmetic<std::ranges::range_value_t<Range>>
	std::tuple<std::size_t, std::size_t, std::ranges::range_value_t<Range>> maxSumSubarray(const Range& elements, AlgorithmType algorithm)
	{
		// TODO: Implementation
		return std::make_tuple(0, 0, 0);
	}
}
