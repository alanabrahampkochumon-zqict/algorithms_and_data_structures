#pragma once

#include <cstddef>
#include <span>
#include <tuple>
#include <concepts>

namespace Algorithms::DivideAndConquer
{
	
	template<typename T>
	concept Arithmetic = std::integral<T> || std::floating_point<T>;

	enum AlgorithmType: unsigned char
	{
		BRUTE_FORCE,
		DIVIDE_AND_CONQUER,
		HYBRID
	};

	template<Arithmetic T>
	std::tuple<std::size_t, std::size_t, T> maxSumSubarray(std::span<T> elements);

}

#include "MaxSumSubarray.tpp"
