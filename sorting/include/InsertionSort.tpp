#pragma once

namespace Algorithms::InsertionSort
{
	template <typename T, typename Comparator>
	void _sort(T* data, std::size_t size, Comparator comp)
	{
		for (std::size_t i = 1; i < size; i++)
		{
			T key = data[i];
			int j = i - 1;
			while (j >= 0 && comp(key, data[j]))
			{
				data[j + 1] = data[j];
				--j;
			}
			data[j + 1] = key;
		}
	}

	template <typename T, std::size_t Size, typename Comparator>
	void sort(T (&array)[Size], Comparator comp)
	{
		_sort(array, Size, comp);
	}

	template <typename T, std::size_t Size>
	void sort(T (&array)[Size])
	{
		sort(array, std::less<T>());
	}

	template<typename T, typename Comparator>
	void sort(std::vector<T>& vector, Comparator comp)
	{
			_sort(vector.data(), vector.size(), comp);
	}

	template<typename T>
    void sort(std::vector<T>& vector)
	{
		sort(vector, std::less<T>());
	}
}
