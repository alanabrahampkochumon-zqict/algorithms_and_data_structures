#pragma once

#include <cstddef>

namespace Algorithms
{
	namespace Searching {


		template<typename T, std::size_t Size>
		std::optional<size_t> linearSearch(const T (&array)[Size], const T& element);

		template<typename T>
		std::optional<size_t> linearSearch(const std::vector<T>& vector, const T& element);
	}
}

#include "LinearSearch.tpp"