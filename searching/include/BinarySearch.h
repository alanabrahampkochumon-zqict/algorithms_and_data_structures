#pragma once

#include <vector>
#include <cstddef>
#include <optional>

namespace Algorithms::Searching
{
	template<typename T, std::size_t Size>
	std::optional<std::size_t> binarySearch(const T(&array)[Size], T searchElement);

	template<typename T>
	std::optional<std::size_t> binarySearch(const std::vector<T>& vector, T searchElement);


}

#include "BinarySearch.tpp"