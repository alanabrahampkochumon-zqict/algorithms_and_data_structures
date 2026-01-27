#pragma once

#include <functional>
#include <type_traits>

namespace Algorithms::RecursiveInsertionSort
{
    template<typename T, typename Comparator>
    void _sort(T* data, const size_t size, Comparator comp)
    {
        static_assert(std::is_invocable_r_v<bool, Comparator, T, T>, "Comparable must be a invocable(function)(T,T) with a bool return value.");

        if (size <  2) return;

        _sort(data, size - 1, comp);

        T key = data[size - 1];
        int i = static_cast<int>(size) - 2;
        for (; i >= 0 && comp(key, data[i]); --i)
        {
			data[i + 1] = data[i];
        }
        data[i + 1] = key;
    }


    template <typename T, std::size_t Size, typename Comparator>
    void sort(T (&array)[Size], Comparator comp)
    {
        _sort(array, Size, comp);
    }

    template <typename T, std::size_t Size>
    void sort(T(& array)[Size])
    {
        _sort(array, Size, std::less<T>());
    }

    template <typename T, typename Comparator>
    void sort(std::vector<T>& vector, Comparator comp)
    {
        _sort(vector.data(), vector.size(), comp);
    }

    template <typename T>
    void sort(std::vector<T>& vector)
    {
        _sort(vector.data(), vector.size(), std::less<T>());
    }
}
