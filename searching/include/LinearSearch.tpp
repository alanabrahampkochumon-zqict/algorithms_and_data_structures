#include "LinearSearch.h"


template<typename T>
int _linearSearch(const T* searchable, size_t size, const T& element)
{
	for (std::size_t i = 0; i < size; i++) {
		if (element == searchable[i])
		{
			return i;
		}
	}

	return -1;
}

template<typename T, std::size_t Size>
int Algorithms::Searching::linearSearch(const T(&array)[Size], const T& element)
{
	return _linearSearch(array, Size, element);
}

template<typename T>
int Algorithms::Searching::linearSearch(const std::vector<T>& vector, const T& element)
{
	return _linearSearch(vector.data(), vector.size(), element);
}
