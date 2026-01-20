#pragma once

namespace Algorithms::InsertionSort
{
	template <typename T, std::size_t Size, typename Comparator>
	void sort(T (&array)[Size], Comparator comp)
	{
		for (size_t i = 1; i < Size; i++ )
		{
			T key = array[i];
			int j = i - 1;
			while (j >= 0 && key < array[j])
			{
				array[j + 1] = array[j];
				--j;
			}
			array[j + 1] = key;
		}
	}

	template <typename T, std::size_t Size>
	void sort(T (&array)[Size])
	{
		sort(array, std::less<T>());
	}
}
