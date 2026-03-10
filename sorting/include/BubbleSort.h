#pragma once
/**
 * @file BubbleSort.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Sorting algorithm that sorts a data structure by "bubbling up" elements (largest or smallest depending on
 * comparator).
 * @note Only supports C-style array and std::vector.
 *
 * @par Time Complexity
 * Runs in O(N^2), Θ(N^2), Ω(N^2)
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstddef>
#include <vector>


namespace algorithms
{

    template <typename T, std::size_t Size, typename Comparator>
    void bubbleSort(T (&array)[Size], Comparator comp);

    template <typename T, std::size_t Size>
    void bubbleSort(T (&array)[Size]);


    template <typename T, typename Comparator>
    void bubbleSort(std::vector<T>& vector, Comparator comp);

    template <typename T>
    void bubbleSort(std::vector<T>& vector);
} // namespace algorithms


#include "BubbleSort.tpp"
