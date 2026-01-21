#pragma once

#include <cstddef>

namespace Algorithms
{
	namespace Searching {


		template<typename T, std::size_t Size>
		int linearSearch(const T (&array)[Size], const T& element);

		template<typename T>
		int linearSearch(const std::vector<T>& vector, const T& element);
	}
}

#include "LinearSearch.tpp"