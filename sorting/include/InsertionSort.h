#pragma once
#include <cstddef>

namespace Algorithms::InsertionSort
{
        template <typename T, std::size_t Size, typename Comparator>
        void sort(T (&array)[Size], Comparator comp);

        template <typename T, std::size_t Size>
        void sort(T (&array)[Size]);

}

#include <InsertionSort.tpp>