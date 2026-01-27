#pragma once

namespace Algorithms::Searching
{
	template<typename T>
	std::optional<size_t> _binarySearch(const T* data, size_t size, T searchElement)
	{
		size_t start = 0;
		size_t end = size;
		while (end > start)
		{
			size_t middle = start + (end - start) / 2; // To prevent overflow for large numbers
			
			if (searchElement == data[middle])
			{
				return middle;
			}
			else if (searchElement > data[middle])
			{
				start = middle + 1;
			}
			else
			{
				end = middle; // Exclusive
			}

		}

		return std::nullopt;
	}

	template <typename T, size_t Size>
	std::optional<size_t> binarySearch(const T(& array)[Size], T searchElement)
	{
		return _binarySearch(array, Size, searchElement);
	}

	template <typename T>
	std::optional<size_t> binarySearch(const std::vector<T>& vector, T searchElement)
	{
		return _binarySearch(vector.data(), vector.size(), searchElement);
	}
}
