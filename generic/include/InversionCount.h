#pragma once

#include <cstddef>
#include <vector>

namespace Algorithms::Generic
{
	
	template<typename T, std::size_t Size, typename Comparator>
	std::size_t countInversions(const T(&array)[Size], Comparator comp);

	template<typename T, std::size_t Size>
	std::size_t countInversions(const T(&array)[Size]);

	template<typename T, typename Comparator>
	std::size_t countInversions(std::vector<T> vector, Comparator comp);

	template<typename T>
	std::size_t countInversions(std::vector<T> vector);

}

#include "InversionCount.tpp"