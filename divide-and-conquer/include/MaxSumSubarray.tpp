#pragma once

#include <tuple>
#include <limits>

namespace Algorithms::DivideAndConquer
{
	template<std::ranges::contiguous_range Range>
		requires Arithmetic<std::ranges::range_value_t<Range>>
	static auto _bruteForce(const Range& elements)
	{
		using R = WideType<std::ranges::range_value_t<Range>>;
		R maxSum = std::numeric_limits<R>::lowest(); // Initialize to the Wide types(double's or long long's min value)
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

		return std::make_tuple(start, end, maxSum);
	}

	template<std::ranges::contiguous_range Range>
	requires Arithmetic<std::ranges::range_value_t<Range>>
	static auto _divideAndConquer(const Range& elements, std::size_t start, std::size_t end)
	{
		return std::make_tuple(0, 0, 0);
	}

	template<std::ranges::contiguous_range Range>
		requires Arithmetic<std::ranges::range_value_t<Range>>
	std::tuple<std::size_t, std::size_t, WideType<std::ranges::range_value_t<Range>>> maxSumSubarray(const Range& elements, AlgorithmType algorithm)
	{
		if (elements.empty())
		{
			return { 0, 0, 0 };
		}

		if (algorithm == AlgorithmType::BRUTE_FORCE)
			return _bruteForce(elements);
		else if (algorithm == AlgorithmType::DIVIDE_AND_CONQUER)
			return _divideAndConquer(elements, 0, elements.size());

		// TODO: Implement DIVIDE_AND_CONQUER and HYBRID
		throw std::invalid_argument("Algorithm not yet implemented");
	}

}
