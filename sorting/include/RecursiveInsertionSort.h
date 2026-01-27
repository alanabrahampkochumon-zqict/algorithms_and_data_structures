#pragma once
#include <cstddef>
#include <vector>

namespace Algorithms::RecursiveInsertionSort
{
    template <typename T, std::size_t Size, typename Comparator>
    void sort(T(&array)[Size], Comparator comp);

    template <typename T, std::size_t Size>
    void sort(T(&array)[Size]);

    template<typename T, typename Comparator>
    void sort(std::vector<T>& vector, Comparator comp);

    template<typename T>
    void sort(std::vector<T>& vector);

}

#include "RecursiveInsertionSort.tpp"