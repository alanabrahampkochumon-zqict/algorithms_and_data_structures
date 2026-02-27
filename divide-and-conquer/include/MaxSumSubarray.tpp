#pragma once

#include <tuple>
#include <limits>

namespace Algorithms::DivideAndConquer
{
	template<std::ranges::contiguous_range Range>
		requires Arithmetic<std::ranges::range_value_t<Range>>
	static auto bruteForce(const Range& elements, std::size_t size)
	{
		using R = WideType<std::ranges::range_value_t<Range>>;
		R maxSum = std::numeric_limits<R>::lowest(); // Initialize to the Wide types(double's or long long's min value)
		std::size_t start = 0, end = 0;

		for (std::size_t i = 0; i < size; ++i)
		{
			R currentSum = 0;
			for (std::size_t j = i; j < size; ++j)
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
	static std::tuple<std::size_t, std::size_t, WideType<std::ranges::range_value_t<Range>>> crossMaxSumSubarray(const Range& elements, std::size_t start, std::size_t middle, std::size_t end)
	{
		using R = WideType<std::ranges::range_value_t<Range>>;
		R leftSum = std::numeric_limits<R>::lowest(), rightSum = std::numeric_limits<R>::lowest(); // Initialize to the lowest value of the given data type.

		std::size_t leftMax = 0, rightMax = 0;

		// Find the max sum subarray in the right part [-2, 4, 3] -> [4, 3]
		R currentSum = 0;
		for (std::size_t i = middle;; --i)
		{
			currentSum += elements[i];
			if (currentSum > leftSum)
			{
				leftSum = currentSum;
				leftMax = i;
			}

			if (i == start) break;
		}

		// Find the max sum subarray in the left part [6, 8, -4] -> [6, 8]
		currentSum = 0;
		for (std::size_t i = middle + 1; i <= end ; ++i)
		{
			currentSum += elements[i];
			if (currentSum > rightSum)
			{
				rightSum = currentSum;
				rightMax = i;
			}
		}

		return { leftMax, rightMax, leftSum + rightSum };
	}

	template<std::ranges::contiguous_range Range>
		requires Arithmetic<std::ranges::range_value_t<Range>>
	std::tuple<std::size_t, std::size_t, WideType<std::ranges::range_value_t<Range>>> divideAndConquer(const Range& elements, std::size_t start, std::size_t end)
	{
		if (start == end)
			return { start, end, elements[start] };
		std::size_t middle = start + ( end - start ) / 2;

		const auto [leftStart, leftEnd, leftSum] = divideAndConquer(elements, start, middle); // Left
		const auto [rightStart, rightEnd, rightSum] = divideAndConquer(elements, middle + 1, end); // Right
		const auto [crossStart, crossEnd, crossSum] = crossMaxSumSubarray(elements, start, middle, end); // Cross

		// If the greatest sum subarray is the left subarray return it
		if (leftSum >= rightSum && leftSum >= crossSum)
			return { leftStart, leftEnd, leftSum };
		// If the greatest sum subarray is in the right subarray return it
		else if (rightSum >= crossSum)
			return { rightStart, rightEnd, rightSum };
		// Else return the subarray between the two containing the max sum
		return { crossStart, crossEnd, crossSum };
	}

	template<std::ranges::contiguous_range Range>
		requires Arithmetic<std::ranges::range_value_t<Range>>
	std::tuple<std::size_t, std::size_t, WideType<std::ranges::range_value_t<Range>>> maxSumSubarray(const Range& elements, std::size_t size, AlgorithmType algorithm)
	{

		if (elements.empty())
		{
			return { 0, 0, 0 };
		}

		std::cout << "Size: " << size;
		if (algorithm == AlgorithmType::BRUTE_FORCE)
			return bruteForce(elements, size);
		else if (algorithm == AlgorithmType::DIVIDE_AND_CONQUER)
			return divideAndConquer(elements, 0, size - 1);

		// TODO: Implement DIVIDE_AND_CONQUER and HYBRID
		throw std::invalid_argument("Algorithm not yet implemented");
	}

}
