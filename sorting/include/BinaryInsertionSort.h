#pragma once
/**
 * @file BinaryInsertionSort.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Sorting algorithm that combines Binary Search and Insertion Sort.
 * @note Only supports C-style array and vectors.
 *
 * @par Time Complexity
 * Runs in O(N^2), Θ(N^2), Ω(N)
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <cstddef>
#include <vector>


namespace algorithms
{

    template <typename T, std::size_t Size, typename Comparator>
    void binaryInsertionSort(T (&array)[Size], Comparator comp);

    template <typename T, std::size_t Size>
    void binaryInsertionSort(T (&array)[Size]);

    template <typename T, typename Comparator>
    void binaryInsertionSort(std::vector<T>& vector, Comparator comp);

    template <typename T>
    void binaryInsertionSort(std::vector<T>& vector);
} // namespace algorithms


#include "BinaryInsertionSort.tpp"