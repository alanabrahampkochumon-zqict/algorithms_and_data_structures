#pragma once

#include <tuple>
#include <limits>

namespace Algorithms::DivideAndConquer
{
	template<std::ranges::contiguous_range Range>
		requires Arithmetic<std::ranges::range_value_t<Range>>
	std::tuple<std::size_t, std::size_t, WideType<std::ranges::range_value_t<Range>>> maxSumSubarray(const Range& elements, AlgorithmType algorithm)
	{
		using R = WideType<std::ranges::range_value_t<Range>>;
		if (elements.empty())
		{
			return { 0, 0, 0 };
		}

		R maxSum = std::numeric_limits<R>::min(); // Initialize to the Wide types(double's or long long's min value)
		std::size_t start = 0, end = 0;

		for (std::size_t i = 0; i < elements.size(); ++i)
		{
			R currentSum = 0;
			for (std::size_t j = i; j < elements.size(); ++j)
			{
				currentSum += elements[j];
				if (currentSum > maxSum)
				{
					maxSum = currentSum;
					start = i;
					end = j;
				}
			}
		}

		return { start, end, maxSum };
	}

}
