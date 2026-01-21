#pragma once

#include <cstddef>

namespace Algorithms
{
	namespace Searching {


		template<typename T, std::size_t Size>
		std::size_t linearSearch(const T (&array)[Size], const T& element);
	}
}

#include "LinearSearch.tpp"