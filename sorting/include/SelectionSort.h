#pragma once
/**
 * @file SelectionSort.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Sorting algorithm that sorts a data structure by "selecting" a key element and placing it in the correct
 * position by comparing it with every forward elements.
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
    void selectionSort(T (&array)[Size], Comparator comp);

    template <typename T, std::size_t Size>
    void selectionSort(T (&array)[Size]);

    template <typename T, typename Comparator>
    void selectionSort(std::vector<T>& vector, Comparator comp);

    template <typename T>
    void selectionSort(std::vector<T>& vector);
} // namespace algorithms


#include "SelectionSort.tpp"
