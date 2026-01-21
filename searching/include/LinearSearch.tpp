#include "LinearSearch.h"


template<typename T>
std::optional<size_t> _linearSearch(const T* searchable, size_t size, const T& element)
{
	for (std::size_t i = 0; i < size; i++) {
		if (element == searchable[i])
		{
			return i;
		}
	}

	return std::nullopt;
}

template<typename T, std::size_t Size>
std::optional<size_t> Algorithms::Searching::linearSearch(const T(&array)[Size], const T& element)
{
	return _linearSearch(array, Size, element);
}

template<typename T>
std::optional<size_t> Algorithms::Searching::linearSearch(const std::vector<T>& vector, const T& element)
{
	return _linearSearch(vector.data(), vector.size(), element);
}
