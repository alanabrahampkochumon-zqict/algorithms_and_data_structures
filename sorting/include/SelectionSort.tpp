#pragma once
/**
 * @file SelectionSort.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Selection sort implementation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstddef>
#include <functional>
#include <regex>
#include <type_traits>
#include <vector>


namespace algorithms
{

    template <typename T, typename Comparator>
    void _sort(T* data, size_t size, Comparator comp)
    {
        static_assert(std::is_invocable_r_v<bool, Comparator, T, T>,
                      "Comparator error: Comparator must be a function that takes (T, T) and return a bool.");

        for (size_t i = 0; i < size - 1; ++i)
        {
            size_t minIndex = i;
            for (size_t j = i + 1; j < size; ++j)
            {
                if (comp(data[j], data[minIndex]))
                {
                    minIndex = j;
                }
            }
            // Swap
            // T temp = data[minIndex];
            // data[minIndex] = data[i];
            // data[i] = temp;
            std::swap(data[i], data[minIndex]);
        }
    }

    template <typename T, std::size_t Size, typename Comparator>
    void selectionSort(T (&array)[Size], Comparator comp)
    {
        _sort(array, Size, comp);
    }

    template <typename T, std::size_t Size>
    void selectionSort(T (&array)[Size])
    {
        _sort(array, Size, std::less<T>());
    }

    template <typename T, typename Comparator>
    void selectionSort(std::vector<T>& vector, Comparator comp)
    {
        _sort(vector.data(), vector.size(), comp);
    }

    template <typename T>
    void selectionSort(std::vector<T>& vector)
    {
        _sort(vector.data(), vector.size(), std::less<T>());
    }

} // namespace algorithms
